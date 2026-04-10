/* ECE319K_Lab5main.c
 * Digital Piano using a Digital to Analog Converter
 * January 12, 2026
 * 5-bit binary-weighted DAC connected to PB4-PB0
 * 4-bit keyboard connected to PB19-PB16
 * 
 * Satvik Chawla (sc73994)
 * Spring 2026
*/

#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/UART.h"
#include "../inc/Timer.h"
#include "../inc/Dump.h"  // student's Lab 3
#include "../inc/DAC5.h"  // student's Lab 5
#include "../inc/Key.h"   // student's Lab 5
#include <stdio.h>
#include <string.h>
// put your EID in the next line
const char EID1[] = "s73994"; // replace abc123 with your EID

const uint8_t SineWave[32] = {
    16,19,22,24,27,28,30,31,31,31,30,
    28,27,24,22,19,16,13,10,8,5,4,
    2,1,1,1,2,4,5,8,10,13
};

uint32_t Index = 0;

// Period =  80000000/32/Freq=2500000/Freq			
#define C1   1194   // 2093 Hz			
#define B1   1265   // 1975.5 Hz			
#define BF1  1341   // 1864.7 Hz			
#define A1   1420   // 1760 Hz			
#define AF1  1505   // 1661.2 Hz			
#define G1   1594   // 1568 Hz			
#define GF1  1689   // 1480 Hz			
#define F1   1790   // 1396.9 Hz			
#define E1   1896   // 1318.5 Hz			
#define EF1  2009   // 1244.5 Hz			
#define D1   2128   // 1174.7 Hz			
#define DF1  2255   // 1108.7 Hz			
#define C    2389   // 1046.5 Hz			
#define B    2531   // 987.8 Hz			
#define BF   2681   // 932.3 Hz			
#define A    2841   // 880 Hz			
#define AF   3010   // 830.6 Hz			
#define G    3189   // 784 Hz			
#define GF  3378   // 740 Hz			
#define F   3579   // 698.5 Hz			
#define E   3792   // 659.3 Hz			
#define EF  4018   // 622.3 Hz			
#define D   4257   // 587.3 Hz			
#define DF  4510   // 554.4 Hz			
#define C0  4778   // 523.3 Hz			
#define B0  5062   // 493.9 Hz			
#define BF0 5363   // 466.2 Hz			
#define A0  5682   // 440 Hz			
#define AF0 6020   // 415.3 Hz			
#define G0  6378   // 392 Hz			
#define GF0 6757   // 370 Hz			
#define F0  7159   // 349.2 Hz			
#define E0  7584   // 329.6 Hz			
#define EF0 8035   // 311.1 Hz			
#define D0  8513   // 293.7 Hz			
#define DF0 9019   // 277.2 Hz			
#define C7  9556   // 261.6 Hz			
#define B7  10124   // 246.9 Hz			
#define BF7 10726   // 233.1 Hz			
#define A7  11364   // 220 Hz			
#define AF7 12039   // 207.7 Hz			
#define G7  12755   // 196 Hz			
#define GF7 13514   // 185 Hz			
#define F7  14317   // 174.6 Hz			
#define E7  15169   // 164.8 Hz			
#define EF7 16071   // 155.6 Hz			
#define D7  17026   // 146.8 Hz			
#define DF7 18039   // 138.6 Hz			
#define C6  19111   // 130.8 Hz			


// prototypes to your low-level Lab 5 code
void Sound_Init(uint32_t period, uint32_t priority);
void Sound_Start(uint32_t period);
void Sound_Stop(void);

// use main1 to determine Lab5 assignment
void Lab5Grader(int mode);
void Grader_Init(void);
int main1(void){ // main1
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Lab5Grader(0); // print assignment, no grading
  while(1){
  }
}
const uint32_t Inputs[12]={0, 1, 7, 8, 15, 16, 17, 23, 24, 25, 30, 31};
uint32_t Testdata;

