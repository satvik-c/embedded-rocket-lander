// Dump.c
// Your solution to ECE319K Lab 3 Spring 2026
// Author: Satvik Chawla
// Last Modified: Your date


#include <ti/devices/msp/msp.h>
#include "../inc/Timer.h"
#include <math.h>
#define MAXBUF 50
uint32_t DataBuffer[MAXBUF];
uint32_t TimeBuffer[MAXBUF];
uint32_t DebugCnt; // 0 to MAXBUF (0 is empty, MAXBUF is full)

// *****Debug_Init******
// Initializes your index or pointer.
// Input: none
// Output:none
void Debug_Init(void){
// students write this for Lab 3
// This function should also initialize Timer G12, call TimerG12_Init.
  DebugCnt = 0;
  TimerG12_Init();
}

// *****Debug_Dump******
// Records one data and one time into the two arrays.
// Input: data is value to store in DataBuffer
// Output: 1 for success, 0 for failure (buffers full)
uint32_t Debug_Dump(uint32_t data){
// students write this for Lab 3
// The software simply reads TIMG12->COUNTERREGS.CTR to get the current time in bus cycles.
  if (DebugCnt >= MAXBUF) {
    return 0;
  }

  DataBuffer[DebugCnt] = data;
  TimeBuffer[DebugCnt] = TIMG12->COUNTERREGS.CTR;
  DebugCnt++;
  
  return 1; // success
}

// *****Debug_Dump2******
// Always record data and time on the first call to Debug_Dump2
// However, after the first call
//    Records one data and one time into the two arrays, only if the data is different from the previous call.
//    Do not record data or time if the data is the same as the data from the previous call
// Input: data is value to store in DataBuffer
// Output: 1 for success (saved or skipped), 0 for failure (buffers full)
uint32_t Debug_Dump2(uint32_t data){
// students write this for Lab 3
// The software simply reads TIMG12->COUNTERREGS.CTR to get the current time in bus cycles.
  if (DebugCnt == 0) {
    DataBuffer[DebugCnt] = data;
    TimeBuffer[DebugCnt] = TIMG12->COUNTERREGS.CTR;
    DebugCnt++;
    return 1;
  } 
  
  else if (DebugCnt >= MAXBUF) {
    return 0;
  }

  if (data != DataBuffer[DebugCnt-1]) {
    DataBuffer[DebugCnt] = data;
    TimeBuffer[DebugCnt] = TIMG12->COUNTERREGS.CTR;
    DebugCnt++;
    return 1;
  }
  
  return 1; // success
}

// *****Debug_Period******
// Calculate period of the recorded data using mask
// Input: mask specifies which bit(s) to observe
// Output: period in bus cycles
// Period is defined as rising edge (low to high) to the next rising edge.
// Return 0 if there is not enough collected data to calculate period .
uint32_t Debug_Period(uint32_t mask){
// students write this for Lab 3
// This function should not alter the recorded data.
// AND each recorded data with mask,
//    if nonzero the signal is considered high.
//    if zero, the signal is considered low.
  uint32_t times[MAXBUF];
  uint32_t ct = 0;
  
  for (int i = 1; i < MAXBUF; i++) {
    if ((DataBuffer[i] & mask) > 0 && (DataBuffer[i-1] & mask) == 0) {
      times[ct] = TimeBuffer[i];
      ct++;
    }
  }

  if (ct <= 1) {
    return 0;
  }

  uint32_t sum = 0;

  for (int i = 0; i < ct-1; i++) {
    sum += (times[i] - times[i+1]);
  }

  return (sum/(ct-1));
  
}


// *****Debug_Duty******
// Calculate duty cycle of the recorded data using mask
// Input: mask specifies which bit(s) to observe
// Output: period in percent (0 to 100)
// Period is defined as rising edge (low to high) to the next rising edge.
// High is defined as rising edge (low to high) to the next falling edge.
// Duty cycle is (100*High)/Period
// Return 0 if there is not enough collected data to calculate duty cycle.
uint32_t Debug_Duty(uint32_t mask){
// students write this for Lab 3
// This function should not alter the recorded data.
// AND each recorded data with mask,
//    if nonzero the signal is considered high.
//    if zero, the signal is considered low.
  uint32_t pwSum = 0;
  uint32_t periodSum = 0;

  for(int i = 0; i < MAXBUF-2; i += 2){
    pwSum += (TimeBuffer[i] - TimeBuffer[i+1]);
    periodSum += (TimeBuffer[i] - TimeBuffer[i+2]);
  }

  if(periodSum == 0) return 0;
  return ceil(100.0*pwSum/periodSum);
  
}

// Lab2 specific debugging code
uint32_t Theperiod;
void Dump(void){
  uint32_t out = GPIOB->DOUT31_0&0x0070000; // PB18-PB16 outputs
  uint32_t in = GPIOB->DIN31_0&0x0F;        // PB3-PB0 inputs
  uint32_t data = out|in;                   // PB18-PB16, PB3-PB0
  uint32_t result = Debug_Dump(data);       // calls your Lab3 function
  if(result == 0){ // 0 means full
    Theperiod = Debug_Duty(1<<16);        // calls your Lab3 function
   
   __asm volatile("bkpt; \n"); // breakpoint here
// observe Theperiod
  }
}




