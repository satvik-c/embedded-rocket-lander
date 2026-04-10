// Exam2ASMPart.s
// ECE319K/ECE319H Exam2, Fall 2022
// ***Put your name here***
// This is the assembly Part of Exam 2 (See Exam2ASMPart.c for C part)
// The assembly part is not related to the C part
// The assembly part has one function
     .text
     .align 2
     .global GetNum //.global means your code can call my GetNum

// *************Question 1 (of 3) worth 30 points*************
// ***********Replace**************
// Inputs:
//    R0=pt   holds the address of a 16-bit unsigned array
//    R1=i    is an unsigned integer index
//    R2=port is an unsigned integer 0 to 5
// There is an initial array pointed to by pt
// 1) Call my function to get num=GetNum(port)
//    pass into my function the port number
//    get a num from my GetNum() function
// 2) Replace the number at index i of the array with num
// Output: return R0 = num

// Example test cases
// E.g., Initial array pt-> { 3, 5, 6, 3, 4, 3}, i=2, port=5
//       num = GetNum(5) = 36
//       Final array   pt-> { 3, 5,36, 3, 4, 3} (replaced 6 with 36)
// E.g., Initial array pt-> { 3, 5, 6, 3, 4, 3}, i=0, port=1
//       num = GetNum(1) = 16
//       Final array   pt-> { 3,16, 6, 3, 4, 3} (replaced 5 with 16)
// Actual test cases will appear in the UART window when you run
// Your subroutine MUST comply with AAPCS
// You need not know the length of the array, because
//       you may assume the index i is within the array
// Note: local variables need NOT be on the stack,
//       you may put them in registers

     .global Replace //.global means my code can call your Replace
     
Replace:
     PUSH {R4-R7, LR}

     MOVS R7, R0         // R7 has copy of ptr
     MOVS R6, R1         // R6 has copy of i
     MOVS R0, R2
     BL GetNum           // R0 has final num

     LSLS R6, #1         // R6 = R1*2 (2 byte elemtns)

     STRH R0, [R7, R6]
     

     POP {R4-R7, PC}
      
 
// ***********GetNum**************
// There is a function called GetNum in the grader.
//   You do NOT write GetNum, it is in the grader
//   Your software will call this function once per invocation of Replace
//  Input parameter (you pass port to me)
//    R0 is the port
//  Return parameter (I return num to you)
//    R0 returns to you one number, which is num
//  This function is AAPCS compliant.
//  GetNum may modify registers R1,R2,R3,and R12

     .end
