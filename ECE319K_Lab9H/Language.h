#ifndef LANGUAGE_H
#define LANGUAGE_H
#include <stdint.h>

// ── Language selector ─────────────────────────────────────────────────────────
typedef enum { English, Spanish } Language_t;
extern Language_t myLanguage;

// ── All user-facing strings in the game ──────────────────────────────────────
// Add new phrases here and add matching translations in Language.cpp.
typedef enum {

  // ── Original game HUD phrases ─────────────────────────────────────────────
  PHRASE_SCORE,           // "Score"          / "Puntos"
  PHRASE_FUEL,            // "Fuel"           / "Combustible"
  PHRASE_LEVEL,           // "Level"          / "Nivel"
  PHRASE_PRESS_START,     // "Press to Start" / "Presione Iniciar"
  PHRASE_CRASH,           // "Crash!"         / "¡Choque!"
  PHRASE_SAFE_LAND,       // "Safe Landing!"  / "¡Aterrizaje!"

  // ── Language select screen ────────────────────────────────────────────────
  PHRASE_SELECT_LANG,     // "Select Language"   / "Seleccionar Idioma"
  PHRASE_ENGLISH,         // "English"           / "Inglés"
  PHRASE_SPANISH,         // "Spanish"           / "Español"

  // ── Difficulty select screen ──────────────────────────────────────────────
  PHRASE_DIFFICULTY,      // "Difficulty"  / "Dificultad"
  PHRASE_EASY,            // "Easy"        / "Fácil"
  PHRASE_MEDIUM,          // "Medium"      / "Medio"
  PHRASE_HARD,            // "Hard"        / "Difícil"

  // ── Rounds select screen ──────────────────────────────────────────────────
  PHRASE_ROUNDS,          // "Rounds"    / "Rondas"
  PHRASE_3_ROUNDS,        // "3 Rounds"  / "3 Rondas"
  PHRASE_5_ROUNDS,        // "5 Rounds"  / "5 Rondas"
  PHRASE_7_ROUNDS,        // "7 Rounds"  / "7 Rondas"

  // ── Countdown / in-round ──────────────────────────────────────────────────
  PHRASE_ROUND,           // "Round"  / "Ronda"
  PHRASE_OF,              // "of"     / "de"

  // ── Round result screen ───────────────────────────────────────────────────
  PHRASE_LANDED,          // "LANDED!"       / "ATERRIZAJE!"
  PHRASE_CRASHED,         // "CRASHED!"      / "CHOQUE!"
  PHRASE_ROUND_SCORE,     // "Round Score:"  / "Puntaje:"
  PHRASE_TOTAL_SCORE,     // "Total Score:"  / "Total:"
  PHRASE_NEXT_ROUND,      // "Thrust = Next" / "Empuje = Sig."

  // ── Game over screen ──────────────────────────────────────────────────────
  PHRASE_GAME_OVER,       // "GAME OVER"     / "FIN DEL JUEGO"
  PHRASE_LANDED_COUNT,    // "Landed:"       / "Aterrizados:"
  PHRASE_CRASHED_COUNT,   // "Crashed:"      / "Choques:"
  PHRASE_FINAL_SCORE,     // "Final Score:"  / "Puntaje Final:"
  PHRASE_PLAY_AGAIN,      // "Thrust = Again"/ "Empuje = Otra Vez"

  // ── Shared nav hint ───────────────────────────────────────────────────────
  PHRASE_CONFIRM,         // "Thr=OK  Rst=Back"   / "Emp=OK  Rst=Atras"

  // ── Pause menu ────────────────────────────────────────────────────────────
  PHRASE_PAUSED,          // "PAUSED"          / "PAUSADO"
  PHRASE_RESUME,          // "Resume"          / "Reanudar"
  PHRASE_RESTART_ROUND,   // "Restart Round"   / "Reiniciar Ronda"
  PHRASE_PAUSE_HINT,      // "Thr=OK  Rst=Resume" / "Emp=OK  Rst=Reanudar"

  PHRASE_COUNT            // always last — used for array sizing
} phrase_t;

// Returns the string for the given phrase in the currently selected language.
const char* GetPhrase(phrase_t id);

#endif