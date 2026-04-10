/*  Exam2CPart.c
 *****Your name goes here*******

 This is ECE319K/ECE319H Exam2, Fall 2022
 This is the C Part of the Quiz (See Exam2ASMPart.s for the assembly part)
 The C part is not related to the assembly part
 You MUST edit line 11 to specify your EID 

*/   
#include <stdint.h>
const char EID[16] = "sc73994";   // replace abc123 with your EID

/*************Question 2 (of 3) worth 40 points*************
   ************String2Decimal****************
 Convert an ASCII string to decimal
 ASCII strings are terminated with 0
 Each ASCII character is 8 bits
 ASCII character '0' is 0x30, and '9' is 0x39
Input: p is a pointer to an ASCII string
Output: Decimal value of that string
Normal cases:
p-> "1234"       return 1234
p-> "987"        return 987
p-> "4000000000" return 4000000000
p-> ""           return 0
p-> "123a456"    see UART window
p-> "z12456"     see UART window
p-> "1z2b56"     see UART window
Do not worry about values above 4294967294 */
// mode=0, if any input character is not '0' to '9' return 4294967295
// mode=1, if any input character is not '0' to '9' return the value prior to that character
// mode=2, if any input character is not '0' to '9' ignore it
uint32_t String2Decimal(char p[]){

  int i;
  // for (i = 0; p[i] != 0; i++) {}
  // i = i-1;    // now i is index of last digit

  int num = 0;
  
  for (i = 0; p[i] != 0; i++) {
    if (p[i] < '0' || p[i] > '9') return 4294967295;
    num += (p[i] - '0');

    if (p[i+1] != 0) num *= 10;
  }

  return num;

}

// *************Question 3 of 3 worth 30 points*************
struct Pixel{
  uint32_t x,y;      
  uint32_t size;     
  uint32_t color;}; 
typedef const struct Pixel Pixel_t;

/* ************FindCommonColor****************
  You are passed two arrays of pixels 
Inputs:   
  m1 is the first array of pixels.
  n1 is the number of elements in m1. 
  m2 is the second array of pixels. 
  n2 is the number of elements in m2. 
Output: common color
  Search both arrays looking for any pixel color that exists in both arrays. 
  If the same color value is found in both arrays, return that color value. 
  If more than one color value exists in both, you may return either value. 
  If the arrays do not share any common color, see UART window. 
  If either or both the arrays are empty, see UART window. 
Example
  m1={{0,0,1,88}},n1=1,           m2={{4,5,6,45},{1,2,3,88},{4,5,1,75}},n2=3 return 88
  m1={{5,4,3,55},{1,2,3,75}},n1=2,m2={{4,5,6,45},{9,3,5,70},{4,5,1,75},{7,6,1,55}},n2=4 return 55 or 75
*/
uint32_t FindCommonColor(Pixel_t m1[], uint32_t n1, Pixel_t m2[], uint32_t n2){

  if (n1 == 0 || n2 == 0) return 0;
  
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < n2; j++) {
      if (m1[i].color == m2[j].color) return m1[i].color;
    }
  }

  return 0;

}


