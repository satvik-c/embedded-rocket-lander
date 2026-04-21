// Lab9HMain.cpp
// Runs on MSPM0G3507
// Lab 9 ECE319H
// Your name
// Last Modified: January 12, 2026

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/SlidePot.h"
#include "../inc/DAC5.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "Language.h"
#include "images/images.h"
extern "C" void __disable_irq(void);
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);

void PLL_Init(void){ Clock_Init80MHz(0); }

uint32_t M = 1;
uint32_t Random32(void){ M = 1664525*M+1013904223; return M; }
uint32_t Random(uint32_t n){ return (Random32()>>16)%n; }

SlidePot Sensor(1760, 198);

// ═══════════════════════════════════════════════════════════════════════════════
//  Lookup tables
// ═══════════════════════════════════════════════════════════════════════════════
const int8_t ThrPerpX[32] = {  2,   2,   2,   2,   1,   1,   1,   0,   0,   0,  -1,  -1,  -1,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   1,   1,   1,   2,   2,   2};
const int8_t ThrPerpY[32] = {  0,   0,  -1,  -1,  -1,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   1,   1,   1,   0};
const int8_t ThrExhX[32]  = {  0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,   0};
const int8_t ThrExhY[32]  = {  1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1};
const int8_t ThrBaseX[32] = {  0,   1,   3,   4,   5,   6,   6,   7,   7,   7,   6,   6,   5,   4,   3,   1,   0,  -1,  -3,  -4,  -5,  -6,  -6,  -7,  -7,  -7,  -6,  -6,  -5,  -4,  -3,  -1};
const int8_t ThrBaseY[32] = {  7,   7,   6,   6,   5,   4,   3,   1,   0,  -1,  -3,  -4,  -5,  -6,  -6,  -7,  -7,  -7,  -6,  -6,  -5,  -4,  -3,  -1,   0,   1,   3,   4,   5,   6,   6,   7};
const int8_t FlameAnchorX[32] = {  -7,   -4,    0,    2,    5,    7,    8,    9,    9,    9,    7,    6,    3,    1,   -2,   -6,   -9,  -12,  -16,  -18,  -21,  -23,  -24,  -25,  -25,  -25,  -23,  -22,  -19,  -17,  -14,  -10};
const int8_t FlameAnchorY[32] = {  25,   25,   23,   22,   19,   17,   14,   10,    7,    4,    0,   -2,   -5,   -7,   -8,   -9,   -9,   -9,   -7,   -6,   -3,   -1,    2,    6,    9,   12,   16,   18,   21,   23,   24,   25};

// ═══════════════════════════════════════════════════════════════════════════════
//  App state machine
// ═══════════════════════════════════════════════════════════════════════════════
enum AppState {
  APP_LANG_SELECT,
  APP_DIFFICULTY_SELECT,
  APP_ROUNDS_SELECT,
  APP_COUNTDOWN,
  APP_PLAYING,
  APP_PAUSED,         // ← new: pause menu shown mid-round
  APP_ROUND_RESULT,
  APP_GAME_OVER
};
volatile AppState appState = APP_LANG_SELECT;

// ═══════════════════════════════════════════════════════════════════════════════
//  Session data
// ═══════════════════════════════════════════════════════════════════════════════
typedef struct {
  uint8_t  language;
  uint8_t  difficulty;
  uint8_t  totalRounds;
  uint8_t  currentRound;
  uint32_t roundScore;
  uint32_t totalScore;
  uint8_t  roundsLanded;
  uint8_t  roundsCrashed;
} GameSession;
GameSession session;

// ═══════════════════════════════════════════════════════════════════════════════
//  Physics / round state
// ═══════════════════════════════════════════════════════════════════════════════
enum RoundState { ROUND_PLAYING, ROUND_LANDED, ROUND_CRASHED };
volatile RoundState roundState;

