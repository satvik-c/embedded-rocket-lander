/*  Exam2CPart.c
 *****Satvik Chawla*******

 This is EE319K/EE319H Exam2, Spring 2021
 This is the C Part of the Quiz (See Exam2ASMPart.s for the assembly part)
 The C part is not related to the assembly part
 You MUST edit line 11 to specify your EID using lower case letters

*/   
#include <stdint.h>
const char EID[10] = "sc73994";   // replace abc123 with your EID
/****************** FindM ****************************
// Question 2: Find the highest base raised to the exponent n that is 
// less than or equal to x (m^n <= x). Solve for m and return its value.
// You are given two numbers x and n
// Your function should find the
//       largest integer m such
//       m^n is less than or equal to x
// Input:  x is a 32-bit unsigned value
//         n is a 32-bit unsigned value
// Output: 32-bit value m, where m^n <= x
// Error conditions: None
// Test Cases:
//(Only the test cases seen below will be tested by the grader for this question)
// x = 1000, n = 3: m = 10   (note: m^n = 10^3 = 1000)
// x = 16, n = 2: m = 4      (note: m^n = 4^2 = 16)
// x = 250, n = 3: m = 6     (note: m^n = 6^3 = 216)
// x = 12345, n = 4: m = 10  (note: m^n = 10^4 = 10000)
// x = 5, n = 5: m = 1       (note: m^n = 1^5 = 1)
// x = 5, n=10; m = 1        (note: m^n = 1^10 = 1)
*/

uint32_t findExp(int base, int power) {
  int result = 1;
  for (int i = 0; i < power; i++) {
    result *= base;
  }
  return result;
}

uint32_t FindM(uint32_t x, uint32_t n){
  int m;
  for (m = 0; findExp(m, n) <= x; m++) {}
  return m-1;
}


// Each Person has two attributes: 
//    ID - Identity that is different from their INDEX in the Group array
//    Debts - An array of INDEXES of people who owe the person money
//            The array is variable length terminated with sentinel=99
//    Notes: 1. This is not an array of IDs of people, Nor is it the amount owed
//           2. No person owes themself money (a person's INDEX will not be present in their own debt array)
struct person{      
  uint32_t ID;         // unique ID of this person
  uint8_t Debts[16];   // INDEXES of people who owe this person money
};
typedef const struct person person_t;
/****************** DebtFree ****************************
Question 3: Evaluate a group of people and find someone who has no debt 
That is, find the person whose INDEX is not present in anybody else's Debts array
Each person is located at an INDEX in the array Group. 
Each person has an INDEX from 0 to NumPeople-1 (this is unrelated to their ID)
Inputs: Group is an array of type person_t
        NumPeople is the number of people in the Group
        Assume NumPeople is 1 to 16
Output: Return the ID of a person with no debt (Not the INDEX)
        If more than one person is debt free, return any of their IDs (see case 3)
        Return 9999 if no one is debt free (see case 2)
Test Cases:
(Only the test cases seen below will be tested by the grader for this question)
1. NumPeople=3,Group={{100,{1,99}},{200,{2,99}},{300,{1,99}}}   DebtFree =100 (at index 0)
2. NumPeople=4,Group={{400,{1,2,99}},{401,{0,99}},{402,{3,99}},{403,{99}}} DebtFree =9999 (no one)
3. NumPeople=2,Group={{500,{99}},{501,{99}}}  DebtFree = 500 or 501 (at indices 0 or 1)
4. NumPeople=5,Group={{605,{3,99}},{601,{4,3,99}},{602,{3,4,0,99}},{603,{3,99}},{606,{1,99}}} DebtFree =602 (at index 2)
5. NumPeople=1,Group={{703,{99}}} DebtFree =703 (at index 0)
*/
uint32_t DebtFree(person_t Group[],uint32_t NumPeople){
  int occurences[100];
  for (int i = 0; i < 100; i++) occurences[i] = 0;
  int idx = 0;

  for (int i = 0; i < NumPeople; i++) {
    for (int j = 0; Group[i].Debts[j] != 99; j++) {
      occurences[idx] = Group[i].Debts[j];
      idx++;
    }
  }

  int i, j;
  for (i = 0; i < NumPeople; i++) {
    int found = 0;
    for (j = 0; j < idx; j++) {
      if (occurences[j] == i) {
        found = 1;
        break;
      }
    }
    if (!found) return Group[i].ID;
  }

  return 9999;

}
