// Nokia5110.h
// Runs on LM4F120/TM4C123
// Use SSI0 to send an 8-bit code to the Nokia5110 48x84
// pixel LCD to display text, images, or other information.
// Daniel Valvano
// October 20, 2014

// Font table, initialization, and other functions based
// off of Nokia_5110_Example from Spark Fun:
// 7-17-2011
// Spark Fun Electronics 2011
// Nathan Seidle
// http://dlnmh9ip6v2uc.cloudfront.net/datasheets/LCD/Monochrome/Nokia_5110_Example.pde

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */


// *************************************************************
// ***************Be careful************************************
// ** There are multiple Nokia5110 boards in the world,       **
// ** some with different pin numbers,                        **
// ** but all with the same basic signals                     **
// *************************************************************

// One type of Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

// Another type of Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total


// Contrast value 0xB1 looks good on red SparkFun
// and 0xB8 looks good on blue Nokia 5110.
// Adjust this from 0xA0 (lighter) to 0xCF (darker) for your display.
#define CONTRAST                0xB1


//********LCD_Init*****************
// Initialize Nokia 5110 48x84 LCD by sending the proper
// commands to the PCD8544 driver.  One new feature of the
// LM4F120 is that its SSIs can get their baud clock from
// either the system clock or from the 16 MHz precision
// internal oscillator.  If the system clock is faster than
// 50 MHz, the SSI baud clock will be faster than the 4 MHz
// maximum of the Nokia 5110.
// inputs: none
// outputs: none
// assumes: system clock rate of 50 MHz or less
void LCD_Init(void);

//********LCD_OutChar*****************
// Print a character to the Nokia 5110 48x84 LCD.  The
// character will be printed at the current cursor position,
// the cursor will automatically be updated, and it will
// wrap to the next row or back to the top if necessary.
// One blank column of pixels will be printed on either side
// of the character for readability.  Since characters are 8
// pixels tall and 5 pixels wide, 12 characters fit per row,
// and there are six rows.
// inputs: data  character to print
// outputs: none
// assumes: LCD is in default horizontal addressing mode (V = 0)
void LCD_OutChar(char data);

//********LCD_OutString*****************
// Print a string of characters to the Nokia 5110 48x84 LCD.
// The string will automatically wrap, so padding spaces may
// be needed to make the output look optimal.
// inputs: ptr  pointer to NULL-terminated ASCII string
// outputs: none
// assumes: LCD is in default horizontal addressing mode (V = 0)
void LCD_OutString(char *ptr);

//********LCD_Goto*****************
// Move the cursor to the desired X- and Y-position.  The
// next character will be printed here.  X=0 is the leftmost
// column.  Y=0 is the top row.
// inputs: newX  new X-position of the cursor (0<=newX<=11)
//         newY  new Y-position of the cursor (0<=newY<=5)
// outputs: none
void LCD_Goto(uint8_t newX, uint8_t newY);

//********LCD_Clear*****************
// Clear the LCD by writing zeros to the entire screen and
// reset the cursor to (0,0) (top left corner of screen).
// inputs: none
// outputs: none
void LCD_Clear(void);

//********LCD_DrawFullImage*****************
// Fill the whole screen by drawing a 48x84 bitmap image.
// inputs: ptr  pointer to 504 byte bitmap
// outputs: none
// assumes: LCD is in default horizontal addressing mode (V = 0)
void LCD_DrawFullImage(const uint8_t *ptr);

//-----------------------LCD_OutDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: data is a 32-bit unsigned number
// Output: none
// students implement this as part of Lab 7
void LCD_OutDec(uint32_t data);

// -----------------------LCD _OutFix----------------------
// Output characters to LCD display in fixed-point format
// unsigned decimal, resolution 0.001, range 0.000 to 9.999
// Inputs:  unsigned 32-bit number
// Outputs: none
// E.g., data=0,    then output "0.000 "
//       data=3,    then output "0.003 "
//       data=89,   then output "0.089 "
//       data=123,  then output "0.123 "
//       data=9999, then output "9.999 "
//       data>9999, then output "*.*** "
// students implement this as part of Lab 7
void LCD_OutFix(uint32_t data);

// *************** LCD_PlotClear ********************
// Clear the graphics buffer, set X coordinate to 0
// It does not output to display until LCD_ShowPlot called
// Inputs: ymin and ymax are range of the plot
// Outputs: none
void LCD_PlotClear(int32_t ymin, int32_t ymax);

// *************** LCD_PlotPoint ********************
// Used in the voltage versus time plot, plot one point at y
// It does not output to display until LCD_ShowPlot called
// Inputs: y is the y coordinate of the point plotted
// Outputs: none
void LCD_PlotPoint(int32_t y);

// *************** LCD_PlotNext ********************
// Used in all the plots to step the X coordinate one pixel
// X steps from 0 to 83, then back to 0 again
// It does not output to display until LCD_ShowPlot called
// Inputs: none
// Outputs: none
void LCD_PlotNext(void);

// *************** LCD_ShowPlot ********************
// Dump data to display
// Inputs: none
// Outputs: none
void LCD_ShowPlot(void);
