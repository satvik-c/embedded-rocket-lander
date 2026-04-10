// WWWWWExam2ASMPartWWWWW.s
// ECE319K/ECE319H Exam2, Fall 2024
// ***Satvik Chawla***
// This is the assembly Part of Exam 2 (See WWWWWExam2CPartWWWWW.c for C part)
// The assembly part is not related to the C part
     .text
     .align 2 
     .global DAC4_Out  //.global means my grader can call your DAC4_Out
     .global Rotate    //.global means my grader can call your Rotate

 .equ GPIOB_DOUT31_0,0x400A3280
// *************Question 1 (of 4) worth 30 points*************
// Assume all Port B pins are already initialized as output pins
// A four-bit DAC is already connected to your four pins
// Your version number is shown in terminal window
// Input: R0 is a four-bit number 0 to 15
//                   Version 0 Version1 Version2 Version3
// MSB R0 bit 3 into   PB5      PB6      PB7      PB8
//     R0 bit 2 into   PB4      PB5      PB6      PB7
//     R0 bit 1 into   PB1      PB1      PB1      PB1
// LSB R0 bit 0 into   PB0      PB0      PB0      PB0
// Output: no formal output parameter
// Write to your four bits in GPIOB_DOUT31_0 in a friendly manner
// Your subroutine MUST comply with AAPCS
DAC4_Out:
// you write this


    BX LR



//*************Question 4 (of 4) worth 10 points*************
// Left-wise rotate the numbers in a buffer, k positions
// Inputs: R0 is a pointer to a buffer of size N, unsigned integers
//         R1=k is the number of positions to rotate
// Output: no formal return parameter,
// The number of bits (8, 16, 32) is given in the terminal window
// The size N for your exam is given in the terminal window
// Rotate the data in the buffer to the left in place
// Your subroutine MUST comply with AAPCS
// Return without changing the buffer if k is not between 1 and N-1
// Some examples given in the terminal window
// Hint: implement a subfunction, Rot1, which rotates the buffer once
// Hint: there is no need to optimize for speed
Rotate:
// you write this


    BX LR

//*** Rot1 is not required/graded, but suggested ***
// Left-wise rotate the numbers in a buffer once
// Inputs: R0 is a pointer to a buffer same format as Rotate
// Output: no formal return parameter,
Rot1:
// you write this


    BX   LR

   .end
		 
