/* This module implements the GPIO funtions to:
    - setup Switch and LED
    - Read the Switch
    - Write to the LED
 Another example of splitting your project into multiple files
*/
#include <stdint.h>  // C99 
#include <ti/devices/msp/msp.h> // Imports MSPM0 Device Register Values
#include "../inc/LaunchPad.h"   // This has PB3Index and PB18Index
/* IOInit sets up Input Output to blink LED when switch is pressed
   Switch on PB3; LED on PB18
   Input: None
   Output: None
*/
// Delay is a crude implementation
// counts down a count passed
void Delay(uint32_t count){
  for (int i=0; i < count; i++){
    // do nothing
  }
}
void SwitchLED_init(){
	// Reset Port B
	GPIOB->GPRCM.RSTCTL = (uint32_t)0xB1000003;
	// Power up Port B
	GPIOB->GPRCM.PWREN = (uint32_t)0x26000001;
	// PB3: Input Enable; S/W; GPIO mode
    Delay(24); // The Reset and Power steps take time to
               // to complete: at least 24 bus cylces 
	IOMUX->SECCFG.PINCM[PB3INDEX] = (uint32_t) 0x00040081; 
	// PB18: S/W; GPIO mode
	IOMUX->SECCFG.PINCM[PB18INDEX] = (uint32_t) 0x00000081;
	// Output Enable PB18
	GPIOB->DOE31_0 |= 1<<18; 
}
/* Switch_In gets Switch state
	Inputs: None
	Outputs: return a 0: open; 1: closed(pressed)
*/
uint8_t Switch_In(){
   return ((GPIOB->DIN31_0) & (0x8))>>3;
}
/* LED_On turns LED On
	Inputs: None
	Outputs: None
*/
void LED_On(){
   GPIOB->DOUT31_0 |= 0x00040000;
}
/* LED_Off turns LED Off
	Inputs: None
	Outputs: None
*/
void LED_Off(){
   GPIOB->DOUT31_0 &= 0xFFFBFFFF;
}
