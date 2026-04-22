// Sound.cpp
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// your name
// your data 
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds/sounds.h"
#include "../inc/DAC.h"
#include "../inc/Timer.h"

const uint16_t * volatile Sound_Ptr;
volatile uint32_t Sound_Count;  

void SysTick_IntArm(uint32_t period, uint32_t priority){}

void Sound_Init(void){
  Sound_Ptr = 0;
  Sound_Count = 0;
  DAC_Init();
  SysTick->LOAD = 6663; 
  SysTick->CTRL = 0x00000007; 
  SysTick->VAL = 0;

  SCB->SHP[1] = (SCB->SHP[1] & ~0xC0000000);
}

extern "C" void SysTick_Handler(void);
void SysTick_Handler(void){
  if(Sound_Count > 0){
    Sound_Count--;
    DAC_Out(*Sound_Ptr);
    Sound_Ptr++;
  }
}

//******* Sound_Start ************
// This function does not output to the DAC. 
// Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// It starts the sound, and the SysTick ISR does the output
// feel free to change the parameters
// Sound should play once and stop
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement

void Sound_Start(const uint16_t *pt, uint32_t count){
  Sound_Ptr = pt;
  Sound_Count = count;
}

void Sound_Thrust(void){
  Sound_Start(thrust, sizeof(thrust)/2);

}

void Sound_Win(void){
  Sound_Start(win, sizeof(win)/2);
}

void Sound_Fah(void) {
  Sound_Start(fah, sizeof(fah)/2);
}
