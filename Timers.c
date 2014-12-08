#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Timers.h"

// *************** Timer 0 Init *********************
// Timer used for updating game status (30 Hz)

void (*PeriodicTask0)(void); 
// Declare a user-defined function
// called by Timer1 Handler.

void Timer0_Init(void(*task)(void), uint32_t period){
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
  PeriodicTask0 = task;          // user function
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = period-1;    // 4) reload value
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x6000000; // 8) priority 3
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
}

void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER0A timeout
  (*PeriodicTask0)();                // execute user task
}


// *************** Timer 1 Init *********************
// Timer used for playing SFX (__ Hz)
void (*PeriodicTask1)(); 
// Declare a user-defined function
// called by Timer1 Handler.

void Timer1_Init(void(*task)(void), uint32_t period){
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate TIMER1
  PeriodicTask1 = task;          // user function
  TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = period-1;    // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_ICR_R = 0x00000001;    // 6) clear TIMER1A timeout flag
  TIMER1_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF)|0x0000A000; // 8) priority 5
// interrupts enabled in the main program after all devices initialized
// vector number 37, interrupt number 21
  NVIC_EN0_R = 1<<21;           // 9) enable IRQ 21 in NVIC
  //TIMER1_CTL_R = 0x00000001;    // 10) enable TIMER1A
}

void Timer1A_Handler(void){
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
  (*PeriodicTask1)();                // execute user task
}

void Timer1A_Stop(void){
	TIMER1_CTL_R &= ~0x00000001;
}

void Timer1A_Start(void){
	TIMER1_CTL_R |= 0x00000001;
}

// *************** Timer 2 Init *********************
// Timer used for playing SFX (Output sound at 11.025 Hz)

void (*PeriodicTask2)(); 

//uint32_t TimerCount;
void Timer2_Init(void(*task)(void), uint32_t period){
	uint32_t volatile delay; 
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate TIMER2
  delay = SYSCTL_RCGCTIMER_R;
	PeriodicTask2 = task;
  //TimerCount = 0;
  TIMER2_CTL_R = 0x00000000;    // 1) disable TIMER2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear TIMER2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  //TIMER2_CTL_R = 0x00000001;    // 10) enable TIMER2A
}

//Timer 2A plays sounds
// trigger is Timer2A Time-Out Interrupt
// set periodically TATORIS set on rollover

void Timer2A_Handler(void){
  TIMER2_ICR_R = 0x00000001;// acknowledge TIMER2A timeout
	(*PeriodicTask2)();
}
	
	void Timer2A_Stop(void){ 
  TIMER2_CTL_R &= ~0x00000001; // disable (call to stop sound)
}

void Timer2A_Start(void){ 
  TIMER2_CTL_R |= 0x00000001;   // enable (call to start sound)
}
// *************** Timer 3 Init *********************
// Timer used for playing SFX (Output sound at 11.025 Hz)

void (*PeriodicTask3)(); 

void Timer3_Init(void(*task)(void), uint32_t period){
	uint32_t volatile delay; 
  SYSCTL_RCGCTIMER_R |= 0x08;   // 0) activate TIMER3
  delay = SYSCTL_RCGCTIMER_R;
	PeriodicTask3 = task;
  TIMER3_CTL_R = 0x00000000;    // 1) disable TIMER2A during setup
  TIMER3_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER3_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER3_TAILR_R = period-1;    // 4) reload value
  TIMER3_TAPR_R = 0;            // 5) bus clock resolution
  TIMER3_ICR_R = 0x00000001;    // 6) clear TIMER2A timeout flag
  TIMER3_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI8_R = (NVIC_PRI8_R&0x00FFFFFF)|0x80000000; // 8) priority 4
  NVIC_EN1_R = 1<<3;           // 9) enable IRQ 35 in NVIC
}


void Timer3A_Handler(void){
  TIMER2_ICR_R = 0x00000001;// acknowledge TIMER2A timeout
	(*PeriodicTask3)();
}
	
	void Timer3A_Stop(void){ 
  TIMER2_CTL_R &= ~0x00000001; // disable (call to stop sound)
}

void Timer3A_Start(void){ 
  TIMER2_CTL_R |= 0x00000001;   // enable (call to start sound)
}