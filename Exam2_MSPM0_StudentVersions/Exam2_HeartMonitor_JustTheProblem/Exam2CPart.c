// File: Exam2CPart.c
// ****Your name goes here*******
// -5 points if you do not add your name
// This is Exam2
// EE319K Fall 2017 exam 2, November 8, 2017
// This is the C Part of the Exam (See Exam2AsmPart.s for the assembly part)  
#include <stdint.h>

// find the range of twelve 8-bit signed numbers
// input: pointer to array of twelve 8-bit signed numbers
// output: range of values in array
// range = maximum-minimum, which will always be positive
// range could be as large as 255 = +127 - -128
// test cases
//{  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12} returns Range = 11
//{ -2, -4, -6, -8,-10,-12,-14,-16,-18,-20,-22,-24} returns Range = 22
//{  1,  2,  7,-10,  3,-80,  0, 10,  2, 33, 60,  0} returns Range = 140
//{  1,  2,  7,-10,  3,-80,  0, 10,  2, 33, 40, 50} returns Range = 130
//{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2} returns Range = 0
int32_t Range(int8_t *p){ 
 return 42; // replace this line with solution
}

struct record{
  uint8_t Age;      // in years
  uint8_t Weight;   // in pounds
  uint8_t Size;     // number of resting heart rate measurements in Rate[]
  uint8_t Rate[10]; // 0 to 10 resting heart rate measurements (BPM)
}; // the Rate[] index goes from 0 to 9, but Size goes from 0 to 10
typedef struct record record_t;

// find the average resting heart rate for a person
// if Size is 0, return 255
// first test case has Size = 5, Rate = {60,61,62,62,60} returns FindResting = 61
// second, third, fourth test cases are randomly generated
// last test case has Size = 0, returns FindResting = 255 (error)
uint8_t FindResting(record_t person){
  
 return 42; // replace this line with solution
}




