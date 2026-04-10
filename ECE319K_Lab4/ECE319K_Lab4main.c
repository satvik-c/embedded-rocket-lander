/* ECE319K_Lab4main.c
 * Traffic light FSM
 * ECE319H students must use pointers for next state
 * ECE319K students can use indices or pointers for next state
 * Satvik Chawla (sc73994)
 * Spring 2026
  */

#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/UART.h"
#include "../inc/Timer.h"
#include "../inc/Dump.h"  // student's Lab 3
#include <stdio.h>
#include <string.h>
// put your EID in the next line
const char EID1[] = "sc73994"; //  ;replace abc123 with your EID
// Hint implement Traffic_Out before creating the struct, make struct match your Traffic_Out
const uint32_t codes[4] = {0, 1, 2, 4};

struct State {
  uint32_t index;
  uint32_t west;
  uint32_t south;
  uint32_t walk;
  double time;
  const struct State *next[8];
}; typedef const struct State State_t;

#define goSouth       &FSM[0]
#define hurrySouth    &FSM[1]
#define allStopSouth  &FSM[2]
#define goWest        &FSM[3]
#define hurryWest     &FSM[4]
#define allStopWest   &FSM[5]
#define goWalk        &FSM[6]
#define red1          &FSM[7]
#define off1          &FSM[8]
#define red2          &FSM[9]
#define off2          &FSM[10]
#define red3          &FSM[11]
#define off3          &FSM[12]
#define allStopWalk   &FSM[13]

State_t FSM[14] = {
  {0, 4, 1, 4, 3, {goSouth, hurrySouth, goSouth, hurrySouth, hurrySouth, hurrySouth, hurrySouth, hurrySouth}},
  {1, 4, 2, 4, 1, {allStopSouth, allStopSouth, allStopSouth, allStopSouth, allStopSouth, allStopSouth, allStopSouth, allStopSouth}},
  {2, 4, 4, 4, 1, {goWest, goWest, goSouth, goWest, goWalk, goWest, goWalk, goWalk}},
  {3, 1, 4, 4, 3, {goWest, goWest, hurryWest, hurryWest, hurryWest, hurryWest, hurryWest, hurryWest}},
  {4, 2, 4, 4, 1, {allStopWest, allStopWest, allStopWest, allStopWest, allStopWest, allStopWest, allStopWest, allStopWest}},
  {5, 4, 4, 4, 1, {goSouth, goWest, goSouth, goSouth, goWalk, goWalk, goSouth, goSouth}},
  {6, 4, 4, 7, 3, {goWalk, red1, red1, red1, goWalk, red1, red1, red1}},
  {7, 4, 4, 4, 1, {off1, off1, off1, off1, off1, off1, off1, off1}},
  {8, 4, 4, 0, 1, {red2, red2, red2, red2, red2, red2, red2, red2}},
  {9, 4, 4, 4, 1, {off2, off2, off2, off2, off2, off2, off2, off2}},
  {10, 4, 4, 0, 1, {red3, red3, red3, red3, red3, red3, red3, red3}},
  {11, 4, 4, 4, 1, {off3, off3, off3, off3, off3, off3, off3, off3}},
  {12, 4, 4, 0, 1, {allStopWalk, allStopWalk, allStopWalk, allStopWalk, allStopWalk, allStopWalk, allStopWalk, allStopWalk}},
  {13, 4, 4, 4, 1, {goSouth, goWest, goSouth, goSouth, goWalk, goWest, goSouth, goWest}}
};

State_t* pt;

// initialize all 6 LED outputs and 3 switch inputs
// assumes LaunchPad_Init resets and powers A and B
void Traffic_Init(void){ // assumes LaunchPad_Init resets and powers A and B
  IOMUX->SECCFG.PINCM[PB0INDEX] = IOMUX->SECCFG.PINCM[PB1INDEX] = 
  IOMUX->SECCFG.PINCM[PB2INDEX] = IOMUX->SECCFG.PINCM[PB6INDEX] = 
  IOMUX->SECCFG.PINCM[PB7INDEX] = IOMUX->SECCFG.PINCM[PB8INDEX] = 0x81;
  GPIOB->DOE31_0 |= 0x1C7;

  IOMUX->SECCFG.PINCM[PB15INDEX] = IOMUX->SECCFG.PINCM[PB16INDEX] = 
  IOMUX->SECCFG.PINCM[PB17INDEX] = 0x40081;
}

uint32_t convertWalk(uint32_t in) { // R G B means bit 2 is red, bit 1 is green, bit 0 is blue
  uint32_t result = 0;              // R -> 26, G -> 27, B -> 22
  
  result |= (in & 0x4)<<24;
  result |= (in & 0x2)<<26;
  result |= (in & 0x1)<<22;

  return result;
}

