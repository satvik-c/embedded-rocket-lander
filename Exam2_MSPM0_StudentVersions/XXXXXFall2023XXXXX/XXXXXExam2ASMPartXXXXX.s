// XXXXXExam2ASMPartXXXXX.s
// ECE319K/ECE319H Exam2, Fall 2023
// ***Put your name here***
// This is the assembly Part of Exam 2 (See XXXXXExam2CPartXXXXX.c for C part)
// The assembly part is not related to the C part
// The assembly part has two functions
     .text
     .align 2

//*************Question 1 (of 4) worth 20 points*************
//***********upper**************
// Convert lower case ASCII to upper case ASCII
// Input parameter: R0 is input character
//   if 'a'  <= R0 <= 'z'  subtract 0x20 from R0 (converting it to upper case)
//   if 0x61 <= R0 <= 0x7A subtract 0x20 from R0 (converting it to upper case)
//   otherwise return R0 unchanged.
// You may assume the input R0 is between 0x01 and 0xFF
// Output parameter: return R0 with the converted ASCII character
// Your subroutine MUST comply with AAPCS
    .global upper //.global means my grader can call your upper
upper: // put your code here
     MOVS R0,#128 // remove this line
     BX   LR

     .global OutChar //.global means your code can call my OutChar
// the C prototype for OutChar is
//      void OutChar(char letter);
// where letter is an ASCII character 0x01 to 0xFF
// Do not write OutChar, it is in the grader
// OutChar will comply with AAPCS

//*************Question 2 (of 4) worth 20 points*************
//***********OutString**************
// 1) Read the characters from the string one by one
//    a) Convert upper case to lower case by calling your upper function
//    b) Output the character to the device by calling my OutChar function
// 2) Return the number of characters in the string
// Input parameter:
//    R0=pt   pointer to an 8-bit unsigned character string
//            The string is null-terminated
// Output parameter: return R0 number of characters in the string
// Example test cases
// E.g., String pt-> "Jony"
//       You should call OutChar 4 times
//       outputting 'J', 'O', 'N', 'Y' and return R0=4
// E.g., String pt-> "ece319k"
//       You should call OutChar 7 times
//       outputting 'E', 'C', 'E', '3', '1', '9', 'K' and return R0=7
// E.g., String pt-> ""
//       Output nothing and return R0=0

// Actual test cases will appear in the UART window when you run
// Your subroutine MUST comply with AAPCS
// Note: do not output the null(0)
// Note: local variables need NOT be on the stack,
//       you may put local variables in registers
     .global OutString //.global means my grader can call your OutString
OutString:   // put your code here


     MOVS R0,#42 //remove this line
     BX  LR


     .end
