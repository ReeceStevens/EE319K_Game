// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0

// Student names: Ramya Ramachandran and Reece Stevens
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void){ volatile unsigned long delay;


 SYSCTL_RCGCGPIO_R |= 0x00000031;   	// 1) activate clock for Port E
  delay = SYSCTL_RCGCGPIO_R;         //    allow time for clock to stabilize
	      


 SYSCTL_RCGCGPIO_R |= 0x00000010;   	// 1) activate clock for Port E
  delay = SYSCTL_RCGC2_R;         //    allow time for clock to stabilize
	  delay = 20;        
	while(delay != 0){delay --;};
  GPIO_PORTE_DIR_R &= ~0x04;      // 2) make PE2 input
  GPIO_PORTE_AFSEL_R |= 0x04;     // 3) enable alternate function on PE2
  GPIO_PORTE_DEN_R &= ~0x04;      // 4) disable digital I/O on PE2
  GPIO_PORTE_AMSEL_R |= 0x04;     // 5) enable analog function on PE2
  //SYSCTL_RCGC0_R |= 0x00010000;   // 6) activate ADC0
	SYSCTL_RCGCADC_R |= 0x01;   // 6) activate ADC0
  delay = SYSCTL_RCGC2_R;        
  delay = 20;        
	while(delay != 0){delay --;};    
  delay = SYSCTL_RCGC2_R;        
  //SYSCTL_RCGC0_R &= ~0x00000200;  // 7) configure for 125K
  delay = SYSCTL_RCGC2_R;        
  delay = 20;        
	while(delay != 0){delay --;};      
	ADC0_PC_R = 0x01;
	delay = SYSCTL_RCGC2_R;        
  delay = 20;        
	while(delay != 0){delay --;};       
  ADC0_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
  //ADC0_SSMUX3_R &= ~0x0001;       // 11) clear SS3 field
  //ADC0_SSMUX3_R += 1;             //    set channel Ain1 (PE2)
	ADC0_SSMUX3_R &= ~0x000F;       // 11) clear SS3 field
  ADC0_SSMUX3_R += 1;             //    set channel Ain1 (PE2)
	//ADC0_SSCTL3_R &= ~0x000F;
  ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC0_ACTSS_R |= 0x0008;         // 13) enable sample sequencer 3

  GPIO_PORTE_DIR_R &= ~0x04;      // 2) make PE2 input
  GPIO_PORTE_AFSEL_R |= 0x04;     // 3) enable alternate function on PE2
  GPIO_PORTE_DEN_R &= ~0x04;      // 4) disable digital I/O on PE2
  GPIO_PORTE_AMSEL_R |= 0x04;     // 5) enable analog function on PE2

	SYSCTL_RCGCADC_R |= 0x0001001;   // 6) activate ADC0
  delay = SYSCTL_RCGCADC_R;        
  SYSCTL_RCGCADC_R &= ~0x0000030;     
  ADC0_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger

	ADC0_SSMUX3_R &= ~0x0001;       // 11) clear SS3 field
  ADC0_SSMUX3_R += 1;             //    set channel Ain1 (PE2)

  ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC0_ACTSS_R |= 0x0008;         // 13) enable sample sequencer 3
}


//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void){uint32_t result;
	ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
	//uint32_t delay2 = 99;
	while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
  //while(delay2 != 0){delay2 --;};   // 2) wait for conversion done

  result = ADC0_SSFIFO3_R & 0xFFF;   // 3) read result
  ADC0_ISC_R |= 0x0008;             // 4) acknowledge completion
	//result = 42;
  return result;
}

void GPIO_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x30; // Enable clock for Port E and F
	volatile uint32_t delay = SYSCTL_RCGCGPIO_R;
	
	// Fire Button and Start Button
	GPIO_PORTE_DEN_R |= 0x20;
	GPIO_PORTE_AFSEL_R &= ~0x20;
	GPIO_PORTE_AMSEL_R &= ~0x20;
	GPIO_PORTE_DIR_R &= ~0x20;
	GPIO_PORTE_PCTL_R &= ~0x00FF0000;
	GPIO_PORTE_IS_R &= ~0x20; // Begin configuration for edge-triggered interrupts
	GPIO_PORTE_IBE_R &= ~0x20;
	GPIO_PORTE_IEV_R |= 0x20;
	GPIO_PORTE_ICR_R = 0x20;
	GPIO_PORTE_IM_R |= 0x20; // Configured for rising-edge interrupts
	NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00) | 0x00000040; // Make priority 5
	NVIC_EN0_R = 0x00000010; // enable the interrupt in NVIC
	
	// LED
	GPIO_PORTF_DEN_R |= 0x04;
	GPIO_PORTF_DIR_R |= 0x04;
	GPIO_PORTF_AFSEL_R &= ~0x04;
}
 