volatile int32_t  rocketX_q8, rocketY_q8;
volatile int32_t  velX_q8,    velY_q8;
volatile int32_t  hullAngle_q8;
volatile int32_t  angularVel_q8;
volatile uint32_t angle;
volatile uint32_t fuel;
volatile uint8_t  thrustActive;
volatile uint32_t prevSw;         // tracks previous sw for edge detection in ISR
volatile uint32_t Semaphore = 0;
volatile uint32_t SlidePotResult = 0;

#define Q8(x)    ((int32_t)(x) << 8)
#define UNQ8(x)  ((x) >> 8)

#define START_X   Q8(55)
#define START_Y   Q8(10)
#define PAD_Y     140
#define ROCKET_W  18

// Difficulty-driven values set by ApplyDifficulty()
int32_t  PAD_X_MIN    = 48;
int32_t  PAD_X_MAX    = 80;
int32_t  GRAVITY_VAL  = 5;
uint32_t FUEL_MAX_VAL = 270;

#define THRUST_FORCE  20
#define SAFE_VY_Q8    Q8(2)
#define SAFE_VX_Q8    Q8(1)

#define GIMBAL_STAGES 7
#define GIMBAL_RANGE  (GIMBAL_STAGES / 2)   // = 3
#define TORQUE_GAIN   1
#define ANG_VEL_MAX   Q8(1)
#define ANG_DAMP_NUM  63
#define ANG_DAMP_DEN  64

// ═══════════════════════════════════════════════════════════════════════════════
//  Language strings
// ═══════════════════════════════════════════════════════════════════════════════
#define LANG_EN 0
#define LANG_ES 1
#define NUM_LANGS 2

typedef enum {
  PH_SELECT_LANG, PH_ENGLISH, PH_SPANISH,
  PH_DIFFICULTY, PH_EASY, PH_MEDIUM, PH_HARD,
  PH_ROUNDS, PH_3_ROUNDS, PH_5_ROUNDS, PH_7_ROUNDS,
  PH_ROUND, PH_OF,
  PH_LANDED, PH_CRASHED,
  PH_ROUND_SCORE, PH_TOTAL_SCORE,
  PH_NEXT_ROUND,
  PH_GAME_OVER, PH_LANDED_COUNT, PH_CRASHED_COUNT,
  PH_FINAL_SCORE, PH_PLAY_AGAIN,
  PH_CONFIRM,
  PH_PAUSED,          // "PAUSED"   / "PAUSADO"
  PH_RESUME,          // "Resume"   / "Reanudar"
  PH_RESTART_ROUND,   // "Restart"  / "Reiniciar"
  PH_PAUSE_HINT,      // "Thr=OK  Rst=Resume" / ...
  NUM_PHRASES
} PhraseID;

const char* Phrases[NUM_PHRASES][NUM_LANGS] = {
  { "Select Language",   "Seleccionar Idioma" },
  { "English",           "Ingl\x82s"          },
  { "Spanish",           "Espa\x96ol"         },
  { "Difficulty",        "Dificultad"         },
  { "Easy",              "F \x83 cil"           },
  { "Medium",            "Medio"              },
  { "Hard",              "Dif \x96 cil"         },
  { "Rounds",            "Rondas"             },
  { "3 Rounds",          "3 Rondas"           },
  { "5 Rounds",          "5 Rondas"           },
  { "7 Rounds",          "7 Rondas"           },
  { "Round",             "Ronda"              },
  { "of",                "de"                 },
  { "LANDED!",           "ATERRIZAJE!"        },
  { "CRASHED!",          "CHOQUE!"            },
  { "Round Score:",      "Puntaje:"           },
  { "Total Score:",      "Total:"             },
  { "Thrust = Next",     "Empuje = Sig."      },
  { "GAME OVER",         "FIN DEL JUEGO"      },
  { "Landed:",           "Aterrizados:"       },
  { "Crashed:",          "Choques:"           },
  { "Final Score:",      "Puntaje Final:"     },
  { "Thrust = Again",    "Empuje = Otra Vez"  },
  { "Thr=OK  Rst=Back",  "Emp=OK  Rst=Atras"  },
  { "PAUSED",            "PAUSADO"            },
  { "Resume",            "Reanudar"           },
  { "Restart Round",     "Reiniciar Ronda"    },
  { "Thr=OK  Rst=Resume","Emp=OK  Rst=Reanudar"},
};

