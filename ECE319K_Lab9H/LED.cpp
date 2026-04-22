/*
 * LED.cpp
 * Red LED:   PA26
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"

#define RED_LED   (1<<26)

void LED_Init(void){
  IOMUX->SECCFG.PINCM[PA26INDEX] = 0x00000081;
  GPIOA->DOE31_0 |= RED_LED;
  GPIOA->DOUTCLR31_0 = RED_LED;
}

void LED_On(uint32_t data){
  GPIOA->DOUTSET31_0 = data;
}

void LED_Off(uint32_t data){
  GPIOA->DOUTCLR31_0 = data;
}

void LED_Toggle(uint32_t data){
  GPIOA->DOUTTGL31_0 = data;
}