/*  ZZZZExam2CPartZZZZ.c
 *****Your name goes here*******

 This is ECE319K/ECE319H Exam2, Spring 2024
 This is the C Part of the Quiz (See ZZZZExam2ASMPartZZZZ.s for the assembly part)
 The C part is not related to the assembly part
 You MUST edit line 11 to specify your EID 

*/   
#include <stdint.h>
const char EID[16] = "abc123";   // replace abc123 with your EID

/*************Question 3 (of 4) worth 40 points*************
 ************CombineSound****************
 Concatenate the first sound with the second, storing the new sound into dest
 Each sound is an array of 16-bit integers, terminated with -1
Inputs: first, a sound array, terminated with -1
	    second, a sound array, terminated with -1
        size, total available halfwords (16 bit each) in dest array
        dest, sound array initially containing garbage, into which you will store the new sound
Output: 0 if first and second will not fit into dest (including Sentinel)
        1 if successful concatenation
Example cases (10 total cases will be tested):
  first      second   size  dest           return
  {0,2,3,-1} {4,5,-1}  16   {0,2,3,4,5,-1} 1   
  {-1}       {6,7,-1}  10   {6,7,-1}       1  
  {8,-1}     {-1}       4   {8,-1}         1  
  {1,2,3,-1} {0,5,-1}   5   unchanged      0   (5 data values needs 6 spaces)
Note: add the -1 termination to the concatenated sound (if room)
*/
int CombineSound(const int16_t first[], const int16_t second[], const int32_t size, int16_t dest[]){
// put your code here

 return 42; // remove this line
}

// *************Question 4 of 4 worth 20 points*************
// There is an array of records
struct record{
  uint32_t ID;     // Identification key
  uint32_t Value;  // Numerical value
}; 
typedef const struct record record_t;
// inputs: rec is an array of record_t
//         size is the number of records in the array rec
//         key is an identification key (nonzero)
// output: search the array of records to find the record with key matching ID,
//         return the corresponding Value for this record
// if there is more than one match, return the Value of the first one found
// if there is no ID that matches key, return 0 
// examples (6 total cases will be tested)
// rec                       size  key return explanation
// {{1,5},{4,6},{7,2}}        3     4    6    record {4,6} has ID=4
// {{8,3},{1,9},{9,9},{4,2}}  4     4    2    record {4,2} has ID=4
// {{3,2},{8,3},{9,5},{7,6}}  4     5    0    no record with ID=5
// {}                         0     7    0    array was empty
uint32_t FindValue(record_t rec[], uint32_t size, uint32_t key){
  // put your code here

  return 42; // remove this line
}


