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
// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}

SlidePot Sensor(1500,0); // copy calibration from Lab 7

const int8_t ThrPerpX[32] = {  2,   2,   2,   2,   1,   1,   1,   0,   0,   0,  -1,  -1,  -1,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   1,   1,   1,   2,   2,   2};
const int8_t ThrPerpY[32] = {  0,   0,  -1,  -1,  -1,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   1,   1,   1,   0};
const int8_t ThrExhX[32]  = {  0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,   0};
const int8_t ThrExhY[32]  = {  1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1};
const int8_t ThrBaseX[32] = {  0,   1,   3,   4,   5,   6,   6,   7,   7,   7,   6,   6,   5,   4,   3,   1,   0,  -1,  -3,  -4,  -5,  -6,  -6,  -7,  -7,  -7,  -6,  -6,  -5,  -4,  -3,  -1};
const int8_t ThrBaseY[32] = {  7,   7,   6,   6,   5,   4,   3,   1,   0,  -1,  -3,  -4,  -5,  -6,  -6,  -7,  -7,  -7,  -6,  -6,  -5,  -4,  -3,  -1,   0,   1,   3,   4,   5,   6,   6,   7};

const int8_t FlameAnchorX[32] = {  -7,   -4,    0,    2,    5,    7,    8,    9,    9,    9,    7,    6,    3,    1,   -2,   -6,   -9,  -12,  -16,  -18,  -21,  -23,  -24,  -25,  -25,  -25,  -23,  -22,  -19,  -17,  -14,  -10};
const int8_t FlameAnchorY[32] = {  25,   25,   23,   22,   19,   17,   14,   10,    7,    4,    0,   -2,   -5,   -7,   -8,   -9,   -9,   -9,   -7,   -6,   -3,   -1,    2,    6,    9,   12,   16,   18,   21,   23,   24,   25};

void DrawFlame(int16_t rocketX, int16_t rocketY, uint32_t rocket_angle){
  int16_t cx = rocketX + 9;
  int16_t cy = rocketY - 9;
  ST7735_DrawBitmap(cx + FlameAnchorX[rocket_angle],
                    cy + FlameAnchorY[rocket_angle],
                    FlameFrames[rocket_angle], 16, 16);
}

void DrawThruster(int16_t rocketX, int16_t rocketY, uint32_t rocket_angle){
  int16_t cx = rocketX + 9;
  int16_t cy = rocketY - 9;
  int16_t tx = cx + ThrBaseX[rocket_angle];
  int16_t ty = cy + ThrBaseY[rocket_angle];
  ST7735_Line(tx - ThrPerpX[rocket_angle],
              ty - ThrPerpY[rocket_angle],
              tx + ThrPerpX[rocket_angle],
              ty + ThrPerpY[rocket_angle],
              0xFFFF);
}


// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

// use main1 to observe special characters
int main1(void){ // main1
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(0x0000);            // set screen to black
  myLanguage = English;
  for(int i = 0; i < PHRASE_COUNT; i++){
    ST7735_OutString((char*)GetPhrase((phrase_t)i));
    ST7735_OutChar(13); // newline
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);
  myLanguage = Spanish;
  for(int i = 0; i < PHRASE_COUNT; i++){
    ST7735_OutString((char*)GetPhrase((phrase_t)i));
    ST7735_OutChar(13);
  }
}

// use main2 to observe graphics
int main(void){
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB);
  ST7735_FillScreen(ST7735_BLACK);

  const int16_t rocketX = 55;
  const int16_t rocketY = 90;

  while(1){
    for(int i = 0; i < 32; i++){
      ST7735_FillRect(46, 63, 36, 36, ST7735_BLACK);
      ST7735_DrawBitmap(rocketX, rocketY, Rocket[i], 18, 18);
      DrawThruster(rocketX, rocketY, i);
      DrawFlame(rocketX, rocketY, i);
      Clock_Delay1ms(150);
    }
  }
}

// use main3 to test switches and LEDs
int main3(void){
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB);
  ST7735_FillScreen(ST7735_BLACK);
  Switch_Init();
  LED_Init();

  ST7735_SetCursor(0, 0);
  ST7735_OutString((char*)"Switch Test");
  ST7735_SetCursor(0, 1);
  ST7735_OutString((char*)"PA24=Thrust");
  ST7735_SetCursor(0, 2);
  ST7735_OutString((char*)"PA25=Reset");

  uint32_t last = 0;
  while(1){
    uint32_t sw = Switch_In();

    if(sw & THRUSTER_SW){
      LED_On(RED_LED);
    } else {
      LED_Off(RED_LED);
    }

    if(sw & RESET_SW){
      LED_On(GREEN_LED);
    } else {
      LED_Off(GREEN_LED);
    }

    if(sw != last){
      ST7735_SetCursor(0, 4);
      ST7735_OutString((char*)"Thrust: ");
      ST7735_OutUDec(sw & THRUSTER_SW ? 1 : 0);
      ST7735_OutChar(' ');
      ST7735_SetCursor(0, 5);
      ST7735_OutString((char*)"Reset:  ");
      ST7735_OutUDec(sw & RESET_SW ? 1 : 0);
      ST7735_OutChar(' ');
      last = sw;
    }

    Clock_Delay1ms(10);
  }
}

// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  Sensor.Init(); // PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  
  // initialize all data structures
  __enable_irq();

  while(1){
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
  }
}
