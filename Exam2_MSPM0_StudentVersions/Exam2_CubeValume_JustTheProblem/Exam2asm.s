// ****Your name goes here******* 
// Exam2asm.s
// EE319K Fall 2020, Nov 24, 2020
// This is the assembly Part of the Exam (See Exam2.c for the C part)
// You have to complete one subroutine in assembly

    .text
	.align 2
    .global  Sine
    
//******************Sine**************************
//Convert a 3-bit input into a 16-bit output
//The functional relationship is shown in this data
//Input   I    0,   1,    2,   3,4,    5,     6,    7
//Output  J    0,7071,10000,7071,0,-7071,-10000,-7071

//Input: R0 3-bit unsigned number I
//Output: R0 16-bit signed number J
//Error conditions: if the input is not 0-7 return -32768
//Test Cases: shown above (plus some invalid inputs)
//Hint: Create a 16-bit signed array in ROM, and then index into the array
// Warning: must be AAPCS compliant
Sine:
// put your answer here


      
    MOVS   R0,#42   // replace this line with your solution
    BX    LR
    


   .end   // end of file
