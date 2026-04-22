#include "Language.h"

Language_t myLanguage = English;

static const char * const Phrases[PHRASE_COUNT][2] = {

  // ── Original HUD ──────────────────────────────────────────────────────────
  /* PHRASE_SCORE        */ { "Score",           "Puntos"               },
  /* PHRASE_FUEL         */ { "Fuel",            "Combustible"          },
  /* PHRASE_LEVEL        */ { "Level",           "Nivel"                },
  /* PHRASE_PRESS_START  */ { "Press to Start",  "Presione Iniciar"     },
  /* PHRASE_CRASH        */ { "Crash!",          "\xAD" "Choque!"       },
  /* PHRASE_SAFE_LAND    */ { "Safe Landing!",   "\xAD" "Aterrizaje!"   },

  // ── Language select ───────────────────────────────────────────────────────
  /* PHRASE_SELECT_LANG  */ { "Select Language", "Seleccionar Idioma"   },
  /* PHRASE_ENGLISH      */ { "English",         "Ingl\x82s"            },
  /* PHRASE_SPANISH      */ { "Spanish",         "Espa\xA4ol"           },

  // ── Difficulty select ─────────────────────────────────────────────────────
  /* PHRASE_DIFFICULTY   */ { "Difficulty",      "Dificultad"           },
  /* PHRASE_EASY         */ { "Easy",            "F\xA0" "cil"          },
  /* PHRASE_MEDIUM       */ { "Medium",          "Medio"                },
  /* PHRASE_HARD         */ { "Hard",            "Dif\xA1" "cil"        },

  // ── Rounds select ─────────────────────────────────────────────────────────
  /* PHRASE_ROUNDS       */ { "Rounds",          "Rondas"               },
  /* PHRASE_3_ROUNDS     */ { "3 Rounds",        "3 Rondas"             },
  /* PHRASE_5_ROUNDS     */ { "5 Rounds",        "5 Rondas"             },
  /* PHRASE_7_ROUNDS     */ { "7 Rounds",        "7 Rondas"             },

  // ── Countdown / in-round ──────────────────────────────────────────────────
  /* PHRASE_ROUND        */ { "Round",           "Ronda"                },
  /* PHRASE_OF           */ { "of",              "de"                   },

  // ── Round result ──────────────────────────────────────────────────────────
  /* PHRASE_LANDED       */ { "LANDED!",         "ATERRIZAJE!"          },
  /* PHRASE_CRASHED      */ { "CRASHED!",        "CHOQUE!"              },
  /* PHRASE_ROUND_SCORE  */ { "Round Score:",    "Puntaje:"             },
  /* PHRASE_TOTAL_SCORE  */ { "Total Score:",    "Total:"               },
  /* PHRASE_NEXT_ROUND   */ { "Thrust = Next",   "Empuje = Sig."        },

  // ── Game over ─────────────────────────────────────────────────────────────
  /* PHRASE_GAME_OVER    */ { "GAME OVER",       "FIN DEL JUEGO"        },
  /* PHRASE_LANDED_COUNT */ { "Landed:",         "Aterrizados:"         },
  /* PHRASE_CRASHED_COUNT*/ { "Crashed:",        "Choques:"             },
  /* PHRASE_FINAL_SCORE  */ { "Final Score:",    "Puntaje Final:"       },
  /* PHRASE_PLAY_AGAIN   */ { "Thrust = Again",  "Empuje = Otra Vez"    },

  // ── Shared nav hint ───────────────────────────────────────────────────────
  /* PHRASE_CONFIRM      */ { "Thr=OK  Rst=Back",    "Emp=OK  Rst=Atras"    },

  // ── Pause menu ────────────────────────────────────────────────────────────
  /* PHRASE_PAUSED       */ { "PAUSED",              "PAUSADO"              },
  /* PHRASE_RESUME       */ { "Resume",              "Reanudar"             },
  /* PHRASE_RESTART_ROUND*/ { "Restart Round",       "Reiniciar Ronda"      },
  /* PHRASE_PAUSE_HINT   */ { "Thr=OK  Rst=Resume",  "Emp=OK  Rst=Reanudar" },
};

const char* GetPhrase(phrase_t id){
  return Phrases[id][myLanguage];
}