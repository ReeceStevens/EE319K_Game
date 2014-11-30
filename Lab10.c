#include <stdio.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "random.h"
#include "Nokia5110.h"
#include "Resources.h"
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

#define ONE_PLAYER      42
#define TWO_PLAYER      -42
#define ENEMY_HEIGHT    10

void startScreen(int mode){
    LCD_ClearBuffer();
    LCD_DisplayBuffer();
    LCD_PrintBMP(0, ENEMY_HEIGHT - 1, SmallEnemy30PointA, 0);
    LCD_PrintBMP(16, ENEMY_HEIGHT - 1, SmallEnemy30PointB, 0);
    LCD_PrintBMP(32, ENEMY_HEIGHT - 1, SmallEnemy30PointA, 0);
    LCD_PrintBMP(48, ENEMY_HEIGHT - 1, SmallEnemy30PointB, 0); 
    LCD_PrintBMP(64, ENEMY_HEIGHT - 1, SmallEnemy30PointA, 0);
    LCD_DisplayBuffer(); 
}

int main(void){
    //TExaS_Init(SSI0_Real_Nokia5110_Scope); // Sets system clock to 80 MHz
    Random_Init(1);
    LCD_Init();
    LCD_ClearBuffer();
    LCD_DisplayBuffer();
    startScreen(ONE_PLAYER); 
     
    return 0;
}
