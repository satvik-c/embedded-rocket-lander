// Lab7HMain.c
// Runs on MSPM0G3507
// Lab 7 
// Satvik Chawla, Shane Nguyen
// Last Modified: 3/28/26

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/SlidePot.h"
extern "C" void __disable_irq(void);
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);

// in ECE319H Lab 7, all classes will be statically allocated
SlidePot Sensor(1760, 198); // needs calibration

// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

// implement this function
void OutFix(uint32_t n){
// resolution is 0.001cm
// n is integer 0 to 2000
// output to ST7735 0.000cm to 2.000cm
  
  ST7735_OutChar('0' + n / 1000);
  ST7735_OutChar('.');
  ST7735_OutChar('0' + (n % 1000) / 100);
  ST7735_OutChar('0' + (n % 100)  / 10);
  ST7735_OutChar('0' + (n % 10));
  ST7735_OutChar(' ');
  ST7735_OutChar('c');
  ST7735_OutChar('m');
}

// do not use this function in final lab solution
// it is added just to show you how SLOW floating point in on a Cortex M0+
void FloatOutFix(float x){
// resolution cm
// x is integer 0 to 2.000
// output to ST7735 0.000cm to 2.000cm
  printf("d=%f cm   ",x);  // floating point output
}

uint32_t Data;        // 12-bit ADC
uint32_t Position;    // 32-bit fixed-point 0.001 cm
float FloatPosition;  // 32-bit floating-point cm
uint32_t startTime,stopTime;
uint32_t Offset,ADCtime,Converttime,FloatConverttime,OutFixtime,FloatOutFixtime, PlotTime; // in bus cycles
uint32_t Time;


// sampling frequency is 30 Hz
void TIMG12_IRQHandler(void){
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    Time++;
    // sample
    Data = Sensor.In();
    // store data into mailbox
    // and set the semaphore
    Sensor.Save(Data);

    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}

uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

// use main5 for final system
// use scope or logic analyzer to verify real time samples
// option 1) remove call to TExaS_Init and use a real scope on PB27
// option 2) use TExaS logic analyzer
int main(void){ // main5
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  SysTick->LOAD = 0xFFFFFF;    // max
  SysTick->VAL = 0;            // any write to current clears it
  SysTick->CTRL = 0x00000005;  // enable SysTick with core clock
  Sensor.Init(); //PB18 = ADC1 channel 5, slidepot
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
  ST7735_PlotClear(0,2000);
  // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(2666667, 1);

  startTime = SysTick->VAL;
  stopTime = SysTick->VAL;
  Offset = (startTime-stopTime)&0x0FFFFFF; 
 
  Time = 0;
  __enable_irq();

  while(1){
    // complete this
    Sensor.Sync();

    GPIOB->DOUTTGL31_0 = RED; // toggle PB26 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = RED; // toggle PB26 (minimally intrusive debugging)
    // toggle red LED2 on Port B, PB26
    // convert Data to Position
    Position = Sensor.Distance();
    // move cursor to top
    ST7735_SetCursor(0, 0);
    // display distance in top row OutFix
    startTime = SysTick->VAL;
    OutFix(Position);
    stopTime = SysTick->VAL;
    OutFixtime = ((startTime-stopTime)&0x0FFFFFF)-Offset; // in bus cycles

    Time++;
    if((Time%15)==0){
      startTime = SysTick->VAL;
      ST7735_PlotPoint(Position);
      ST7735_PlotNextErase(); // data plotted at about 2 Hz
      stopTime = SysTick->VAL;
      PlotTime = ((startTime-stopTime)&0x0FFFFFF)-Offset;
    }
    GPIOB->DOUTTGL31_0 = RED; // toggle PB26 (minimally intrusive debugging)
  }
}