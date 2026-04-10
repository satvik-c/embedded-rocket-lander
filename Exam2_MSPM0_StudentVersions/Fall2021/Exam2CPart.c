/*  Exam2CPart.c
 *****Your name goes here*******

 This is EE319K/EE319H Exam2, Fall 2021
 This is the C Part of the Quiz (See Exam2ASMPart.s for the assembly part)
 The C part is not related to the assembly part
 You MUST edit line 11 to specify your EID 

*/   
#include <stdint.h>
const char EID[10] = "sc73994";   // replace abc123 with your EID
struct train{      
  int32_t x;         // coordinate of the front of the train in meters 
  int32_t speed;     // speed in meters/sec
  int32_t length;    // length of train in meters
  int32_t life;      // 0 means inactive, 1 means active
};
typedef struct train train_t;

//***************** Question2 ****************************
// Look at the UART window to see if you solve "Overlapping" or "Touching"
// You are passed as inputs two trains on a straight track
// The front of a train is always on left, and the back on right
// Assume "Overlapping" means they share some non-zero area
//     Trains that simply touch front to back are not overlapping
// Assume "Touching" means the front of one train touches the back of another
//     Trains that overlap with non-zero area are not touching
// No trains have length 0,
// For this question do not worry about speed or life
// Input:  train1 is the first train
//         train2 is the second train
// Output: 1 for true, 0 for false, see UART output window 
// Error conditions: None
// These first five test cases drawn on the Canvas document
//   Train1 is x=0, length=2;	Train2 is x=5, length =4; No touching, and no overlapping
//   Train1 is x=0, length=4;	Train2 is x=4, length =3; Touching, but not overlapping
//   Train1 is x=4, length=2;	Train2 is x=1, length =3; Touching, but not overlapping
//   Train1 is x=1, length=4;	Train2 is x=3, length =3; Overlapping, but not touching
//   Train1 is x=4, length=4;	Train2 is x=2, length =3; Overlapping, but not touching
// The remaining cases are randomly generated
int Question2(train_t train1, train_t train2){
  
  for (int i = train1.x; i < train1.x+train1.length; i++) {
    for (int j = train2.x; j < train2.x+train2.length; j++) {
      if (i == j) return 1;
    }
  }

  return 0;

}


/****************** MakeActive ****************************
Question 3: You are given an array of NumTrains trains. 
  All trains have length 1.
First, set the life field of every train to 1
Second, search the array again. If a train has the same x value 
  as any other train then set both trains' life to 0
Third, count the number of trains that have life equal to 1
Inputs: Fleet is an array of type train_t
        NumTrains is the number of trains in the Fleet
        Assume NumTrains is 0 to 10
Output: Return the number of trains that have life equal to 1
Error conditions: None
First five Test Cases, other cases are random:

NumTrains=0; return 0 
NumTrains=1; Fleet[0] is x=0; make Fleet[0]'s life = 1; 
             return 1
NumTrains=2; Fleet[0] is x=2;	make Fleet[0]'s life = 0
             Fleet[1] is x=2;	make Fleet[1]'s life = 0 
             return 0
NumTrains=3; Fleet[0] is x=9;	make Fleet[0]'s life = 1
             Fleet[1] is x=5; make Fleet[1]'s life = 1
             Fleet[2] is x=6; make Fleet[2]'s life = 1
             return 3
NumTrains=4; Fleet[0] is x=9;	make Fleet[0]'s life = 1
             Fleet[1] is x=5; make Fleet[1]'s life = 0
             Fleet[2] is x=6; make Fleet[2]'s life = 1
             Fleet[3] is x=5; make Fleet[2]'s life = 0
             return 2
*/
uint32_t MakeActive(train_t Fleet[],uint32_t NumTrains){

  for (int i = 0; i < NumTrains; i++) {
    Fleet[i].life = 1;
  }

  for (int i = 0; i < NumTrains; i++) {
    for (int j = 0; j < NumTrains; j++) {
      if (Fleet[i].x == Fleet[j].x && i != j) Fleet[i].life = Fleet[j].life = 0;
    }
  }

  int cnt = 0;
  for (int i = 0; i < NumTrains; i++) {
    if (Fleet[i].life == 1) cnt++;
  }

  return cnt;

}