static inline const char* Ph(PhraseID id){ return Phrases[id][session.language]; }

// ═══════════════════════════════════════════════════════════════════════════════
//  Difficulty
// ═══════════════════════════════════════════════════════════════════════════════
void ApplyDifficulty(void){
  switch(session.difficulty){
    case 0: PAD_X_MIN=40; PAD_X_MAX=88; GRAVITY_VAL=4; FUEL_MAX_VAL=360; break;
    case 1: PAD_X_MIN=48; PAD_X_MAX=80; GRAVITY_VAL=5; FUEL_MAX_VAL=270; break;
    case 2: PAD_X_MIN=54; PAD_X_MAX=74; GRAVITY_VAL=7; FUEL_MAX_VAL=180; break;
  }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Input helpers
// ═══════════════════════════════════════════════════════════════════════════════
static inline int32_t GimbalOffset(uint32_t pot){
  uint32_t bw    = 4096 / GIMBAL_STAGES;
  uint32_t stage = pot / bw;
  if(stage >= (uint32_t)GIMBAL_STAGES) stage = GIMBAL_STAGES - 1;
  return -((int32_t)stage - GIMBAL_RANGE); // negated = pot direction flip
}

static inline uint8_t PotToOption(uint32_t pot, uint8_t nOpts){
  uint32_t idx = (pot * nOpts) >> 12;
  if(idx >= nOpts) idx = nOpts - 1;
  return (uint8_t)idx;
}

// menuPrevSw is separate from prevSw so pause/resume button edges don't
// bleed into menu edge detection and vice versa.
static uint32_t menuPrevSw = 0;
static inline bool RisingEdge(uint32_t sw, uint32_t bit){
  return (sw & bit) && !(menuPrevSw & bit);
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Draw helpers
// ═══════════════════════════════════════════════════════════════════════════════
void DrawThruster(int16_t rx, int16_t ry, uint32_t hull, uint32_t thr){
  int16_t cx=rx+9, cy=ry-9;
  int16_t tx=cx+ThrBaseX[hull], ty=cy+ThrBaseY[hull];
  ST7735_Line(tx-ThrPerpX[thr], ty-ThrPerpY[thr],
              tx+ThrPerpX[thr], ty+ThrPerpY[thr], 0xFFFF);
}
void DrawFlame(int16_t rx, int16_t ry, uint32_t hull, uint32_t thr){
  int16_t cx=rx+9, cy=ry-9;
  int16_t extX=(int16_t)FlameAnchorX[thr]-(int16_t)ThrBaseX[thr];
  int16_t extY=(int16_t)FlameAnchorY[thr]-(int16_t)ThrBaseY[thr];
  ST7735_DrawBitmap(cx+(int16_t)ThrBaseX[hull]+extX,
                    cy+(int16_t)ThrBaseY[hull]+extY,
                    FlameFrames[thr], 16, 16);
}

static int32_t sPrevX=-1, sPrevY=-1;
static inline int16_t clamp16(int32_t v,int32_t lo,int32_t hi){
  if(v<lo)return(int16_t)lo; if(v>hi)return(int16_t)hi; return(int16_t)v;
}

void DrawScreen(void){
  int32_t  px   = UNQ8(rocketX_q8);
  int32_t  py   = UNQ8(rocketY_q8);
  uint32_t hull = UNQ8(hullAngle_q8);

  if(sPrevX >= 0){
    int16_t ex=clamp16(sPrevX-28,0,127), ey=clamp16(sPrevY-37,0,159);
    int16_t ew=clamp16(sPrevX+46,0,127)-ex, eh=clamp16(sPrevY+19,0,159)-ey;
    ST7735_FillRect(ex, ey, ew, eh, ST7735_BLACK);
  }
  ST7735_DrawFastHLine((int16_t)PAD_X_MIN, PAD_Y,
                       (int16_t)(PAD_X_MAX-PAD_X_MIN), ST7735_WHITE);
  ST7735_DrawBitmap(px, py, Rocket[hull], 18, 18);
  if(thrustActive){ DrawThruster(px,py,hull,angle); DrawFlame(px,py,hull,angle); }

  // Fuel gauge
  uint32_t fp=(fuel*40)/FUEL_MAX_VAL;
  ST7735_FillRect(1,10,4,40,ST7735_BLACK);
  if(fp>0){ ST7735_FillRect(1,(int16_t)(10+(40-fp)),4,(int16_t)fp, fp>13?ST7735_GREEN:ST7735_RED); }

  // Round indicator
  ST7735_SetCursor(11,0);
  ST7735_OutUDec(session.currentRound); ST7735_OutChar('/'); ST7735_OutUDec(session.totalRounds);

  sPrevX=px; sPrevY=py;
}

// ── Generic menu screen ───────────────────────────────────────────────────────
void DrawMenuScreen(PhraseID titleID, const PhraseID opts[], uint8_t nOpts, uint8_t sel, PhraseID hintID){
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_SetCursor(0,0); ST7735_OutString((char*)Ph(titleID));
  for(uint8_t i=0;i<nOpts;i++){
    ST7735_SetCursor(0,2+i);
    ST7735_OutString((char*)(i==sel ? "> " : "  "));
    ST7735_OutString((char*)Ph(opts[i]));
  }
  ST7735_SetCursor(0,14); ST7735_OutString((char*)Ph(hintID));
}

// ═══════════════════════════════════════════════════════════════════════════════
//  ResetRound
// ═══════════════════════════════════════════════════════════════════════════════
void ResetRound(void){
  roundState   = ROUND_PLAYING;
  rocketX_q8  = START_X; rocketY_q8  = START_Y;
  velX_q8     = 0;       velY_q8     = 0;
  hullAngle_q8= 0;       angularVel_q8=0;
  angle=0; fuel=FUEL_MAX_VAL; thrustActive=0;
  sPrevX=-1; sPrevY=-1;
}

// ═══════════════════════════════════════════════════════════════════════════════
//  GameTick — called from ISR only during APP_PLAYING
//  Reset button is handled in the ISR before GameTick, so it never reaches here.
// ═══════════════════════════════════════════════════════════════════════════════
void GameTick(uint32_t sw){
  if(roundState != ROUND_PLAYING){ thrustActive=0; return; }

  int32_t curHull = UNQ8(hullAngle_q8);
  int32_t gimbal  = GimbalOffset(SlidePotResult);
  angle = (uint32_t)(curHull + gimbal + 32) % 32;

  velY_q8 += GRAVITY_VAL;

  thrustActive = ((sw & THRUSTER_SW) && fuel > 0) ? 1 : 0;
  if(thrustActive){
    fuel--;
    velX_q8 -= (int32_t)ThrExhX[angle] * THRUST_FORCE;
    velY_q8 -= (int32_t)ThrExhY[angle] * THRUST_FORCE;
    angularVel_q8 += gimbal * TORQUE_GAIN;
    // TODO: Sound_ThrusterOn();
  }

  angularVel_q8 = (angularVel_q8 * ANG_DAMP_NUM) / ANG_DAMP_DEN;
  if(angularVel_q8 >  ANG_VEL_MAX) angularVel_q8 =  ANG_VEL_MAX;
  if(angularVel_q8 < -ANG_VEL_MAX) angularVel_q8 = -ANG_VEL_MAX;

  hullAngle_q8 += angularVel_q8;
  if(hullAngle_q8 <   0)    hullAngle_q8 += Q8(32);
  if(hullAngle_q8 >= Q8(32))hullAngle_q8 -= Q8(32);
  curHull = UNQ8(hullAngle_q8);

  rocketX_q8 += velX_q8; rocketY_q8 += velY_q8;
  if(rocketX_q8 < 0)              { rocketX_q8=0;              velX_q8=-(velX_q8>>1); }
  if(rocketX_q8 > Q8(128-ROCKET_W)){ rocketX_q8=Q8(128-ROCKET_W); velX_q8=-(velX_q8>>1); }

  int32_t py=UNQ8(rocketY_q8);
  if(py >= PAD_Y){
    int32_t px=UNQ8(rocketX_q8), center=px+ROCKET_W/2;
    bool onPad  =(center>=PAD_X_MIN)&&(center<=PAD_X_MAX);
    bool safeVY =(velY_q8<=SAFE_VY_Q8);
    bool safeVX =(velX_q8>=-SAFE_VX_Q8)&&(velX_q8<=SAFE_VX_Q8);
    bool upRight=(curHull>=30)||(curHull<=2);

    if(onPad && safeVY && safeVX && upRight){
      roundState = ROUND_LANDED;
      uint32_t speedPenalty = (uint32_t)(velY_q8>0?velY_q8:0);
      session.roundScore  = 1000>speedPenalty*10 ? 1000-speedPenalty*10 : 100;
      session.totalScore += session.roundScore;
      session.roundsLanded++;
      // TODO: Sound_Landing();
    } else {
      roundState = ROUND_CRASHED;
      session.roundScore = 0;
      session.roundsCrashed++;
      // TODO: Sound_Explosion();
    }
    velX_q8=0; velY_q8=0; angularVel_q8=0; thrustActive=0;
    appState = APP_ROUND_RESULT;
  }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  ISR — 30 Hz
// ═══════════════════════════════════════════════════════════════════════════════
void TIMG12_IRQHandler(void){
  if((TIMG12->CPU_INT.IIDX) == 1){
    GPIOB->DOUTTGL31_0 = GREEN;
    SlidePotResult = Sensor.In();
    uint32_t sw = Switch_In();

    if(appState == APP_PLAYING){
      // Rising edge on RESET → pause instead of passing to GameTick
      bool resetEdge = (sw & RESET_SW) && !(prevSw & RESET_SW);
      if(resetEdge){
        thrustActive = 0;           // kill flame immediately
        appState     = APP_PAUSED;
        menuPrevSw   = sw;          // seed menu edge state
      } else {
        GameTick(sw);
      }
    }
    // All other states handled by main loop via Semaphore

    prevSw    = sw;
    Semaphore = 1;
    GPIOB->DOUTTGL31_0 = GREEN;
  }
}

uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Screen handlers
// ═══════════════════════════════════════════════════════════════════════════════

// ── Language select ───────────────────────────────────────────────────────────
static bool    langDrawn = false;
static uint8_t langSel   = 0;
void RunLangSelect(void){
  uint32_t sw = Switch_In();
  uint8_t  newSel = PotToOption(SlidePotResult, 2);
  const PhraseID opts[2] = { PH_ENGLISH, PH_SPANISH };
  if(!langDrawn || newSel != langSel){ langSel=newSel; DrawMenuScreen(PH_SELECT_LANG,opts,2,langSel,PH_CONFIRM); langDrawn=true; }
  if(RisingEdge(sw, THRUSTER_SW)){ session.language=langSel; langDrawn=false; menuPrevSw=sw; appState=APP_DIFFICULTY_SELECT; }
  menuPrevSw = sw;
}

// ── Difficulty select ─────────────────────────────────────────────────────────
static bool    diffDrawn = false;
static uint8_t diffSel   = 1;
void RunDifficultySelect(void){
  uint32_t sw = Switch_In();
  uint8_t  newSel = PotToOption(SlidePotResult, 3);
  const PhraseID opts[3] = { PH_EASY, PH_MEDIUM, PH_HARD };
  if(!diffDrawn || newSel != diffSel){ diffSel=newSel; DrawMenuScreen(PH_DIFFICULTY,opts,3,diffSel,PH_CONFIRM); diffDrawn=true; }
  if(RisingEdge(sw, THRUSTER_SW)){ session.difficulty=diffSel; diffDrawn=false; menuPrevSw=sw; appState=APP_ROUNDS_SELECT; }
  if(RisingEdge(sw, RESET_SW))   { diffDrawn=false; menuPrevSw=sw; appState=APP_LANG_SELECT; }
  menuPrevSw = sw;
}

// ── Rounds select ─────────────────────────────────────────────────────────────
static bool    roundsDrawn = false;
static uint8_t roundsSel   = 1;
void RunRoundsSelect(void){
  uint32_t sw = Switch_In();
  uint8_t  newSel = PotToOption(SlidePotResult, 3);
  const PhraseID opts[3] = { PH_3_ROUNDS, PH_5_ROUNDS, PH_7_ROUNDS };
  if(!roundsDrawn || newSel != roundsSel){ roundsSel=newSel; DrawMenuScreen(PH_ROUNDS,opts,3,roundsSel,PH_CONFIRM); roundsDrawn=true; }
  if(RisingEdge(sw, THRUSTER_SW)){
    const uint8_t counts[3]={3,5,7};
    session.totalRounds=counts[roundsSel]; session.currentRound=1;
    session.totalScore=0; session.roundsLanded=0; session.roundsCrashed=0;
    roundsDrawn=false; menuPrevSw=sw; appState=APP_COUNTDOWN;
  }
  if(RisingEdge(sw, RESET_SW)){ roundsDrawn=false; menuPrevSw=sw; appState=APP_DIFFICULTY_SELECT; }
  menuPrevSw = sw;
}

// ── Countdown ─────────────────────────────────────────────────────────────────
void RunCountdown(void){
  ApplyDifficulty();
  ResetRound();
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_SetCursor(3,1);
  ST7735_OutString((char*)Ph(PH_ROUND)); ST7735_OutChar(' ');
  ST7735_OutUDec(session.currentRound);  ST7735_OutChar(' ');
  ST7735_OutString((char*)Ph(PH_OF));    ST7735_OutChar(' ');
  ST7735_OutUDec(session.totalRounds);
  const char* nums[3]={"3","2","1"};
  for(int i=0;i<3;i++){ ST7735_SetCursor(6,7); ST7735_OutString((char*)nums[i]); Clock_Delay1ms(1000); }
  ST7735_SetCursor(5,7); ST7735_OutString((char*)"GO! "); Clock_Delay1ms(500);
  ST7735_FillScreen(ST7735_BLACK);
  prevSw   = Switch_In();  // clear stale button state before game starts
  menuPrevSw = prevSw;
  appState = APP_PLAYING;
}

// ── Pause menu ────────────────────────────────────────────────────────────────
// Two options: Resume (0) or Restart Round (1).
// Thruster button confirms selected option.
// Reset button always resumes regardless of selection.
static bool    pauseDrawn = false;
static uint8_t pauseSel   = 0;  // default = Resume

void RunPaused(void){
  uint32_t sw = Switch_In();
  uint8_t  newSel = PotToOption(SlidePotResult, 2);
  const PhraseID opts[2] = { PH_RESUME, PH_RESTART_ROUND };

  if(!pauseDrawn || newSel != pauseSel){
    pauseSel = newSel;
    DrawMenuScreen(PH_PAUSED, opts, 2, pauseSel, PH_PAUSE_HINT);
    pauseDrawn = true;
  }

  bool thrEdge = RisingEdge(sw, THRUSTER_SW);
  bool rstEdge = RisingEdge(sw, RESET_SW);

  if(rstEdge || (thrEdge && pauseSel == 0)){
    // Resume — return to game exactly as it was, just redraw the game screen
    pauseDrawn = false;
    menuPrevSw = sw;
    ST7735_FillScreen(ST7735_BLACK);   // clear pause menu
    sPrevX = -1; sPrevY = -1;         // force full sprite redraw on next frame
    prevSw   = sw;                    // reseed ISR edge state so reset edge is consumed
    appState = APP_PLAYING;
  } else if(thrEdge && pauseSel == 1){
    // Restart round — re-run countdown for this round number
    pauseDrawn = false;
    menuPrevSw = sw;
    // Undo the session stats that haven't been committed yet
    // (no stats are committed mid-round; they only write on landing/crash)
    appState = APP_COUNTDOWN;
  }
  menuPrevSw = sw;
}

// ── Round result ──────────────────────────────────────────────────────────────
static bool resultDrawn = false;
void RunRoundResult(void){
  uint32_t sw = Switch_In();
  if(!resultDrawn){
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_SetCursor(0,0);
    ST7735_OutString((char*)Ph(PH_ROUND)); ST7735_OutChar(' ');
    ST7735_OutUDec(session.currentRound);  ST7735_OutChar(' ');
    ST7735_OutString((char*)Ph(PH_OF));    ST7735_OutChar(' ');
    ST7735_OutUDec(session.totalRounds);
    ST7735_SetCursor(0,2);
    ST7735_OutString((char*)Ph(roundState==ROUND_LANDED ? PH_LANDED : PH_CRASHED));
    ST7735_SetCursor(0,4);
    ST7735_OutString((char*)Ph(PH_ROUND_SCORE)); ST7735_OutChar(' '); ST7735_OutUDec(session.roundScore);
    ST7735_SetCursor(0,6);
    ST7735_OutString((char*)Ph(PH_TOTAL_SCORE));  ST7735_OutChar(' '); ST7735_OutUDec(session.totalScore);
    ST7735_SetCursor(0,14);
    ST7735_OutString((char*)Ph(PH_NEXT_ROUND));
    resultDrawn = true;
  }
  if(RisingEdge(sw, THRUSTER_SW)){
    resultDrawn=false; menuPrevSw=sw; session.currentRound++;
    appState = (session.currentRound > session.totalRounds) ? APP_GAME_OVER : APP_COUNTDOWN;
  }
  menuPrevSw = sw;
}

// ── Game over ─────────────────────────────────────────────────────────────────
static bool gameOverDrawn = false;
void RunGameOver(void){
  uint32_t sw = Switch_In();
  if(!gameOverDrawn){
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_SetCursor(3,0);  ST7735_OutString((char*)Ph(PH_GAME_OVER));
    ST7735_SetCursor(0,2);  ST7735_OutString((char*)Ph(PH_LANDED_COUNT));  ST7735_OutChar(' '); ST7735_OutUDec(session.roundsLanded);
    ST7735_SetCursor(0,4);  ST7735_OutString((char*)Ph(PH_CRASHED_COUNT)); ST7735_OutChar(' '); ST7735_OutUDec(session.roundsCrashed);
    ST7735_SetCursor(0,6);  ST7735_OutString((char*)Ph(PH_FINAL_SCORE));   ST7735_OutChar(' '); ST7735_OutUDec(session.totalScore);
    ST7735_SetCursor(0,14); ST7735_OutString((char*)Ph(PH_PLAY_AGAIN));
    gameOverDrawn = true;
  }
  if(RisingEdge(sw, THRUSTER_SW)){
    gameOverDrawn=false; langDrawn=false; diffDrawn=false; roundsDrawn=false;
    menuPrevSw=sw; appState=APP_LANG_SELECT;
  }
  menuPrevSw = sw;
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Test mains
// ═══════════════════════════════════════════════════════════════════════════════
int main1(void){
  __disable_irq(); PLL_Init(); LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); ST7735_FillScreen(0x0000);
  session.language=LANG_EN;
  for(int i=0;i<NUM_PHRASES;i++){ ST7735_OutString((char*)Ph((PhraseID)i)); ST7735_OutChar(13); }
  Clock_Delay1ms(3000); ST7735_FillScreen(0x0000);
  session.language=LANG_ES;
  for(int i=0;i<NUM_PHRASES;i++){ ST7735_OutString((char*)Ph((PhraseID)i)); ST7735_OutChar(13); }
  while(1){}
}

int main2(void){
  __disable_irq(); PLL_Init(); LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); ST7735_FillScreen(ST7735_BLACK);
  const int16_t rx=55,ry=90;
  while(1){
    for(int hull=0;hull<32;hull++){
      for(int off=-GIMBAL_RANGE;off<=GIMBAL_RANGE;off++){
        uint32_t thr=(uint32_t)((hull+off+32)%32);
        ST7735_FillRect(20,55,60,60,ST7735_BLACK);
        ST7735_DrawBitmap(rx,ry,Rocket[hull],18,18);
        DrawThruster(rx,ry,hull,thr); DrawFlame(rx,ry,hull,thr);
        Clock_Delay1ms(60);
      }
    }
  }
}

volatile uint32_t switch_debug_raw; 

int main(void) {
    // 1. Power up the board and GPIO Port A
    LaunchPad_Init(); 

    // 2. Set PA26 and PA24 to Input mode with Internal Pull-ups
    // (This ensures they aren't 'floating' and reading random noise)
    IOMUX->SECCFG.PINCM[PA26INDEX] = 0x00040081;
    IOMUX->SECCFG.PINCM[PA24INDEX] = 0x00040081;

    while(1) {
        // 3. Constant read of the entire 32-bit Port A register
        switch_debug_raw = GPIOA->DIN31_0;
        
        // Small NOP delay for stability
        for(volatile int i=0; i<100; i++); 
    }
}

int main3(void){
  __disable_irq(); PLL_Init(); LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); ST7735_FillScreen(ST7735_BLACK);
  Switch_Init(); LED_Init();
  ST7735_SetCursor(0,0); ST7735_OutString((char*)"Switch Test");
  ST7735_SetCursor(0,1); ST7735_OutString((char*)"PA26=Thrust");
  ST7735_SetCursor(0,2); ST7735_OutString((char*)"PA24=Reset");
  uint32_t last=0;
  uint32_t sw;
  while(1){
    sw=Switch_In();
    if(sw&THRUSTER_SW) LED_On(RED_LED);   else LED_Off(RED_LED);
    if(sw&RESET_SW)    LED_On(GREEN_LED); else LED_Off(GREEN_LED);
    if(sw!=last){
      ST7735_SetCursor(0,4); ST7735_OutString((char*)"Thrust: "); ST7735_OutUDec(sw&THRUSTER_SW?1:0);
      ST7735_SetCursor(0,5); ST7735_OutString((char*)"Reset:  "); ST7735_OutUDec(sw&RESET_SW?1:0);
      last=sw;
    }
    Clock_Delay1ms(10);
  }
}

int main4(void){
  uint32_t last=0,now;
  __disable_irq(); PLL_Init(); LaunchPad_Init();
  Switch_Init(); LED_Init(); Sound_Init(); TExaS_Init(ADC0,6,0);
  __enable_irq();
  while(1){
    now=Switch_In();
    if((last==0)&&(now==1)) Sound_Shoot();
    if((last==0)&&(now==2)) Sound_Killed();
    if((last==0)&&(now==4)) Sound_Explosion();
    if((last==0)&&(now==8)) Sound_Fastinvader1();
    last=now;
  }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Production main
// ═══════════════════════════════════════════════════════════════════════════════
int main5(void){
  __disable_irq();
  PLL_Init(); LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB);
  ST7735_FillScreen(ST7735_BLACK);
  Sensor.Init(); Switch_Init(); LED_Init(); Sound_Init();
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26);

  session.language=LANG_EN; session.difficulty=1;
  session.totalRounds=5;    session.currentRound=1;
  session.totalScore=0;     session.roundsLanded=0; session.roundsCrashed=0;
  menuPrevSw=0; prevSw=0;
  appState=APP_LANG_SELECT;

  TimerG12_IntArm(2666667, 2);  // 80 MHz / 2666667 ≈ 30 Hz
  __enable_irq();

  while(1){
    while(Semaphore==0){}
    Semaphore=0;
    switch(appState){
      case APP_LANG_SELECT:       RunLangSelect();       break;
      case APP_DIFFICULTY_SELECT: RunDifficultySelect(); break;
      case APP_ROUNDS_SELECT:     RunRoundsSelect();     break;
      case APP_COUNTDOWN:         RunCountdown();        break;
      case APP_PLAYING:           DrawScreen();          break;
      case APP_PAUSED:            RunPaused();           break;
      case APP_ROUND_RESULT:      RunRoundResult();      break;
      case APP_GAME_OVER:         RunGameOver();         break;
    }
  }
}