/*
 * garage.c
 *
 * Created: 9/29/2022 9:52:52 PM
 *  Author: HP.SXH08
 */ 


#include <avr/io.h>
#include "timer.h"
#include "DIO.h"
#include "LCD.h"
#include "LCD_config.h"
#define F_CPU 1000000UL
#include <avr/delay.h>

unsigned char count_in=0;
unsigned char oldIn,newIn,oldOut,newOut;
int main(void)
{
	LCD_vInit();
	LCD_vSend_string("cars in: 0");
    while(1)
    {
		newIn=DIO_u8read('D',0);
		newOut=DIO_u8read('D',1);
		
        if(oldIn==0 && newIn==1  &&  count_in<3)
		{
			timer1B_wave_fastPWM(2);
			_delay_ms(300);
			timer1B_wave_fastPWM(1.5);
			count_in++;
			LCD_movecursor(1,10);
			LCD_vSend_char(count_in + 48);
			
		}		
		
		if(oldOut==0 && newOut==1 &&  count_in>0)
		{
			timer1A_wave_fastPWM(2);
			_delay_ms(300);
			timer1A_wave_fastPWM(1.5);
			count_in--;
			LCD_movecursor(1,10);
			LCD_vSend_char(count_in + 48);
		}
		
		
		oldIn = newIn;
		oldOut = newOut;
		
		
    }
	
	
}