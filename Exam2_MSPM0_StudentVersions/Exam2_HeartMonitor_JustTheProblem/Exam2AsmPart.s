//Exam2AsmPart.s
// EE319K Fall 2017 exam 2, November 8, 2017
// This is the assembly Part of the Exam (See Exam2CPart.c for the C part)
// You have to complete two subroutines in assembly: Size, InZone

    .text
	.align 2
    
    .global  Size
    .global  InZone
        
//******** Size **********
// Count the number of elements in the array
// Inputs: R0 has address of an array of 16-bit signed numbers 
// Outputs: R0 will be returned with the number of elements
// Notes: The variable-length array is terminated with -32768
// test cases
//{1,2,3,-32768}            // returns length is 3
//{0,32767,4,6,5,7,-32768}  // returns length is 6
//{-1,0,4,4,1,5,6,7,-32768} // returns length is 8
//{1,-32768}                // returns length is 1
//{-32768}                  // returns length is 0
Size:
	MOVS  R0,#42
    BX    LR
    
//******** InZone **********
// Determine if you are in the exercise zone
// Let age be your age in years
// Let rest be your resting heart rate in BPM
// Let HR be your current heart rate
// Calculate maximum heart rate, max = 220-age
// Calculate exercise reserve, reserve = max-rest  
// Input: R0 has resting heart rate, rest, in BPM
//        R1 has age in years
//        R2 has current heart rate, HR, in BPM
// Output: R0 has the heart rate classification
//  0 means error,                              HR < rest
//  1 means not in zone,  rest               <= HR < rest+(reserve/2)
//  2 means in zone,      rest+(reserve/2)   <= HR < rest+(3*reserve)/4
//  3 means danger,       rest+(3*reserve)/4 <= HR 
// note: the test cases will have reserve values that are powers of four, so you do not need to worry about rounding
// test cases
//rest  age   max  reserve upper  lower    HR    result
//50    62    158    108    131    104    104    returns 2, in zone (at lower)
//60    20    200    140    165    130    164    returns 2, in zone (one less than upper)
//62    22    198    136    164    130    129    returns 1, not in zone (one less than lower)
//58    26    194    136    160    126    160    returns 3, danger (at upper)
//66    18    202    136    168    134    60     returns 0, error (less than rest)
//66    18    202    136    168    134    61     returns 0, error (less than rest)
//66    18    202    136    168    134    62     returns 0, error (less than rest)
// tests all cases with HR from 63 to 199
//66    18    202    136    168    134    200    returns R0 =3, danger 
//bpm  years  bpm    bpm    bpm    bpm    bpm
InZone:
	MOVS R0,#42
	BX  LR
	
    .end                             // end of file
	