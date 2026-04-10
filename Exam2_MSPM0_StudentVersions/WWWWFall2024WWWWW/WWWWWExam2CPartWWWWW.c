/*  WWWWWExam2CPartWWWWW.c
 *****Satvik Chawla*******

 This is ECE319K/ECE319H Exam2, Fall 2024
 This is the C Part of the Quiz (See WWWWWExam2ASMPartWWWWW.s for the assembly part)
 The C part is not related to the assembly part
 You MUST edit line 11 to specify your EID 

*/   
#include <stdint.h>
const char EID[16] = "sc73994";   // replace abc123 with your EID

// convert letters 'a' to 'z' to uppercase 'A' to 'Z'
// other ASCII characters are unchanged
char upper(char in){
  if((in >= 'a')&&(in <= 'z')){
    return in-0x20;
  }
  return in;
}
//************Question 2 (of 4) worth 40 points*************
// Takes two null-terminated strings and returns 1 if equal
// Input: str1 pointer to first string
//        str2 pointer to second string
// Output: TRUE if equal, FALSE if different
// See terminal window for specification of TRUE FALSE
// One or both strings may be empty
// Consider uppercase letters equivalent to lowercase
// Some examples (many cases will be tested)
//  str1     str2    result   explanation
// "Jan 22"  "Jan 2"   FALSE  different lengths
// "jan 5"   "Jan 5"   TRUE
// "July 22" "Jan 22"  FALSE  second letter does not match
// "March 9" "May 9"   FALSE  third letter does not match
// "MAY 9"   "may 9"   TRUE
// ""        ""        TRUE   two empty strings match
int StrCompare(const char str1[], const char str2[]){
  int i = 0;
  while (upper(str1[i]) == upper(str2[i])) {
    if (str1[i] == 0) return 1;
    i++;
  }
  return 0;
}


// *************Question 3 of 4 worth 20 points*************
// There is an array of records
struct record{
  uint32_t ID;        // Identification key
  char Birthday[16];  // birthday, string null terminated
}; 
typedef const struct record record_t;

// inputs: rec is an array of record_t
//         ID=0 is the sentinel (end of array)
// output: search the array of records to find two people with the same birthday,
//         return a simple operation based on the IDs for the two people
//         exactly what operation to perform is shown in the terminal window
// There will be no test cases where the grader gives you three or more matches
// Months will always have exactly three letters
// If there are no two people with the same birthday, return 0
// If the array is empty, return 0
// Some examples (many cases will be tested)
// rec                                                      return explanation
// {{1,"Jan 22"},{4,"Jul 4"},{7,"jan 22"},{0,""}}              f(1,7) (Jan 22)
// {{8,"Nov 10"},{1,"Mar 2"},{9,"Mar 20"},{4,"MAR 2"},{0,""}}  f(1,4) (Mar 2)
// {{3,"Feb 22"},{8,"Jun 6"},{9,"Jan 29"},{7,"Oct 3"},{0,""}}  0    no matches
// {{0,""}}                                                    0    array was empty
// the function f is specified in the terminal window
uint32_t FindMatch(record_t rec[]){
  for (int i = 0; rec[i].ID != 0; i++) {
    for (int j = 0; rec[j].ID != 0; j++) {
      if (j != i && StrCompare(rec[i].Birthday, rec[j].Birthday)) {
        return rec[i].ID + rec[j].ID;
      }
    }
  }
  return 0;
}



