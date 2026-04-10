//This is Exam2_Mode8
// Satvik Chawla
//You edit Exam2ASMPart.s and Exam2CPart.c files only
       .data
       .align 2
//put RAM variables here
    
      .text
      .align 2
// ***** Size subroutine*********************
//Determines the number of elements in a variable-length array
//Input:   R0 has a pointer to the array of 8-bit numbers
//Output:  R0 is returned as the number of data elements in the array
//Invariables: You must not permanently modify registers R4 to R11
//Error conditions: none
//Test cases
//Array1 .byte 3,1,2,3      //size = 3
//Array2 .byte 0xA0,1...    //size = 0xA0=160
//Array3 .byte 0            //size = 0
// first element is the size
      .global Size
Size:
      MOVS R3, #0
      LDRB R1, [R0, #0]
      CMP R1, #0
      BEQ sizeDone
      
      

sizeDone:
      MOVS R0, R3
      BX    LR

// ***** Count subroutine*********************
//Determine the number of times that a data value occurs in a given array
//Inputs:  R0 has a pointer to the array of 8-bit unsigned numbers
//         R1 is the 8-bit unsigned data value
//Output:  R0 is the number of times the data value occurs in the array
//Invariables: You must not permanently modify registers R4 to R11
//Error conditions: none
//Test cases
//Array1 .byte 3,1,2,3             //Data=4   Count=0 (4 occurs 0 times)
//Array2 .byte 5,12,13,4,12,3      //Data=12  Count=2 (12 occurs twice)
//Array3 .byte 12,1,1,1,2,1,1,2,1,2,1,2,1,1,1      //Data=1  Count=8 (1 occurs 8 times)
//Array4 .byte 9,30,30,30,30,30,30,30,30,30  //Data=30  Count=9 (30 occurs 9 times)
//Array5 .byte 7,50,10,50,10,50,0,0 //Data=50   Count=3 (50 occurs 3 times)
//Array6 .byte 0           //Data=0 Count=0 (0 does not occur in the empty array)
// first element is the size

      .global Count
Count:
// put your code here
  MOVS R2,#42   // remove this line

      BX   LR

      .end
      