// use main2a to perform static testing of DAC, if you have a voltmeter
int main2a(void){ // main2a
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init();   // execute this line before your code
  DAC5_Init();     // your Lab 5 initialization
  if((GPIOB->DOE31_0 & 0x20)==0){
    UART_OutString("access to GPIOB->DOE31_0 should be friendly.\n\r");
  }
  Debug_Init();    // Lab 3 debugging
  while(1){
    for(uint32_t i=0; i<12; i++){ //0-11
      Testdata = Inputs[i];
      DAC5_Out(Testdata);
      // put a breakpoint on the next line and use meter to measure DACout
      // place data in Table 5.3
      Debug_Dump(Testdata);
    }
    if((GPIOB->DOUT31_0&0x20) == 0){
      UART_OutString("DOUT not friendly\n\r");
    }
  }
}
// use main2b to perform static testing of DAC, if you do not have a voltmeter
// attach PB20 (scope uses PB20 as ADC input) to your DACout
// TExaSdisplay scope uses TimerG7, ADC0
// To use the scope, there can be no breakpoints in your code
int main2b(void){ // main2b
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init();   // execute this line before your code
  Lab5Grader(2);   // Scope
  DAC5_Init();     // your Lab 5 initialization
  if((GPIOB->DOE31_0 & 0x20)==0){
    while(1){}; // access to GPIOB->DOE31_0 should be friendly
  }
  Debug_Init();    // Lab 3 debugging
  while(1){
    for(uint32_t i=0; i<12; i++){ //0-11
      Testdata = Inputs[i];
      DAC5_Out(Testdata);
      Debug_Dump(Testdata);
        // use TExaSdisplay scope to measure DACout
        // place data in Table 5.3
        // touch and release S2 to continue
      while(LaunchPad_InS2()==0){}; // wait for S2 to be touched
      while(LaunchPad_InS2()!=0){}; // wait for S2 to be released
      if((GPIOB->DOUT31_0&0x20) == 0){
         while(1){}; // DOUT not friendly
      }
    }
  }
}
// use main3 to perform dynamic testing of DAC,
// In lab, attach your DACout to the real scope
// If you do not have a scope attach PB20 (scope uses PB20 as ADC input) to your DACout
// TExaSdisplay scope uses TimerG7, ADC0
// To perform dynamic testing, there can be no breakpoints in your code
// DACout will be a monotonic ramp with period 32ms,
int main3(void){ // main3
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init();   // execute this line before your code
  Lab5Grader(2);   // Scope
  DAC5_Init();     // your Lab 5 initialization
  Debug_Init();    // Lab 3 debugging
  while(1){
    for(uint32_t i=0; i<32; i++){ //0-31
      DAC5_Out(i);
      Debug_Dump(i);
        // scope to observe waveform
        // place data in Table 5.3
      Clock_Delay1ms(1);
    }
  }
}

// use main4 to debug the four input switches
int main4(void){ // main4
  uint32_t last=0,now;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Key_Init(); // your Lab 5 initialization
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 5, Spring 2026, Step 4. Debug switches\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  while(1){
    now = Key_In(); // Your Lab5 input
    if(now != last){ // change
      UART_OutString("Switch= 0x"); UART_OutUHex(now); UART_OutString("\n\r");
      Debug_Dump(now);
    }
    last = now;
    Clock_Delay(800000); // 10ms, to debounce switch
  }
}

// use main5 to debug your system
// In lab, attach your DACout to the real scope
// If you do not have a scope attach PB20 (scope uses PB20 as ADC input) to your DACout
// TExaSdisplay scope uses TimerG7, ADC0
// To perform dynamic testing, there can be no breakpoints in your code
// DACout will be a sine wave with period/frequency depending on which key is pressed
int main5(void){// main5
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Lab5Grader(2);   // 1=logic analyzer, 2=Scope, 3=grade
  DAC5_Init();     // DAC initialization
  Sound_Init(1,0); // SysTick initialization, initially off, priority 0
  Key_Init();      // Keyboard initialization
  Sound_Start(C7); // start one continuous wave
  while(1){
  }
}
// use main6 to debug/grade your final system
// In lab, attach your DACout to the real scope
// If you do not have a scope attach PB20 (scope uses PB20 as ADC input) to your DACout
// TExaSdisplay scope uses TimerG7, ADC0
// To perform dynamic testing, there can be no breakpoints in your code
// DACout will be a sine wave with period/frequency depending on which key is pressed

uint32_t notes[9] = {0, DF0, F0, 0, AF0, 0, 0, 0, BF0};
uint32_t last,key;

int main(void){// main6
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init();   // execute this line before your code
  Lab5Grader(2);   // 1=logic analyzer, 2=Scope, 3=grade
  DAC5_Init();     // DAC initialization
  Sound_Init(1,0); // SysTick initialization, initially off, priority 0
  Key_Init();      // Keyboard initialization
  Debug_Init();    // Lab 3 debugging
  last = 0;
  while(1){
// if key goes from not pressed to pressed
//   -call Sound_Start with the appropriate period
//   -call Debug_Dump with period
// if key goes from pressed to not pressed
//   -call Sound_Stop
// I.e., if key has not changed DO NOT CALL start or stop
    key = Key_In();
    if (key != last) {
      if (key == 0) {
        Sound_Stop();
      } else {
        Sound_Start(notes[key]);
        Debug_Dump(notes[key]);
      }
    }
    last = key;

    Clock_Delay(800000); // 10ms, to debounce switch
  }
}
// To grade you must connect PB20 to your DACout
// Run main5 with Lab5Grader(3);   // Grader
// Observe Terminal window

