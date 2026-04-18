#ifndef LANGUAGE_H
#define LANGUAGE_H
#include <stdint.h>

typedef enum {English, Spanish} Language_t;

typedef enum {
  PHRASE_SCORE,
  PHRASE_FUEL,
  PHRASE_LEVEL,
  PHRASE_PRESS_START,
  PHRASE_CRASH,
  PHRASE_SAFE_LAND,
  PHRASE_COUNT
} phrase_t;

extern Language_t myLanguage;

const char* GetPhrase(phrase_t id);

#endif