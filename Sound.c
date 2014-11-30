// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 10/5/2014 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "tm4c123gh6pm.h"

// 4-bit 32 element sine wave

uint32_t i = 0;
const unsigned char SineWave[32]= {
	8, 9, 11, 12, 13, 14, 14, 15, 15, 15, 14, 14, 13, 12, 11, 9, 8, 7, 5, 4, 3, 2, 2, 1, 1, 1, 2, 2, 3, 4, 5, 7};

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Called once, with sound initially off
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none
void Sound_Init(uint32_t period){
		// Initialize SysTick
		NVIC_ST_CTRL_R = 0;			// disable systick during setup
		NVIC_ST_RELOAD_R = period - 1; 
		NVIC_ST_CURRENT_R = 0;		// clear current count
		//NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF) | 0x20000000; // set priority level to 1
		NVIC_ST_CTRL_R = 0x0007;		// enable with core clocks and interrupts
	
}

void SysTick_Handler(void){
		i = (i+1)%32;					// Increase index by one (0-31)
		DAC_Out(SineWave[i]);
		//GPIO_PORTF_DATA_R ^= 0x02; // toggle heartbeat

}


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disable sound output
// Output: none
void Sound_Play(uint32_t period){
		/*if (period == 0){
				NVIC_ST_CTRL_R &= ~0x02; //disable systick interrupts if period is zero
				return;
		}*/
		//NVIC_ST_CTRL_R |= 0x02;	// if period isn't zero, enable interrupts
		NVIC_ST_RELOAD_R = period-1; // set new reload time
		//NVIC_ST_CURRENT_R = 0; // clear current systick timer
		
}
