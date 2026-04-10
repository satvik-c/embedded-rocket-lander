// ****Your name goes here******* 
// -5 points if you do not add your name

// Exam2.c November 24, 2020
// This is the C Part of the Exam (See Exam2asm.s for the assembly part)

#include <stdint.h>
char EID[] = "Your EID";

// find the maximum even number
// Input: p is a pointer to a variable length array of signed 8 bit numbers
// the array has a termination value of -128 (-128 is not data)
// Output: largest even number in the array
// p => {0,10,7,3,1,0,19,8,1,-128}, return 10 (not 19)
// p => {-128},                     return -128 (empty)
// p => {-1,5,11,15,3,-128},        return -128, (no even numbers)
// Plus 14 randomly selected arrays
int8_t MaxEven(int8_t *p){
  // write this code
  // put your answer here
   return 42; // replace this line with solution
}

// five possible cube colors 
#define BLACK 0x0000 // RGB 0000,0000,0000,0000
#define RED   0xF800 // RGB 1111,1000,0000,0000
#define GREEN 0x07E0 // RGB 0000,0111,1110,0000
#define BLUE  0x001F // RGB 0000,0000,0001,1111
#define WHITE 0xFFFF // RGB 1111,1111,1111,1111
struct cube{
  uint16_t color; // 16-bit color, 5 possibilities
  int16_t x1,y1,z1;       // one corner
  int16_t x2,y2,z2;       // opposite corner
};
typedef struct cube cube_t;

// *******************SignedVolume******************
// Calculate the signed volume of a cube, signed
// Volume = (x1-x2)*(y1-y2)*(z1-z2)
// The numbers will be small enough so you 
//   can neglect the possibility of overflow
// Input:  a cube object
// Output: signed volume of the cube
// Error conditions: none (although the volume may be zero)
// test data
// corner opposite  volume 
// (1,2,3) (4,6,8)  V=(1-4)*(2-6)*(3-8) = -3*-4*-5 = -60
// (1,2,3) (-4,2,0) V=(1+4)*(2-2)*(3-0) = 5*0*3=0
// other test cases randomly generated with coordinate values from -9 to +9
int32_t SignedVolume(cube_t obj){ 
  // write this code
  // put your answer here
   return 42; // replace this line with solution
}

// **************SameVolumeRed****************
// Search an array of cubes for red cubes with the same signed volume. 
// A match means two or more red cubes have the same signed volume.
// Return the largest signed volume of matching cubes
// Input:  pt is  apointer to an array of cube_t objects
//         size is the number of objects in the array
// Output: largest volume of matching cubes
// Error conditions: return -2147483648 if there are not two or more red cubes with the same volume
//                   return -2147483648 if the array is empty
//------------------------------------------------------------------
//Case 1: four cubes; 3 reds and a blue
// {RED, (1,2,3) (4,6,8)},  // volume=-60        
// {BLUE,(1,2,3) (4,6,8)},  // volume=-60        
// {RED, (1,2,3) (2,3,5)},  // volume=-2        
// {RED, (3,4,4) (2,2,3)},  // volume=-2        
//}  Return -2
//
//------------------------------------------------------------------
//Case 2: five cubes; 3 reds and two blacks
// {RED, (2,2,4) (3,-2,3)},  // volume=-4        
// {BLACK,(3,2,3) (1,6,8)},  // volume=40        
// {BLACK,(4,3,3) (2,7,8)},  // volume=40        
// {RED, (-1,3,3)(9,2,4)},  // volume=10        
// {RED, (0,2,4) (-1,-2,5)},// volume=-4        
//} Return -4
//
//-------------------------------------------------------------------
//Case 3: five cubes; 5 reds 
// {RED, (-2,2,4)(3,-2,3)},  // volume=-20        
// {RED, (1,2,3) (3,6,8)},   // volume=-40        
// {RED, (2,3,8) (4,8,3)},   // volume=50        
// {RED, (-1,2,4)(9,3,3)},   // volume=10        
// {RED, (1,2,3) (1,-2,5)},  // volume=0        
//} Return -2147483648 (no matches)
// more test cases with values -9 to +9
// YOU CAN CALL YOUR SignedVolume FUNCTION, but do not have to call it
//------------------------------------------------------------------
int32_t SameVolumeRed(cube_t students[], unsigned long size){
  // put your answer here
  return 42; // replace this line with your solution
}

