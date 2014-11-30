// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: Reece Stevens and Ramya Ramachandran
// Date Created: 8/25/2014 
// Last Modified: 10/17/2014 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "dac.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
// Description: We will use PA2-5 to interface a 4-bit DAC
void DAC_Init(void){
	volatile uint32_t delay;
		SYSCTL_RCGCGPIO_R |= 0x01;
		delay = SYSCTL_RCGCGPIO_R;
		GPIO_PORTA_DEN_R |= 0x3C;
		GPIO_PORTA_DIR_R |= 0x3C;
		GPIO_PORTA_AFSEL_R &= ~0x3C;
		
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
// Description: Write the given data to the DAC
void DAC_Out(uint32_t data){
		data = data << 2; 		// pins start at PA2
		//data &= 0x3C;		// Change all unused bits to zero for write safety
		GPIO_PORTA_DATA_R &= ~0x3C; // Clear data bits to receive new data
		GPIO_PORTA_DATA_R |= data;	// Add new ones
}
