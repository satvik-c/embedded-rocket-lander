// ****************** ECE319K_Lab2H.s ***************
// Your solution to Lab 2 in assembly code
// Author: Satvik Chawla
// Last Modified: 2/1/2026
// ECE319H Spring 2026 (ECE319K students do Lab2)

    .include "../inc/msp.s"

        .data
        .align 2
// Declare global variables here if needed
// with the .space assembly directive

        .text
        .thumb
        .align 2
        .global EID
EID:    .string "SC73994" // replace ZZZ123 with your EID here
        .align 2
  .equ dot,100
  .equ dash,(3*dot)
  .equ shortgap,(2*dot)  // because it will send an interelement too
  .equ interelement,dot
  
  Morse:
  .long  dot,  dash,    0,    0, 0 // A
  .long  dash,  dot,  dot,  dot, 0 // B
  .long  dash,  dot, dash,  dot, 0 // C
  .long  dash,  dot,  dot,    0, 0 // D
  .long  dot,     0,    0,    0, 0 // E
  .long  dot,   dot, dash,  dot, 0 // F
  .long  dash, dash,  dot,    0, 0 // G
  .long  dot,   dot,  dot,  dot, 0 // H
  .long  dot,   dot,    0,    0, 0 // I
  .long  dot,  dash, dash, dash, 0 // J
  .long  dash,  dot, dash,    0, 0 // K
  .long  dot,  dash,  dot,  dot, 0 // L
  .long  dash, dash,    0,    0, 0 // M
  .long  dash,  dot,    0,    0, 0 // N
  .long  dash, dash, dash,    0, 0 // O
  .long  dot,  dash, dash,  dot, 0 // P
  .long  dash, dash,  dot, dash, 0 // Q
  .long  dot,  dash,  dot,    0, 0 // R
  .long  dot,   dot,  dot,    0, 0 // S
  .long  dash,    0,    0,    0, 0 // T
  .long  dot,   dot, dash,    0, 0 // U
  .long  dot,   dot,  dot, dash, 0 // V
  .long  dot,  dash, dash,    0, 0 // W
  .long  dash,  dot,  dot, dash, 0 // X
  .long  dash,  dot, dash, dash, 0 // Y
  .long  dash, dash,  dot,  dot, 0 // Z

  .align 2
  .global Lab2Grader
  .global Lab2
  .global Debug_Init // Lab3 programs
  .global Dump       // Lab3 programs

// Switch input: PB2 PB1 or PB0, depending on EID
// LED output:   PB18 PB17 or PB16, depending on EID
// logic analyzer pins PB18 PB17 PB16 PB2 PB1 PB0
// analog scope pin PB20
Lab2:
// Initially the main program will
//   set bus clock at 80 MHz,
//   reset and power enable both Port A and Port B
// Lab2Grader will
//   configure interrupts  on TIMERG0 for grader or TIMERG7 for TExaS
//   initialize ADC0 PB20 for scope,
//   initialize UART0 for grader or TExaS
//    MOVS R0,#1  // 0 for info, 1 debug with logic analyzer, 2 debug with scope, 10 for grade
//    BL   Lab2Grader
    BL  LaunchPad_Init
    BL   Lab2Init   // you initialize input pin and output pin
    BL  Debug_Init

loop:
/*
btnRelease:
    LDR     R0, =GPIOB_DIN31_0
    LDR     R1, [R0]
    LDR     R2, =0x1
    ANDS    R2, R1, R2
    BNE     btnRelease
    
btnPress:
    LDR     R0, =GPIOB_DIN31_0
    LDR     R1, [R0]
    LDR     R2, =0x1
    ANDS    R2, R1, R2
    BEQ     btnPress
*/
    MOVS R0, 'O'        //MOVS    R0, #10
                        //BL      Lab2Grader
    SUBS    R0, #65
    LDR     R1, =20
    MULS    R0, R1

    LDR     R4, =Morse
    ADDS    R4, R0

letterLoop:
    LDR     R0, [R4]
    CMP     R0, #0
    BEQ     nextCase
    BL      Out
    ADDS    R4, #4

    B      letterLoop

nextCase:
    B       loop




// make switch an input, LED an output
// PortB is already reset and powered
// Set IOMUX for your input and output
// Set GPIOB_DOE31_0 for your output (be friendly)
Lab2Init:
// ***do not reset/power Port A or Port B, already done****

   LDR      R0, =IOMUXPB0
   LDR      R1, =0x40081
   STR      R1, [R0]
   
   LDR      R0, =IOMUXPB16
   LDR      R1, =0x81
   STR      R1, [R0]
   LDR      R0, =GPIOB_DOE31_0
   LDR      R1, [R0]
   LDR      R2, =0x10000
   ORRS     R1, R1, R2
   STR      R1, [R0]

   BX       LR

Out:
    PUSH    {R4-R7, LR}

    ADDS    R4, R0, #0
    BL      LEDon
    BL      Dump
    ADDS    R0, R4, #0
    BL      Delay
    BL      LEDoff
    BL      Dump
    LDR     R0, =interelement
    BL      Delay
    
    POP     {R4-R7, PC}

LEDon:
    PUSH    {R4-R7, LR}

    LDR     R0, =GPIOB_DOUT31_0
    LDR     R1, [R0]
    LDR     R2, =0x10000
    ORRS    R1, R1, R2
    STR     R1, [R0]

    POP     {R4-R7, PC}

LEDoff:
    PUSH    {R4-R7, LR}

    LDR     R0, =GPIOB_DOUT31_0
    LDR     R1, [R0]
    LDR     R2, =0x10000
    BICS    R1, R1, R2
    STR     R1, [R0]

    POP     {R4-R7, PC}

Delay: // R0 has time in ms
    PUSH    {R4-R7, LR}

    LDR     R1, =20000
    MULS    R0, R1
dLoop:
    SUBS    R0, #1
    NOP
    BNE     dLoop

    POP     {R4-R7, PC}

Done:
    
   .end
