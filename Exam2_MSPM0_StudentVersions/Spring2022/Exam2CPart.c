/*  Exam2CPart.c
 *****Satvik Chawla*******

 This is EE319K/EE319H Exam2, Spring 2022
 This is the C Part of the Quiz (See Exam2ASMPart.s for the assembly part)
 The C part is not related to the assembly part
 You MUST edit line 11 to specify your EID 

*/   
#include <stdint.h>
const char EID[16] = "sc73994";   // replace abc123 with your EID

/*************Question 2 (of 3) worth 40 points*************
   ************FindFactors****************
 Find all the factors that evenly divide into Number
 See the UART window for further explanation 
  n is evenly divisible by m if n/m has no fractional component
 E.g., 100 is evenly divisible by 20 (100/20 is 5), 
 E.g., 100 is not evenly divisible by 8 (100/8 is 12.5)
 When your function is called the array Factors[] is empty
 Your function will store the factors into the Factors[] array
Inputs:
  Number is a nonzero unsigned integer
  Factors[] is initially an empty array 
Output: Number of factors that you have placed into Factors
Test cases will appear in the UART window when you run */
uint32_t FindFactors(uint32_t Number, uint32_t Factors[]){
  int idx = 0;
  for (int i = 1; i <= Number; i++) {
    if (Number%i == 0) {
      Factors[idx] = i;
      idx++;
    }
  }
  return idx;
}

// *************Question 3 of 3 worth 30 points*************
// Note: please look at the color image on the Canvas page 
struct Point{
  uint8_t x; // ranges from 0 to 15
  uint8_t y; // ranges from 0 to 15
}; 
typedef struct Point Point_t;
struct Rect{
  Point_t topLeft;
  Point_t botRight;
};
typedef struct Rect Rect_t;

/* ************Count_Points****************
Inputs: Shape is a rectangle defined by  topLeft and botRight points
        Points is an array of points
        n is the number of points in the Points array
Output: return the result of the count as specified in the UART window
* is (Shape.topLeft.x, Shape.topLeft.y)
(0,0)                                            (15,0)

        *------------------------------------
        |                                   |
        |                                   |
        |                                   |
        |                                   |
        |                                   |
        ------------------------------------+

(0,15)                                           (15,15)
           + is (Shape.botRight.x, Shape.botRight.y)
Note: top left corner of the entire field position (0,0), 
Note: bottom left corner of the entire field position (15,15), 
Note: the Points array may be empty (n could be 0), in which case return 0
The first test case is shown on the Canvas quiz page
  Shape is {{2,1},{12,8}}
  Points are {0,0},{5,3},{11,2},{1,9},{7,8},{3,7}
  n is 6
  There are 2 points strickly outside the shape {0,0},{1,9},
  There are 3 points strickly inside the shape {5,3},{11,2},{3,7}
  There is 1 point on the shape {7,8}
*/
uint8_t Count_Points(Rect_t Shape, Point_t Points[], uint8_t n){
  int count = 0;
  
  for (int i = 0; i < n; i++) {
    if (Points[i].x > Shape.topLeft.x && Points[i].x < Shape.botRight.x &&
        Points[i].y > Shape.topLeft.y && Points[i].y < Shape.botRight.y) {
          count++;
        }
  }

  return count;
}


