 /*
 * task3.c
 *
 *  Created on: Oct 24, 2019
 *      Author: levinm7
 */

#include "init.h"
int32_t firstValue = 256;
int32_t secondValue = 1293;
int32_t finalValue = 0;
int32_t result = 0;
int32_t macResult = 0;
int32_t x = 30;
int main(void)
{
	//Initialize the system
	Sys_Init();
	//configureADC();
	//First Part
	asm("LDR r0, =0x100");
	asm("LDR r1, =0x50D");
	asm("ADD r2, r1 , r0");
	asm("STR r2,%0" : "=m" (finalValue));
	//Second Part
	asm("MUL %[result], %[v1], %[v2]" : [result] "=r" (result) : [v1]"r"(firstValue), [v2]"r"(secondValue));
	printf("The final value is: %d\r\n" ,(int)finalValue); //First Print
	printf("The multiplied value is: %d\r\n" ,(int)result); //Second Print
	//Third Part
	asm("MUL r0, %[v1], %[v2]": :[v1] "r" (0x2), [v2] "r" (x));
	asm("SDIV r0, r0, %[v1]" : : [v1] "r" (0x3));
	asm("ADD r0, r0, %[v1]" :: [v1] "r" (0x5));
	asm("STR r0,%0" : "=m" (result));
	printf("The equation value is: %d\r\n" ,(int)result); //Third Print
	//Fourth Part
	asm("MLA  r0, %[v1], %[v2], %[v3]" :: [v1] "r"(0x2), [v2] "r" (x), [v3] "r" (0xF));
	asm("SDIV r0, r0, %[v1]" : : [v1] "r" (0x3));
	asm("STR r0,%0" : "=m" (macResult));
	printf("The MAC equation value is: %d\r\n" ,(int)macResult); //Third Print


	// Code goes here

}


