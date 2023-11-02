/**
*  LCD 16x2 / 16x4 8Bit Mode Source File 
*
*/

#include	<xc.h>
#include "..\..\mcc_generated_files\device_config.h"

//#define	LCD_16x4 

#define	LCD_RS LATEbits.LE2
//#define	LCD_RW LATDbits.LE2
#define LCD_EN LATEbits.LE1

#define LCD_DATA4	LATDbits.LD4
#define LCD_DATA5	LATDbits.LD5
#define LCD_DATA6	LATDbits.LD6
#define LCD_DATA7	LATDbits.LD7

#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))

/* write a byte to the LCD in 8 bit mode */
void lcd_write(unsigned char c);

/* write one chars to the LCD */
void lcd_putch(char c);

/* 	Clear and home the LCD */
void lcd_clear(void);

/* write a string of chars to the LCD */
void lcd_puts(const char * s);

/* Go to the specified position */
void lcd_1st_line(unsigned char pos);
void lcd_2nd_line(unsigned char pos);

#ifdef LCD_16x4
    void lcd_3rd_line(unsigned char pos);
    void lcd_4th_line(unsigned char pos);
#endif	

/* initialize the LCD - put into 4 bit mode */
void lcd_4bit_init(void);

