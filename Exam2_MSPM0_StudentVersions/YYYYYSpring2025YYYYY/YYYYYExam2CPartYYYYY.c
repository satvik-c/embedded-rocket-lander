/*  YYYYYExam2CPartYYYYY.c
 *****Your name goes here*******

 This is ECE319K/ECE319H Exam2, Spring 2025
 This is the C Part of the Quiz (See YYYYYExam2ASMPartYYYYY.s for the assembly part)
 The C part is not related to the assembly part
 You MUST edit line 11 to specify your EID 

*/   
#include <stdint.h>
const char EID[16] = "abc123";   // replace abc123 with your EID

//************Question 2 (of 3) worth 40 points*************
// Write a Function that checks if the letters needed to form 
// a given word are all present in a given set of tiles.
// If all letters are present then put the length of the word
// in the location passed as pointer (*score) otherwise put zero. 
// Also return success/valid (1) or failure/invalid (0) 
// Inputs:
//	tiles[] is a null-terminated string of letters to use
//	word[] is a null-terminated string containing the word to check
//   *score is a call-by-reference parameter 
// Output:
//   Return 1 if word is valid else return 0 (invalid)
// Testcases (These are the ONLY test cases)
// Case 0: Inputs: tiles[] = "TOAG"; word[] = "TAG"
//         Output: 1; score of 3 (3 letters needed to make "TAG" are all in "TOAG"
// Case 1: Inputs:  tiles[] = "TOAG"; word[] = "TOT"
//        Output:  0; score of 0 ("TOT" needs 2 T’s,  "TOAG" has only one T
// Case 2: Inputs: tiles[] = "UACCREZP"; word[] = "RACE"
//        Output: 1; score of 4 (letters needed to make "RACE" are all in "UACCREZP")
// Case 3: Inputs: tiles[] = "UACCREZP"; word[] = "ACCRUE"
//        Output: 1; score of 6 (letters needed to make "ACCRUE" are all in "UACCREZP"
// Case 4: Inputs: tiles[] = "STRESSED"; word[] = "DESSERTS"
//        Output: 1; score of 8 (letters needed to make "DESSERTS" are all in "STRESSED"

uint8_t IsScrabble(const char tiles[], const char word[], uint8_t *score){
// you write this
  return 42;     // Remove this line
}

// Student record
struct Student {
  uint8_t id;   // unique value set by grader
  uint8_t score; // unique value set by grader
  uint8_t rank;  // you fill these in (1 means highest score)
};
typedef struct Student Student_t;

//************Question 3 (of 3) worth 30 points*************
// Write a Function that Computes and Updates the
// rank of each student in the array
// of students passed as input.
// Rank ranges between 1 to N;
// Highest scoring student has a rank of 1 
// The size of the array N is given. 
// Assume all scores are unique.
// Inputs: InArr is an array of Student_t Records
//     	   N is the length of InArr
// Output: Version 0: Return, Id of the student with the highest rank
//         Version 1: Return, Score of the student with the highest rank
//         For both versions, Return 0 if array is empty
// Hint: The rank of a student X is 
//       N-(how many have a score less than student X)
// *** 5 Testcases NOT shown here but will be displayed if you fail a testcase ****
uint8_t ComputeRanks(Student_t InArr[], uint8_t N){
// you write this
  return 42;     // Remove this line

}




