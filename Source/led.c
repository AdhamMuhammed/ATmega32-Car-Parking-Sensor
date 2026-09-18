/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.c
 *
 * Description: Source file for the AVR LED driver
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/
#include "led.h"
#include "gpio.h"

/*
 * Function: LEDS_init
 * -------------------
 * Initializes the LED pins as output and turns them off initially.
 *
 * Parameters: None
 *
 * Returns: None
 */
void LEDS_init(void)
{
	/* Set LED pins as output */
	GPIO_setupPinDirection(LED_RED_PORT_ID, LED_RED_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, PIN_OUTPUT);

	/* Turn off all LEDs initially */
	GPIO_writePin(LED_RED_PORT_ID, LED_RED_PIN_ID, LED_OFF);
	GPIO_writePin(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LED_OFF);
	GPIO_writePin(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, LED_OFF);
}

/*
 * Function: LED_on
 * ----------------
 * Turns on the specified LED.
 *
 * Parameters:
 *   id - The ID of the LED to turn on (LED_RED, LED_GREEN, or LED_BLUE).
 *
 * Returns: None
 */
void LED_on(LED_ID id)
{
	switch(id)
	{
	case LED_RED:
		GPIO_writePin(LED_RED_PORT_ID, LED_RED_PIN_ID, LED_ON);
		break;
	case LED_GREEN:
		GPIO_writePin(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LED_ON);
		break;
	case LED_BLUE:
		GPIO_writePin(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, LED_ON);
		break;
	}
}

/*
 * Function: LED_off
 * -----------------
 * Turns off the specified LED.
 *
 * Parameters:
 *   id - The ID of the LED to turn off (LED_RED, LED_GREEN, or LED_BLUE).
 *
 * Returns: None
 */
void LED_off(LED_ID id)
{
	switch(id)
	{
	case LED_RED:
		GPIO_writePin(LED_RED_PORT_ID, LED_RED_PIN_ID, LED_OFF);
		break;
	case LED_GREEN:
		GPIO_writePin(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LED_OFF);
		break;
	case LED_BLUE:
		GPIO_writePin(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, LED_OFF);
		break;
	}
}
