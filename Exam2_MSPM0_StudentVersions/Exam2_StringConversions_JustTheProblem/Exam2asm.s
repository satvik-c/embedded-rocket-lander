//Exam2AsmPart.s  
// EE319K Spring 2018 exam 2, April 6, 2018
// ***Put your name here***
// -5 points if you do not add your name
// This is the assembly Part of the Exam (See Exam2CPart.c for the C part)
// You have to complete one subroutine in assembly: String2Octal

    .text
	.align 2
    
    .global  String2Octal
        
// Octal means base 8, with digits 0-7
// ASCII '0' is 0x30
//       '1' is 0x31
// ...
//       '7' is 0x37
    
     
//*** Question 2 ***** String2Octal **********
// Accepts a null-terminated string of ASCII octal digits
// and calculates the unsigned integer value represented by those digits
// Input: R0 is a pointer to a null-terminated ASCII string 
//        each ASCII character is an 8-bit number from 0 to 127
// Output: R0 should be returned as the unsigned 32-bit value
//         return 0xFFFFFFFF if any character in the string is not an octal digit
//         return 0xFFFFFFFF if the numerical result of the conversion exceeds 65535
// Note: the grader will run many test cases, there are only a few of them
// input string                     description    return
// 0x35,0                           "5"            5 
// 0x31,0x32,0                      "12"           10 
// 0x33,0x37,0x31,0                 "371"          249 
// 0x30,0x35,0x34,0x32,0x31,0       "05421"        2833
// 0x31,0x37,0x37,0x37,0x37,0x37,0  "177777"       65535
// 0x32,0x30,0x30,0x30,0x30,0x30,0  "200000"       0xFFFFFFFF
// 0x38,0x34,0                      "84"           0xFFFFFFFF
// 0x33,0x2C,0x31,0                 "3,1"          0xFFFFFFFF
// 0                                null string    0
String2Octal:



     MOVS R0,#42 // delete this line and replace with solution

     BX   LR

    .end                            // end of file
	