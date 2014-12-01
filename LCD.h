// ************** LCD_WriteCommand ************************
// - Writes an 8-bit command to the LCD controller
// - RS low during command write
// In LCD.s file, students implement this as part of Lab 7
// 8-bit command passed in R0
// 1) LCD_DATA = 0x00;    // Write 0 as MSB of command 
// 2) LCD_CTRL = 0x10;    // Set CS, WR, RS low
// 3) LCD_CTRL = 0x70;    // Set WR and RS high
// 4) LCD_DATA = command; // Write 8-bit LSB command 
// 5) LCD_CTRL = 0x10;    // Set WR and RS low
// 6) wait 2 bus cycles     
// 7) LCD_CTRL = 0xF0;    // Set CS, WR, RS high
// ********************************************************
void LCD_WriteCommand(unsigned char command);

// ************** LCD_WriteData ***************************
// - Writes 16-bit data to the LCD controller
// - RS high during data write
// In LCD.s file, students implement this as part of Lab 7
// 16-bit data passed in R0
// 1) LCD_DATA = (data>>8);  // Write MSB to LCD data bus
// 2) LCD_CTRL = 0x50;       // Set CS, WR low
// 3) LCD_CTRL = 0x70;       // Set WR high
// 4) LCD_DATA = data;       // Write LSB to LCD data bus 
// 5) LCD_CTRL = 0x50;       // Set WR low
// 6) wait 2 bus cycles     
// 7) LCD_CTRL = 0xF0;       // Set CS, WR high
// ********************************************************
void LCD_WriteData(unsigned short data);
