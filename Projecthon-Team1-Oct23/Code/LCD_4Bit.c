/**
*  LCD 16x2 / 16x4 8Bit Mode Source File 
*
*/

#include <xc.h>
#include "..\LCD_4Bit.h"

/* write a byte to the LCD in 4 bit mode */
void lcd_write(unsigned char c)
{   unsigned char f;
	f = c;
	__delay_us(40);
	if(c & 0x10)
	LCD_DATA4 = 1;
	else
	LCD_DATA4 = 0;

	if(c & 0x20)
	LCD_DATA5 = 1;
	else
	LCD_DATA5 = 0;

	if(c & 0x40)
	LCD_DATA6 = 1;
	else
	LCD_DATA6 = 0;

	if(c & 0x80)
	LCD_DATA7 = 1;
	else
	LCD_DATA7 = 0;

	//LCD_DATA = ( c & 0xF0 );
	LCD_STROBE();
	
	if(c & 0x01)
	LCD_DATA4 = 1;
	else
	LCD_DATA4 = 0;

	if(c & 0x02)
	LCD_DATA5 = 1;
	else
	LCD_DATA5 = 0;

	if(c & 0x04)
	LCD_DATA6 = 1;
	else
	LCD_DATA6 = 0;

	if(c & 0x08)
	LCD_DATA7 = 1;
	else
	LCD_DATA7 = 0;

	//LCD_DATA = ( ( f << 4 ) & 0xF0 );
	LCD_STROBE();
}

/* write one chars to the LCD */
void lcd_putch(char dis_char)
{
	LCD_RS = 1;	// write characters
	lcd_write( dis_char );
}

/**
 * 	Clear and home the LCD
 */
void lcd_clear(void)
{
	LCD_RS = 0;
	lcd_write(0x1);
	__delay_ms(2);
}

/**
 *  write a string of chars to the LCD 
 */
void lcd_puts(const char * disp_str)
{
	LCD_RS = 1;	// write characters
	while(*disp_str)
		lcd_write(*disp_str++);
}



/*
 * Go to the specified position
 */
void lcd_1st_line(unsigned char pos)
{
	LCD_RS = 0;
#ifdef LCD_16x4
	lcd_write(0x00+pos);
#else
	lcd_write(0x80+pos);
#endif
}

void lcd_2nd_line(unsigned char pos)
{
	LCD_RS = 0;
#ifdef LCD_16x4
	lcd_write(0x40+pos);
#else
	lcd_write(0xC0+pos);
#endif
}

#ifdef LCD_16x4
void lcd_3rd_line(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0x10+pos);
}
#endif

#ifdef LCD_16x4
void lcd_4th_line(unsigned char pos)
{
	LCD_RS = 0;
	lcd_write(0x50+pos);
}
#endif
	
/* initialise the LCD - put into 4 bit mode */
void lcd_4bit_init(void)
{
	LCD_RS = 0;
	LCD_EN = 0;
	//LCD_RW = 0;
	
    __delay_ms(15);	// wait 15mSec after power applied,
	LCD_DATA4	 = 1;
	LCD_DATA5	 = 1;
	LCD_DATA6	 = 0;
	LCD_DATA7	 = 0;
		
	LCD_STROBE();
	__delay_ms(5);
	LCD_STROBE();
	__delay_us(200);
	LCD_STROBE();
	__delay_us(200);
	LCD_DATA4	 = 0;
	LCD_DATA5	 = 1;
	LCD_DATA6	 = 0;
	LCD_DATA7	 = 0;
	LCD_STROBE();

	lcd_write(0x28); // Set interface length
	lcd_write(0x0E); // Display On, Cursor On, Cursor Blink
	lcd_clear();	// Clear screen
	lcd_write(0x06); // Set entry Mode
}

