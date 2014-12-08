#ifndef __TIMER0INTS_H__ // do not include more than once
#define __TIMER0INTS_H__

// ***************** Timer0_Init ****************
// Activate Timer0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer0_Init(void(*task)(void), uint32_t period);

#endif // __TIMER2INTS_H__


#ifndef __TIMER1INTS_H__ // do not include more than once
#define __TIMER1INTS_H__

// ***************** Timer1_Init ****************
// Activate Timer1 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer1_Init(void(*task)(void), uint32_t period);
void Timer1A_Stop(void);
void Timer1A_Start(void);

void Timer2_Init(void(*task)(void), uint32_t period);
void Timer2A_Stop(void);
void Timer2A_Start(void);

void Timer3_Init(void(*task)(void), uint32_t period);
void Timer3A_Stop(void);
void Timer3A_Start(void);

#endif // __TIMER2INTS_H__
