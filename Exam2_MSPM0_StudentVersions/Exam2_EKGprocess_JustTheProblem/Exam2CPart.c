// File: Exam2CPart.c 
// ****Put your name here*******
// -5 points if you do not add your name
// This is Exam2
//EE319K Fall 2018 exam 2, November 8, 2018
// This is the C Part of the Exam (See Exam2AsmPart.s for the assembly part)  
#include <stdint.h>
//****you may not use string.h************

// *** Question 3******************
// You are given a null-terminated ASCII string and 
//     you will return the number of instances of
//     the three-letter sequence 'P' 'V' and 'C' in that order
// input:  pointer to a null-terminated ASCII string
// output: return the number of instances of PVC in the string
// Note: the string may be empty, in which case return 0  
// Note: here are some of the test cases
// case rhythm                    return 
//  1   "APBPVCNNPVCNN"              2
//  2   "PCVPVCPVCPPVCPPPVC"         4
//  3   "AB"                         0
//  4   ""                           0
uint32_t CountPVC(char rhythm[]){


  return 42;  // remove and replace this line
}

// each patient has an ID and 
// a record of their heart beats stored as a null-terminated ASCII string 
typedef struct{
  uint32_t PatientID; // patient number
  char Rhythm[32];    // ASCII string
}Patient_t;

//** Question 4******************
// You are given two inputs, an array of patients and its size
//    Practice[] is an array of Patient_t elements
//    size is the number patients in the array
// Search the Practice[] array for the patient with the most PVCs 
//    in their Rhythm array
// Input: Practice is a pointer to an array of Patient_t entries 
//        size is the number of patients, which may be zero, 
// Output: return the patient ID of the patient with the most PVCs
// Note: you can call the function implemented in Question 3 
// Note: you can assume the PatientIDs are unique
// Note: if two or more patients have the same maximum count, 
//       return the ID of the first one you find
// Note: here are some of the test cases
// *** a practice with 3 patients ***** size  return
//  {5,"PVCPVC"},
//  {6,"ABCDEFG"},
//  {8,".PVCPVCPVC.."}                    3      8
// *** a practice with 5 patients ***** size  return
//  {10,"PVCPVC"},
//  {12,"PVCPVCPVCPVCPVCPVCPVCPVCPVC"},
//  {13,""},
//  {14,""},
//  {15,"PVC"}                            5     12
// *** a practice with 1 patient  ***** size  return
//  {55,"ABC"},                           1     55
// *** a practice with 6 patients ***** size  return
//  {21,"PVACPVBC"},
//  {22,"PCVPPCVPCV"},
//  {33,"ABC"},
//  {44,"WXYZ"},
//  {46,""},
//  {77,"PVC"},                           6     77
uint32_t FindMost(Patient_t Practice[], uint32_t const size){
  
  
  return 42;  // remove and replace this line

}


