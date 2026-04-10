// YYYYYExam2ASMPartYYYYY.s
// ECE319K/ECE319H Exam2, Spring 2025
// ***Put your name here***
// This is the assembly Part of Exam 2 (See YYYYYExam2CPartYYYYY.c for C part)
// The assembly part is not related to the C part
     .text
     .align 2 
     .global SwapIJ    //.global means my grader can call your SwapIJ

//*************Question 1 (of 3) worth 30 points*************
// Assembly Subroutine Swap
// Given an array of numbers
// Version 0: Input array elements are Signed 16-bit Integers
// Version 1: Input array elements are Unsigned 16-bit Integers
// Version 2: Input array elements are Signed 32-bit Integers
// Version 2: Input array elements are Unsigned 32-bit Integers
// with a sentinel of 0. Swap the elements at index i and j
// Inputs: 1. Array of numbers
//     	   2. index i is an unsigned 8-bit number
//     	   3. index j is an unsigned 8-bit number
// Output: if i or j are invalid indexes then return -1
//     	otherwise return the length of the array (not including the sentinel)
// Your subroutine MUST comply with AAPCS
// *** 5 Testcases NOT shown but will be displayed if you fail a testcase ****
SwapIJ:
  // you write this
  MOVS R0, #42         // Remove this line
    BX LR

   .end
		 
