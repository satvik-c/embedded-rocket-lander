/*
;This is Exam2_Mode8
;Your name goes here
;You edit Exam2ASMPart.s and Exam2CPart.c files only

;***** Mode subroutine *********************
;Find the mode of all values in the array
;Inputs:  R0 has a pointer to the array of 8-bit unsigned numbers
;Output:  R0 is the mode of all the values
;first few test cases
;Array1: .byte 3,1,1,3         ;Mode=1
;Array2: .byte 5,12,13,4,12,3  ;Mode=12
;Array3: .byte 14,1,1,1,2,1,1,2,1,2,1,2,1,1,1    ;Mode=1
;Array4: .byte 0           ;Mode=0 (empty array)
; first element is the size
; all values are bounded from 0 to 255
*/
#include <stdint.h>
uint32_t Size(const uint8_t *buffer);
uint32_t Count(const uint8_t *buffer, uint8_t value);


uint8_t Mode(const uint8_t *buffer){ 
  return 42; // replace this line
}

