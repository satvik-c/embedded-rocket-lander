// ZZZZExam2ASMPartZZZZ.s
// ECE319K/ECE319H Exam2, Spring 2024
// ***Put your name here***
// This is the assembly Part of Exam 2 (See ZZZZExam2CPartZZZZ.c for C part)
// The assembly part is not related to the C part
     .text
     .align 2 
     .global ReadPort    //.global means your WaitForHigh can call my subroutine ReadPort
     .global WaitForHigh //.global means my grader can call your WaitForHigh
     .global Integrate   //.global means my grader can call your Integrate

// *************In the grader there is a subroutine called ReadPort*************
// input to ReadPort: none
// output from ReadPort: R0 is 32-bit value from the port
// follows AAPCS (it could modify R1,R2,R3) 

//*************WaitForHigh 1 (of 4) worth 20 points*************
// Implement the functionality in assembly
// void WaitForHigh(uint32_t mask){ uint32_t data;
//   do{
//     data = ReadPort()&mask;
//   }
//   while(data == 0);
//  }
// Your subroutine MUST comply with AAPCS
WaitForHigh:
// you write this



    BX LR // you can replace this line if you wish

// the velocity as a function of time is given as v(t)=4*t-1
// Input: R0, signed integer, t in seconds
// Output: R0, signed integer, meters/sec
v: LSLS R0,R0,#2 // 4*t
   SUBS R0,R0,#1 // 4*t-1
   BX   LR

//*************Question 2 (of 4) worth 20 points*************
// Assume the velocity of an object is defined with the function v(t)
// You will integrate v(t) from ti to tf 
// Inputs: R0 is 32-bit signed integer, ti, initial time (seconds)
//         R1 is 32-bit signed integer, tf, final time (seconds)
// Output: R0 = sum(v(ti)+v(ti+1),...,v(tf)), assuming ti<=tf 
//         R0 = 0 if ti>tf
// Your subroutine MUST comply with AAPCS
// Assume no overflow/underflow
// you can either call v(t) above, or copy paste the 4*t-1 function into your solution
// First few test cases (20 total cases will be tested)
// ti  tf  calculations               Result
// 0   1   (4*0-1)+(4*1-1)            -1+3=2
// 2   4   (4*2-1)+(4*3-1)+(4*4-1)    7+11+15=33
// -1  1   (4*(-1)-1)+(4*0-1)+(4*1-1) -5-1+3=-3
// -2  -2  (4*(-2)-1)                 -9
//  2 -2                              0
Integrate:
// you write this


    MOVS R0,#42 // remove this line
    BX LR       // you can replace this line if you wish
	
.end
		 