// ARM SysTick period interrupts
// Input: interrupts every 12.5ns*period
//        priority is 0 (highest) to 3 (lowest)
void Sound_Init(uint32_t period, uint32_t priority){
  Index = 0;
  SysTick->CTRL = 0;
  SysTick->LOAD = period-1;
  SysTick->VAL = 0;
  SCB->SHP[1] = (SCB->SHP[1] & ~0xC0000000) | (priority << 30);
  SysTick->CTRL = 0x07;
}

void Sound_Stop(void){
  // either set LOAD to 0 or clear bit 1 in CTRL
  SysTick->LOAD = 0;
}

void Sound_Start(uint32_t period){
  // set reload value
  // write any value to VAL, cause reload
  // write this
  SysTick->LOAD = period-1;
  SysTick->VAL = 0;
}

// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
  // write this
  // output one value to DAC
  DAC5_Out(SineWave[Index]);
  Index = (Index+1) & 0x1F;
}




/* DAC5.c
 * Satvik Chawla
 * Modified: put date here
 * 5-bit binary-weighted DAC connected to PB4-PB0
 */
#include <ti/devices/msp/msp.h>
#define PB0INDEX  11 // UART0_TX  SPI1_CS2  TIMA1_C0  TIMA0_C2
#define PB1INDEX  12 // UART0_RX  SPI1_CS3  TIMA1_C1  TIMA0_C2N
#define PB2INDEX  14 // UART3_TX  UART2_CTS I2C1_SCL  TIMA0_C3  UART1_CTS TIMG6_C0  TIMA1_C0
#define PB3INDEX  15 // UART3_RX  UART2_RTS I2C1_SDA  TIMA0_C3N UART1_RTS TIMG6_C1  TIMA1_C1
#define PB4INDEX  16 // UART1_TX  UART3_CTS TIMA1_C0  TIMA0_C2  TIMA1_C0N

// **************DAC5_Init*********************
// Initialize 5-bit DAC, called once
// Input: none
// Output: none
void DAC5_Init(void){
// Assumes LaunchPad_Init has been called
// I.e., PortB has already been reset and activated (do not reset PortB here again)
     IOMUX->SECCFG.PINCM[PB0INDEX] = 
     IOMUX->SECCFG.PINCM[PB1INDEX] = 
     IOMUX->SECCFG.PINCM[PB2INDEX] = 
     IOMUX->SECCFG.PINCM[PB3INDEX] = 
     IOMUX->SECCFG.PINCM[PB4INDEX] = 0x81;

     GPIOB->DOE31_0 |= 0x1F;
}

// **************DAC5_Out*********************
// output to DAC5
// Input: 5-bit data, 0 to 31
// Input=n is converted to n*3.3V/31
// Output: none
// Note: this solution must be friendly
void DAC5_Out(uint32_t data){
     GPIOB->DOUT31_0 = (GPIOB->DOUT31_0 & ~0x1F) | data;
}





/* Key.c
 * Satvik Chawla
 * Modified: January 12, 2026
 * 4-bit keyboard connected to PB19-PB16
 * Piano key 3 PB19 (note with highest frequency)
 * Piano key 2 PB18
 * Piano key 1 PB17
 * Piano key 0 PB16 (note with lowest frequency)
 *
 */
#include <ti/devices/msp/msp.h>
#define PB16INDEX 32 // UART2_RX  SPI1_SCK  UART3_RTS TIMG8_C1  TIMG7_C1
#define PB17INDEX 42 // UART2_TX  SPI0_PICO SPI1_CS1  TIMA1_C0  TIMA0_C2
#define PB18INDEX 43 // UART2_RX  SPI0_SCK  SPI1_CS2  TIMA1_C1  TIMA0_C2N
#define PB19INDEX 44 // COMP2_OUT SPI0_POCI TIMG8_C1  UART0_CTS TIMG7_C1
#include "../inc/LaunchPad.h"

// **************Key_Init*********************
// Initialize piano key inputs on PB19-PB16
// Input: none
// Output: none
void Key_Init(void){
// Assumes LaunchPad_Init has been called
// I.e., PortB has already been reset and activated (do not reset PortB here again)
    IOMUX->SECCFG.PINCM[PB16INDEX] = 
    IOMUX->SECCFG.PINCM[PB17INDEX] = 
    IOMUX->SECCFG.PINCM[PB18INDEX] = 
    IOMUX->SECCFG.PINCM[PB19INDEX] = 0x40081;
}

// **************Key_In*********************
// Input from piano key inputs on PB19-PB16
// Input: none
// Output: 0 to 15 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2, 0x08 is just Key3
uint32_t Key_In(void){
    // regular Lab5
    return (GPIOB->DIN31_0 & 0xF0000) >> 16;
}