/* Activate LEDs
* Inputs: west is 3-bit value to three east/west LEDs
*         south is 3-bit value to three north/south LEDs
*         walk is 3-bit value to 3-color positive logic LED on PB22,PB26,PB27
* Output: none
* - west =1 sets west green
* - west =2 sets west yellow
* - west =4 sets west red
* - south =1 sets south green
* - south =2 sets south yellow
* - south =4 sets south red
* - walk=0 to turn off LED
* - walk bit 22 sets blue color
* - walk bit 26 sets red color
* - walk bit 27 sets green color
* Feel free to change this. But, if you change the way it works, change the test programs too
* Be friendly*/
void Traffic_Out(uint32_t west, uint32_t south, uint32_t walk){
  west = west<<6;

  uint32_t combined = 0;
  combined |= south | west | convertWalk(walk);

  uint32_t mask = 0x0C4001C7;

  GPIOB->DOUT31_0 = (GPIOB->DOUT31_0 & (~mask)) | combined;
}
/* Read sensors
 * Input: none
 * Output: sensor values
 * - bit 0 is west car sensor
 * - bit 1 is south car sensor
 * - bit 2 is walk people sensor
* Feel free to change this. But, if you change the way it works, change the test programs too
 */
uint32_t Traffic_In(void){
  return (GPIOB->DIN31_0 & 0x38000)>>15;
}
// use main1 to determine Lab4 assignment
void Lab4Grader(int mode);
void Grader_Init(void);
int main1(void){ // main1
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Lab4Grader(0); // print assignment, no grading
  while(1){
  }
}
// use main2 to debug LED outputs
// at this point in ECE319K you need to be writing your own test functions
// modify this program so it tests your Traffic_Out  function
int main2(void){ // main2
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  LaunchPad_LED1off();
  SysTick_Init();
  Traffic_Init(); // your Lab 4 initialization
  uint32_t dump;
  if((GPIOB->DOE31_0 & 0x20)==0){
    UART_OutString("access to GPIOB->DOE31_0 should be friendly.\n\r");
  }
  UART_Init();
  UART_OutString("Lab 4, Spring 2026, Step 1. Debug LEDs\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  while(1){
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        for(int k=0;k<4;k++){
          uint32_t west  = codes[i];
          uint32_t south = codes[j];
          uint32_t walk  = codes[k];
          Traffic_Out(west, south, walk);
          dump = 0;
          dump |= walk | south<<8 | west<<16;
          Debug_Dump(dump);
          SysTick_Wait10ms(10);
        }
      }
    }
    if((GPIOB->DOUT31_0&0x20) == 0){
      UART_OutString("DOUT not friendly\n\r");
    }
  }
}
// use main3 to debug the three input switches
// at this point in ECE319K you need to be writing your own test functions
// modify this program so it tests your Traffic_In  function
int main3(void){ // main3
  uint32_t last=0, now;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Traffic_Init(); // your Lab 4 initialization
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2026, Step 2. Debug switches\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  while(1){
    now = Traffic_In(); // Your Lab4 input
    if(now != last){ // change
      UART_OutString("Switch= 0x"); UART_OutUHex(now); UART_OutString("\n\r");
      Debug_Dump(now);
    }
    last = now;
    Clock_Delay(800000); // 10ms, to debounce switch
  }
}
// use main4 to debug using your dump
// proving your machine cycles through all states
int main4(void){// main4
  uint32_t dump;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
  pt = goSouth;
  Debug_Init();   // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2026, Step 3. Debug FSM cycle\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
// initialize your FSM
  SysTick_Init();   // Initialize SysTick for software waits

  while(1){
    Traffic_Out(pt->west, pt->south, pt->walk);
    dump = 0;
    dump |= (pt->walk) | (pt->south)<<8 | (pt->west)<<16 | (pt->index)<<24;
    Debug_Dump(dump);
    SysTick_Wait10ms((uint32_t) pt->time*100);
    pt = pt->next[7];
  }
}
// use main5 to grade
int main(void){// main5
  uint32_t dump;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
  pt = goSouth;
  SysTick_Init();   // Initialize SysTick for software waits
  Lab4Grader(1); // activate UART, grader and interrupts
  while(1){
    Traffic_Out(pt->west, pt->south, pt->walk);
    dump = 0;
    dump |= (pt->walk) | (pt->south)<<8 | (pt->west)<<16 | (pt->index)<<24;
    Debug_Dump(dump);
    SysTick_Wait10ms(((uint32_t) pt->time*100)/2);
    pt = pt->next[Traffic_In()];
  }
}

