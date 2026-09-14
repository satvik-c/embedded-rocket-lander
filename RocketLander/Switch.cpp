/*
 * Switch.cpp
 * Thruster button: PA24
 * Reset button:    PA25
 */
#include <ti/devices/msp/msp.h>
#include "../drivers/LaunchPad.h"

#define THRUSTER_PIN (1<<24)
#define RESET_PIN    (1<<25)

void Switch_Init(void){
  IOMUX->SECCFG.PINCM[PA24INDEX] = 0x00040081;
  IOMUX->SECCFG.PINCM[PA25INDEX] = 0x00040081;
}

uint32_t Switch_In(void){
  uint32_t data = GPIOA->DIN31_0;
  return ((data >> 24) & 0x03);
}