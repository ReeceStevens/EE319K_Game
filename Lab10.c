#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <stdint.h>

#include "random.h"
#include "LCD.h"
#include "LCD.s"
#include "Nokia5110.h"
// Setup for the file structure: 
//     Controls.c (includes ADC, GPIO buttons)
//     Communication.c (includes UART and FIFO)
//     Sound.c (SysTick audio, DAC)
//     Timers.c (Handles game timers)
//     Resources.c (Graphics definitions)
//     Lab10.c (Game engine and main)

// Game engine design:
//     Main Menu: splash logo for 5 sec
//                options (1 Player or 2 Player)
//
//     1 Player: Spawn enemies, begin standard game
//
//     2 Player: Open communication between two boards
//               Each player on opposite sides, enemies
//                   in middle; missiles can hit either 
//                   enemies or other player for points.
//                   Try to get highest score without
//                   running out of lives.

int main(void){
    //TExaS_Init(SSI0_Real_Nokia5110_Scope); // Sets system clock to 80 MHz
    Random_Init(1);
    LCD_Init();
    LCD_ClearBuffer();
    LCD_DisplayBuffer();
     
     
    return 0;
}
