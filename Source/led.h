/******************************************************************************
 *
 * Module: LED Control
 *
 * File Name: led.h
 *
 * Description: Header file for the LED driver.
 *
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LED Pin and Port Configurations */
#define LED_RED_PORT_ID   PORTC_ID
#define LED_RED_PIN_ID    PIN0_ID

#define LED_GREEN_PORT_ID PORTC_ID
#define LED_GREEN_PIN_ID  PIN1_ID

#define LED_BLUE_PORT_ID  PORTC_ID
#define LED_BLUE_PIN_ID   PIN2_ID

/* LED States */
#define LED_ON  LOGIC_HIGH
#define LED_OFF LOGIC_LOW

/*******************************************************************************
 *                               Type Declarations                             *
 *******************************************************************************/

/* Enumeration for LED Identification */
typedef enum
{
	LED_RED,
	LED_GREEN,
	LED_BLUE
} LED_ID;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initializes the LEDs by setting the required pins as output.
 */
void LEDS_init(void);

/*
 * Description :
 * Turns ON the specified LED.
 */
void LED_on(LED_ID id);

/*
 * Description :
 * Turns OFF the specified LED.
 */
void LED_off(LED_ID id);

#endif /* LED_H_ */
