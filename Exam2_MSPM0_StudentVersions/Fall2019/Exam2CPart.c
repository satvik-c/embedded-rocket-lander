/*
 *****Satvik Chawla*******
  -5 points if you do not add your name

 This is Exam2J 
 EE319K Fall 2019 exam 2, November 2019
 This is the C Part of the Exam (See Exam2ASMPart.c for the assembly part)
 The C part is not related to the assembly part
*/   
#include <stdint.h>
/*
1) grandmother pill schedule can vary from day to day, 
2) the pill types are numbered from 0 to NumPills-1 (different from assembly part)
3) the expected number of each pill type taken each day could vary from 0 to 255
4) there are seven days in a week, the days are numbers 0 to 6
*/
struct medicine{        // holds information for one day
  uint8_t NumPills;     // number of pills grandmother is taking
  uint8_t PillCount[8]; // Count of pills taken this day for each type of pill
  uint8_t RxCount[8];   // Expected count of pills for each type of pill
};
typedef struct medicine medicine_t;


/****************** DayCheck ****************************
Check the medicine record for one day to make sure grandmother 
      has taken the correct number of each pill for this day
Inputs: aDay, one record of one day's medicine (populated with pill data)
Output: 
  return 8 if each PillCount[i] matches each RxCount[i] for all i from 0 to NumPills-1
  return i if a PillCount[i] is less than RxCount[i] for some i from 0 to NumPills-1
  return -1 if a PillCount[i] is greater than RxCount[i] for some i from 0 to NumPills-1
Error conditions: 
  there are no test cases where some counts are lower than expected AND at least one count is higher than expected
  return 8 if NumOfPills is 0 (grandmother needs no pills).
*/
int32_t DayCheck(const medicine_t aDay){ 
  
  if (aDay.NumPills == 0) return 8;

  for (int i = 0; i < aDay.NumPills; i++) {
    if (aDay.PillCount[i] < aDay.RxCount[i]) return i;
    else if (aDay.PillCount[i] > aDay.RxCount[i]) return -1;
  }

  return 8;

}
/****************** WeekCheck ****************************
Check the medicine record for one week to make sure grandmother 
      has taken the correct number of each pill for all seven days of the week
Inputs: aWeek[7], an array of 7 records (populated with pill data)
        status[7], an array of 7 booleans (initially empty)
Output: 
  return 1 if any day is not proper (too few or too many pills)
    and fill status[7] array with 0s on proper days, and 1's on not proper
  return 0 if all days are proper
    and fill status[7] array with all 0s        */
int32_t WeekCheck(const medicine_t aWeek[7],int32_t status[7]){

  for (int i = 0; i < 7; i++) {
    if (DayCheck(aWeek[i]) == 8) {
      status[i] = 0;
    } else {
      status[i] = 1;
    }
  }

  for (int i = 0; i < 7; i++) {
    if (status[i] == 1) return 1;
  }

  return 0;

}
