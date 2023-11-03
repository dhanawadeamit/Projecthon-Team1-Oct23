/*
 * Created on Nov 02, 2023, 8:33 PM
 */

#include<stdio.h>
#include<string.h>
#include "mcc_generated_files/mcc.h"
#include "PICSim_Manual_Add_Files\Lcd\LCD_4Bit.h"

#define resolution_vtg 0.005

#define adc_pin_moist 0
#define adc_pin_temp 1
#define gpio_pin_relay LATB1
#define pump_on LATB1 = 1;
#define pump_off LATB1 = 0;

char lcd_buff[20];
unsigned int pump_flag;
unsigned int over_all_status_flag;


void turn_pump_on(void)
{
    if(pump_flag == 0)
    {
        pump_flag = 1;
        pump_on;
    }
}


void turn_pump_off(void)
{
    if(pump_flag == 1)
    {
        pump_flag = 0;
        pump_off;
    }
}


unsigned int read_moisture(void)
{
    unsigned int read_moist;
    unsigned int moist_in_percentage;
    
    read_moist = 0;
    read_moist = ADCC_GetSingleConversion(adc_pin_moist);
    moist_in_percentage = ((((float) read_moist)/840)*100);

    return(moist_in_percentage);
}

unsigned int read_temperature(void)
{
    unsigned int read_temp_adc_count;
    unsigned int temp_in_cen;
    
    read_temp_adc_count = 0;

    read_temp_adc_count = ADCC_GetSingleConversion(adc_pin_temp);
    temp_in_cen = ((float) read_temp_adc_count)/2;
    return(temp_in_cen);
}

void display_moisture(unsigned int disp_moist)
{
    lcd_clear();
    sprintf(lcd_buff, "%3d",disp_moist);
    lcd_1st_line(0);
    lcd_puts("Moist: ");
    lcd_1st_line(6);
    lcd_puts(lcd_buff);
    lcd_putch('%');
    lcd_putch(' ');
}

void display_temperature(unsigned int disp_temp)
{
    sprintf(lcd_buff, "%3d",disp_temp);
    lcd_2nd_line(0);
    lcd_puts("Temp: ");
    lcd_2nd_line(5);
    lcd_puts(lcd_buff);
    lcd_putch('C');
    lcd_putch(' ');
}

void display_pump_status(unsigned int p_flag)
{
    if (p_flag == 1)
    {
        lcd_puts("P: On");
    }
    else
    {
        lcd_puts("P:Off");
    }
}

void display_over_all_status(unsigned int over_all_status_flag)
{
    if (over_all_status_flag == 0)
    {
        lcd_puts("OK!!");
    }
    else
    {
        lcd_puts("Act ");
    }
}

void refresh_display(unsigned int ref_current_moist,unsigned int ref_current_temp,unsigned int ref_pump_flag,unsigned int ref_over_all_status_flag)
{
    display_moisture(ref_current_moist);
    display_over_all_status(ref_over_all_status_flag);
    display_temperature(ref_current_temp);
    display_pump_status(ref_pump_flag);
}

void main(void)
{
    unsigned int current_temp;
    unsigned int current_moist;
    unsigned int temp_var;
    
    pump_flag = 0;
    over_all_status_flag = 0;
    
    current_temp = 0;
    current_moist = 0;

    SYSTEM_Initialize();
    pump_off;
    
    lcd_4bit_init();
    lcd_1st_line(0);
    lcd_puts("    EmbedDNA    ");
    lcd_2nd_line(0);
    lcd_puts(" Irrigation Sys ");
    __delay_ms(1000);

    while(1)
    {
        current_moist = read_moisture();
        current_temp = read_temperature();
        refresh_display(current_moist, current_temp, pump_flag, over_all_status_flag);
        __delay_ms(1000);
        
        if(current_moist < 30)
        {
            over_all_status_flag = 1; 
            turn_pump_on();
        }
        else if((current_temp < 20))
        {
            if(current_moist < 30 )
            {
                over_all_status_flag = 1; 
                turn_pump_on();
            }
            else
            {
                over_all_status_flag = 0; 
                turn_pump_off();
            }                        
        }
        else if((current_temp >= 21) && (current_temp <= 32))
        {
            if(current_moist <= 60 )
            {
                over_all_status_flag = 1; 
                turn_pump_on();
            }
            else
            {
                over_all_status_flag = 0; 
                turn_pump_off();
            }
        }
        else if((current_temp >= 33) && (current_temp <= 45))
        {
            if(current_moist <= 80 )
            {
                over_all_status_flag = 1; 
                turn_pump_on();
            }
            else
            {
                over_all_status_flag = 0; 
                turn_pump_off();
            }
        } 
        else if(current_temp > 45)
        {
            if(current_moist <= 96 )
            {
                over_all_status_flag = 1; 
                turn_pump_on();
            }
            else
            {
                over_all_status_flag = 0; 
                turn_pump_off();
            }
        }
        
        
            
        
        
        
        
    
    }
    
    

}
