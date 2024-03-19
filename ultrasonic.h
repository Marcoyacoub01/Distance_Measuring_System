/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Hreader file for the ultrasonic sensor
 *
 * Author: Marco
 *
 *******************************************************************************/
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ULTRASONIV_TRIG_PORT_ID     PORTB_ID
#define ULTRASONIV_TRIG_PIN_ID      PIN5_ID

#define ULTRASONIV_ECHO_PORT_ID     PORTD_ID
#define ULTRASONIV_ECHO_PIN_ID      PIN6_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
