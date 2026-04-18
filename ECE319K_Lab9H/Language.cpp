#include "Language.h"

Language_t myLanguage = English;

static const char * const Phrases[PHRASE_COUNT][2] = {
  {"Score",          "Puntos"},
  {"Fuel",           "Combustible"},
  {"Level",          "Nivel"},
  {"Press to Start", "Presione Iniciar"},
  {"Crash!",         "\xAD" "Choque!"},
  {"Safe Landing!",  "\xAD" "Terrizaje!"},
};

const char* GetPhrase(phrase_t id){
  return Phrases[id][myLanguage];
}