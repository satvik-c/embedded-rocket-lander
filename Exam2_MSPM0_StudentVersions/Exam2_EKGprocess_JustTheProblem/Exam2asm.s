//Exam2AsmPart.s  
// EE319K Fall 2018 exam 2, November 8, 2018
// ***Put your name here***
// -5 points if you do not add your name
// This is the assembly Part of the Exam (See Exam2CPart.c for the C part)
// You have to complete two subroutines in assembly: IsItAnRwave

   .text
   .align 2
    
    .global  IsItAnRwave
    .global  CountOutofRange
        
     
//*** Question 1 *************
// You are given three EKG data points and 
//   you return a true if the three points signify an R wave. 
//   Let n0,n1,n2 be three signed 32-bit numbers
//   It is an R wave if ((n1-n0) > +1000) and ((n2-n1) < -1000)
// Inputs: R0 is n0, R1 is n1, R2 is n2   
// Output: R0 should be returned as true=1 or false=0
// Note: the grader will run many test cases, here are only a few
//    n0       n1     n2       n1-n0     n2-n1    return
//     0    +2000      0      +2000     -2000     true
//     0    +2000  +1000      +2000     -1000     false
//  -100    +1000  -1000      +1100     -2000     true
//  -100    -1000   1000       -900     +2000     false
// you must satisfy AAPCS 
IsItAnRwave:
   
     MOVS R0,#42 // delete this line and replace with solution
     BX   LR


//*** Question 2  *************
// You are given a variable-length array of 16-bit unsigned data and 
//    you will return the number of out of range values 
// In range values are 0 to 4095
// Out of range values are greater than 4095
// Inputs: R0 is pointer to the array
//         R1 is the size (number of values in the array)
// Output: R0 should be returned with number of out of range values
// Note: the grader will run many test cases, here are only a few
//    array                      size    return
//  1000, 2000,4095,4096,4097     5       2
// 10000,40000,0,1,2,6,50000,10   8       3
// 0,1,2,3,4,5,6,7,8,9,10,11,12   13      0
// 4096,50000,50000,60000         4       4
//                                0       0
// you must satisfy AAPCS
CountOutofRange:
          
     MOVS R0,#42 // delete this line and replace with solution
     BX   LR

     .end                             // end of file
        