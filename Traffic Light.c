#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "LED.h"
#include "timer 0.h"

volatile unsigned char counter;

int main(void)
{
	unsigned char counter_green,counter_yellow,counter_red;
	LCD_init();
	LED_init('D',0);
	LED_init('D',1);
	LED_init('D',2);
	timer0_CTC_init_interrupt();
    while(1)
    {
		counter_green=10;
		counter_yellow=5;
		counter_red=7;
		LED_on('D',0);
		LCD_send_string("Remaining 10 sec");
		while(counter_green>0)
		{
			if(counter>=100)
			{
				counter=0;
				counter_green--;
				LCD_move_cursor(1,11);
				LCD_send_char(counter_green+48);
				LCD_send_char(0x20);
			}
		}
		_delay_ms(500);
		LCD_clear_screen();
		LED_off('D',0);
		LED_on('D',1);
		LCD_send_string("Remaining 5 sec");
		while(counter_yellow>0)
		{
			if(counter>=100)
			{
				counter=0;
				counter_yellow--;
				LCD_move_cursor(1,11);
				LCD_send_char(counter_yellow+48);
			}
		}
		_delay_ms(500);
		LCD_clear_screen();
		LED_off('D',1);
		LED_on('D',2);
		LCD_send_string("Remaining 7 sec");
		while(counter_red>0)
		{
			if(counter>=100)
			{
				counter=0;
				counter_red--;
				LCD_move_cursor(1,11);
				LCD_send_char(counter_red+48);
			}
		}
		_delay_ms(500);
		LCD_clear_screen();
		LED_off('D',2);
    }
}

ISR(TIMER0_COMP_vect)
{
	counter++;
}