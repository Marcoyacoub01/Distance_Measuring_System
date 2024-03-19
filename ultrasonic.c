/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the ultrasonic sensor
 *
 * Author: Marco
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util\delay.h>

uint16 time = 0;
uint8 ticks=0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Ultrasonic_init(void)
{
	GPIO_setupPinDirection(ULTRASONIV_TRIG_PORT_ID,ULTRASONIV_TRIG_PIN_ID, PIN_OUTPUT);
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};
	ICU_init(&ICU_Configurations);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_writePin(ULTRASONIV_TRIG_PORT_ID,ULTRASONIV_TRIG_PIN_ID, LOGIC_LOW);
}



void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ULTRASONIV_TRIG_PORT_ID,ULTRASONIV_TRIG_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIV_TRIG_PORT_ID,ULTRASONIV_TRIG_PIN_ID,LOGIC_LOW );
}


uint16 Ultrasonic_readDistance(void)
{

	Ultrasonic_Trigger();

	/*
	 * Calculation (distance in cm)
	 *  Sound velocity = 340.00 m/s = 34000 cm/s
	 * The distance of Object (in cm) = 340000∗Time2 / 2 = 17000 * Time
	 * Now, here we have selected an internal 8MHz oscillator frequency for ATmega16,
	 *  with Prescaler F_CPU/8 for timer frequency.
	 * Then time to execute 1 instruction is 1 us.
	 * So, the timer gets incremented after 1 us time elapse.
	 * = 17000 x (TIMER value) x 1 x 10^-6 cm
	 * = 0.017 x (TIMER value) cm
	 * (TIMER value) / 58.8 cm
	 * Note TIMER VALUE is the pulse width time calculated by the ICU.
	 */
	return (time/58+1);
}

void Ultrasonic_edgeProcessing(void)
{
	ticks++;
	if (ticks == 1)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	if (ticks == 2)
	{
		time = ICU_getInputCaptureValue();
		/* Clear the timer counter register to start measurements again */
		ICU_clearTimerValue();
		/* Detect rising edge */
		ICU_setEdgeDetectionType(RAISING);
	}
}


