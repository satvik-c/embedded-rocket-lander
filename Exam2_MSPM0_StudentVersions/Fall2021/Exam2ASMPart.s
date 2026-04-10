// Exam2ASMPart.s
// EE319K/EE319H Exam2, Fall 2021
// ***Satvik Chawla***
// This is the assembly Part of the Exam 2 (See Exam2ASMPart.c for the C part)
// The assembly part is not related to the C part
// The assembly part has one function


        .global  SearchForRepeatedValue

     .text
     .align 2
// ***********SearchForRepeatedValue**************
// Question 1: You are passed a pointer to a variable-length
//   array of signed integers terminated by a sentinel of -1
// The array length can be between 0 and 20
// The UART window will reveal whether your signed data is 8, 16, or 32 bits
// Find and return the first value in the array
//   that is repeated at least 4 times in a row
// Input:  R0 holds the address of the array
// Output: R0 holds the value found
// Error Conditions:
//  If the array length is zero, return R0 = -1
//  If no element is repeated 4 times return R0 = -1
// The first few test cases are:
// R0 points to {-5,-5,6,6,6,6,-1}//       Output R0 = 6  (6 is repeated 4 times)
// R0 points to {5,5,5,5,0,6,6,6,6,-1}//   Output R0 = 5  (5 occurs before 6)
// R0 points to {2,4,4,4,6,2,2,2,2,2,-1}// Output R0 = 2  (2 is repeated 5 times)
// R0 points to {7,7,0,7,7,-9,7,-1}//      Output R0 = -1 (7 occurs 4 times but not in a row)
// R0 points to {-1}//                     Output R0 = -1 (empty array)
// 15 more cases are randomly generated
//Must comply with AAPCS, save/restore R4-R11 if used

cnt .req R1
offset .req R2
addr .req R7
prev .req R6
curr .req R5

SearchForRepeatedValue:
   PUSH {R4-R7, LR}

   MOVS cnt, #0
   MOVS offset, #0
   MOVS addr, R0
   LDR R0, =-1
   LDR prev, =-1

incLoop:
   LDR curr, [addr, offset]
   CMP curr, R0
   BEQ done

   CMP curr, prev
   BNE skip
   ADDS cnt, #1
   CMP cnt, #3
   BNE skip
   MOVS R0, curr
   B done

skip:
   MOVS prev, curr
   ADDS offset, #4
   B incLoop

done:
   POP {R4-R7, PC}
   .end
        
