// StringConversion.s
// Student names: Satvik Chawla, Shane Nguyen
// Last modification date: 3/4/2026
// Runs on any Cortex M0
// ECE319K lab 6 number to string conversion
//
// You write udivby10 and Dec2String
   .data
   .align 2
// no globals allowed for Lab 6
   .global OutChar    // virtual output device
   .global OutDec     // your Lab 6 function
   .global Test_udivby10

   .text
   .align 2
// **test of udivby10**
// since udivby10 is not AAPCS compliant, we must test it in assembly
Test_udivby10:
   PUSH {LR}

   MOVS R0,#123
   BL   udivby10
// put a breakpoint here
// R0 should equal 12 (0x0C)
// R1 should equal 3

   LDR R0,=12345
   BL   udivby10
// put a breakpoint here
// R0 should equal 1234 (0x4D2)
// R1 should equal 5

   MOVS R0,#0
   BL   udivby10
// put a breakpoint here
// R0 should equal 0
// R1 should equal 0
   POP {PC}

// ****************************************************
// divisor=10
// Inputs: R0 is 16-bit dividend
// quotient*10 + remainder = dividend
// Output: R0 is 16-bit quotient=dividend/10
//         R1 is 16-bit remainder=dividend%10 (modulus)
// not AAPCS compliant because it returns two values
udivby10:
   PUSH {R4-R7, LR}

   MOVS R7, R0 // r7 = n
   MOVS R0, #0 // r0 = quotient
   MOVS R1, #0 // r1 = remainder
   MOVS R2, #10 // r2 = d
   MOVS R3, #16 // r3 = i, 16 bits

udivby10Loop:
   CMP R3, #0
   BLT done
   LSLS R1, #1
   
   MOVS R4, R7
   LSRS R4, R3
   MOVS R5, #1
   ANDS R4, R5
   ORRS R1, R4

   CMP R1, R2
   BLT skip
   SUBS R1, R2
   MOVS R5, #1
   LSLS R5, R3
   ORRS R0, R5
   
skip:
   SUBS R3, #1
   B udivby10Loop
   
done:
   POP  {R4-R7, PC}

  
//-----------------------OutDec-----------------------
// Convert a 16-bit number into unsigned decimal format
// Call the function OutChar to output each character
// You will call OutChar 1 to 5 times
// OutChar does not do actual output, OutChar does virtual output used by the grader
// Input: R0 (call by value) 16-bit unsigned number
// Output: none
// Invariables: This function must not permanently modify registers R4 to R11

.equ char1, 0
.equ char2, 4
.equ char3, 8
.equ char4, 12
.equ char5, 16           // Binding

OutDec2:
   PUSH {R4-R7, LR}

   SUB SP, #20           // Allocation
   MOV R7, SP

   LDR R4, =char5

OutDecDivideLoop:
   BL udivby10
   ADDS R1, #48
   STRB R1, [R7, R4]    // Access
   
   CMP R0, #0
   BEQ OutDecOutChar
   
   SUBS R4, #4
   B OutDecDivideLoop

OutDecOutChar:
   CMP R4, #char5
   BGT OutDecDone
   
   LDRB R0, [R7, R4]    // Access
   BL OutChar
   ADDS R4, #4
   B OutDecOutChar

OutDecDone:
   ADD SP, #20           // Deallocation
   POP  {R4-R7, PC}
   
// * * * * * * * * End of OutDec * * * * * * * *

// ECE319H recursive version
// Call the function OutChar to output each character
// You will call OutChar 1 to 5 times
// Input: R0 (call by value) 16-bit unsigned number
// Output: none
// Invariables: This function must not permanently modify registers R4 to R11

.equ digit, 0              // BINDING

OutDec:
   CMP R0, #0
   BNE OutDecBody
   PUSH {LR}
   MOVS R0, #48
   BL OutChar
   POP {PC}

OutDecBody:
   PUSH {R7, LR}
   SUB SP, #4              // ALLOCATION
   MOV R7, SP

   CMP R0, #0
   BEQ Base

   BL udivby10
   STRH R1, [R7, #digit]   // ACCESS
   BL OutDecBody
   
   LDRH R0, [R7, #digit]   // ACCESS
   ADDS R0, #48
   BL OutChar

Base:
   ADD SP, #4              // DEALLOCATION
   POP {R7, PC}

     .end
