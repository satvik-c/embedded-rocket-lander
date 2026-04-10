/* UART2.cpp
 * Satvik Chawla, Shane Nguyen
 * Data:
 * PA22 UART2 Rx from other microcontroller PA8 IR output<br>
 */


#include <ti/devices/msp/msp.h>
#include "UART2.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/FIFO2.h"

uint32_t LostData, RxCounter;
extern Queue FIFO;

// power Domain PD0
// for 80MHz bus clock, UART2 clock is ULPCLK 40MHz
// initialize UART2 for 2375 baud rate
// no transmit, interrupt on receive timeout
void UART2_Init(void){
  // RSTCLR to GPIOA and UART2 peripherals
  // write this
  LostData = 0;
  //GPIOA->GPRCM.RSTCTL = 0xB1000003; 
  UART2->GPRCM.RSTCTL = 0xB1000003; // reset UART0
  UART2->GPRCM.PWREN = 0x26000001; // activate UART0
  Clock_Delay(24); // time for uart to activate
// configure PA11 PA10 as alternate UART0 function
  IOMUX->SECCFG.PINCM[PA22INDEX] = 0x00040082;
  
//bits 5-0=2 for UART0_Rx
  UART2->CLKSEL = 0x08; // bus clock
  UART2->CLKDIV = 0x00; // no divide
  UART2->CTL0 &= ~0x01; // disable UART0
  UART2->CTL0 = 0x00020018; // enable fifos, tx and rx
// 40000000/16 = 2,500,000, 2,500,000/115200 = 21.70139
  UART2->IBRD = 1052; // divider = 21+45/64 = 21.703125
  UART2->FBRD = 40;
  UART2->LCRH = 0x00000030; // 8bit, 1 stop, no parity
  //UART2->CTL0 |= 0x01; // enable UART0 
  UART2->CPU_INT.IMASK = 0x01;

  UART2->IFLS = 0x0422;

  NVIC->ICPR[0] = 1<<14;
  NVIC->ISER[0] = 1<<14;
  NVIC->IP[3] = (NVIC->IP[3]&(~0xF000000))|(2<<22);

  UART2->CTL0 |= 0x01;
}

//------------UART2_InChar------------
// Get new serial port receive data from FIFO2
// Input: none
// Output: Return 0 if the FIFO2 is empty
//         Return nonzero data from the FIFO1 if available
char UART2_InChar(void){char out;
  while(FIFO.IsEmpty()) {};
  FIFO.Get(&out);
  return out;
}

extern "C" void UART2_IRQHandler(void);
void UART2_IRQHandler(void){ uint32_t status; char letter;
  status = UART2->CPU_INT.IIDX; // reading clears bit in RTOUT
  if(status == 0x01){   // 0x01 receive timeout
    GPIOB->DOUTTGL31_0 = BLUE; // toggle PB22 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = BLUE; // toggle PB22 (minimally intrusive debugging)
    // read all data, putting in FIFO
    // finish writing this
    while ((UART2->STAT & 0x04) != 0x04) {
      letter = (char)(UART2->RXDATA);
      if (!FIFO.IsFull()) {
        FIFO.Put(letter);
      }
    }
    
    RxCounter++;
    GPIOB->DOUTTGL31_0 = BLUE; // toggle PB22 (minimally intrusive debugging)
  }
}
