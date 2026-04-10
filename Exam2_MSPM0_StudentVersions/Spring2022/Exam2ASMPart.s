// Exam2ASMPart.s
// EE319K/EE319H Exam2, Spring 2022
// ***Satvik Chawla***
// This is the assembly Part of Exam 2 (See Exam2ASMPart.c for C part)
// The assembly part is not related to the C part
// The assembly part has one function
     .text
     .align 2
     .global Func //.global means your code can call my Func

// *************Question 1 (of 3) worth 30 points*************
// ***********Compute**************
// Implement/convert a given C function in/to assembly
// The UART window shows the C version of the function Compute
// XArr is a 32-bit signed array of at least 1 element
// XArr is terminated by a sentinel value of 0
// Input:  R0=>Xarr, holds the address of the array
//         R1=k,     is a 32-bit integer
// Output: R0 holds the computed result
// Error Conditions: none
// The test cases will appear in the UART window when you run
// Your subroutine MUST comply with AAPCS
// Note: local variables need NOT be on the stack,
//       you may put them in registers
     .global Compute //.global means my code can call your Compute
arr .req R6
k .req R7
sum .req R4
idx .req R5
Compute:
     PUSH {R4-R7, LR}

     MOVS arr, R0
     MOVS k, R1
     MOVS sum, #0
     MOVS idx, #0

loopCompute:
     LDR R0, [arr, idx]
     CMP R0, #0
     BEQ done
     MULS R0, k
     BL Func
     ADDS sum, R0
     ADDS idx, #4
     B loopCompute
     
done:
     MOVS R0, sum
     POP {R4-R7, PC}



 
// ***********Func**************
// There is a function called Func in the grader.
//   You do NOT write Func, it is in the grader
//   Your software will call Func multiple times
//   You will pass one 32-bit signed input (R0) into Func
//   Func returns to you one 32-bit signed output (R0)
//   Func is a quadratic equation, but
//     you do not need to know the details of how Func works
//   Its C implementation is int32_t Func(int32_t x){ return ((x-1)*x-5)}//
//   Func is AAPCS compliant.

     .end
