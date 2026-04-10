// ****************** ECE319K_Lab1.s ***************
// Your solution to Lab 1 in assembly code
// Author: Satvik Chawla
// Last Modified: 1/14/2026
// Spring 2026
        .data
        .align 2
// Declare global variables here if needed
// with the .space assembly directive

        .text
        .thumb
        .align 2
        .global EID
EID:    .string "SC73994" // replace ZZZ123 with your EID here

        .global Phase
        .align 2
Phase:  .long 10
// Phase= 0 will display your objective and some of the test cases, 
// Phase= 1 to 5 will run one test case (the ones you have been given)
// Phase= 6 to 7 will run one test case (the inputs you have not been given)
// Phase=10 will run the grader (all cases 1 to 7)
        .global Lab1
// Input: R0 points to the list
// Return: R0 as specified in Lab 1 assignment and terminal window
// According to AAPCS, you must save/restore R4-R7
// If your function calls another function, you must save/restore LR
Lab1: PUSH {R4-R7,LR}

        MOVS    R7, #0
        LDR     R3, =EID
Loop:
        MOVS    R6, #0
        LDR     R1, [R0]
        CMP     R1, #0
        BEQ     MissingEID
NextCharacter:
        LDRB    R2, [R1]
        LDRB    R4, [R3, R6]
        CMP     R2, #0
        BEQ     FoundEID
        CMP     R2, R4
        BNE     NextStudent
        ADDS    R1, #1
        ADDS    R6, #1
        B       NextCharacter
NextStudent:
        ADDS    R7, #1
        ADDS    R0, #8
        B       Loop
FoundEID:
        MOVS    R0, R7
        B       Done
MissingEID:
        MOVS    R0, #0
        SUBS    R0, #1
Done:       

      POP  {R4-R7,PC} // return


        .align 2
        .global myClass
myClass: .long pAB123  // pointer to EID
         .long 95      // Score
         .long pXYZ1   // pointer to EID
         .long 96      // Score
         .long pAB5549 // pointer to EID
         .long 94      // Score
         .long 0       // null pointer means end of list
         .long 0
pAB123:  .string "AB123"
pXYZ1:   .string "XYZ1"
pAB5549: .string "AB5549"
        .end
