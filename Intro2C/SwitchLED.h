/* This is the header file that
   holds the prototypes of functions
   implemented in the SwitchLED.c module.
*/
#include <stdint.h>
// SwitchLED_init sets up Input Output to blink LED when switch is pressed
//   Switch on PB3; LED on PB18
void SwitchLED_init();
// SwitchIn gets Switch state
uint8_t Switch_In();
// LED_On turns LED On
void LED_On();
// LED_Off turns LED Off
void LED_Off();
// Delay is a crude implementation
// counts down a count passed
void Delay(uint32_t count);