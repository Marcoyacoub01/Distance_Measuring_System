/*
 * project_4.c
 *
 *  Created on: Mar 4, 2024
 *      Author: Marco
 */

#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h>


int main (void){

	uint16 distance =0;

	SREG|=(1<<7);
	LCD_init();
	Ultrasonic_init();

	LCD_displayString("Distance = ");

	LCD_moveCursor(0,14);
	LCD_displayString("CM");

	while (1)
	{
		LCD_moveCursor(0,11);
		distance = Ultrasonic_readDistance();

	    if ( distance < 100)
		{
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
		}
		else if (distance >= 100)
		{
			LCD_intgerToString(distance);

		}



	}
}
