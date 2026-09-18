/******************************************************************************
 *
 * Module: Main Application
 *
 * File Name: main.c
 *
 * Description: Main file for Car Parking System Application
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#include "lcd.h"
#include "ultrasonic.h"
#include "led.h"
#include "buzzer.h"
#include <util/delay.h>
#include "avr/io.h"
#include "interrupt.h"

/*******************************************************************************
 *                             Main Function                                   *
 *******************************************************************************/

/*
 * Description: Main function that initializes all the required modules
 *              and continuously reads the distance from the Ultrasonic sensor.
 *              Based on the measured distance, it controls the LCD display,
 *              LEDs, and the Buzzer to indicate object proximity.
 */
int main(void)
{
	uint16 distance = 0; /* Variable to store measured distance */

	/* Initialize peripherals */
	LCD_init();
	LEDS_init();
	Buzzer_init();
	Ultrasonic_init();

	/* Display initial LCD message */
	LCD_displayString("Distance = ");
	LCD_moveCursor(0, 14);
	LCD_displayString("cm");

	/* Enable global interrupts for ICU */
	Enable_Global_Interrupt();

	while (1)
	{
		/* Read the measured distance from the Ultrasonic sensor */
		distance = Ultrasonic_readDistance();

		/* Update distance value on LCD */
		LCD_moveCursor(0, 11);
		LCD_intgerToString(distance);

		/* Object is very close (≤ 5 cm) -> Activate buzzer and flash LEDs */
		if (distance <= 5)
		{
			Buzzer_on();
			LCD_displayString("  "); /* Clear old distance if digits decrease */
			LCD_moveCursor(1, 6);
			LCD_displayString("STOP");

			/* Flash all LEDs for warning */
			_delay_ms(300);
			LED_on(LED_RED);
			LED_on(LED_GREEN);
			LED_on(LED_BLUE);
			_delay_ms(300);
			LED_off(LED_RED);
			LED_off(LED_GREEN);
			LED_off(LED_BLUE);
		}

		/* Object is close (6 - 10 cm) -> Keep LEDs on, but no buzzer */
		else if (distance >= 6 && distance <= 10)
		{
			Buzzer_off();
			LCD_displayString(" ");
			LCD_moveCursor(1, 6);
			LCD_displayString("    "); /* Clear STOP message */
			LED_on(LED_RED);
			LED_on(LED_GREEN);
			LED_on(LED_BLUE);
		}

		/* Object is at a medium distance (11 - 15 cm) -> Turn off blue LED */
		else if (distance >= 11 && distance <= 15)
		{
			LED_on(LED_RED);
			LED_on(LED_GREEN);
			LED_off(LED_BLUE);
		}

		/* Object is farther (16 - 20 cm) -> Only red LED stays on */
		else if (distance >= 16 && distance <= 20)
		{
			LED_on(LED_RED);
			LED_off(LED_GREEN);
			LED_off(LED_BLUE);
		}

		/* No object detected (≥ 20 cm) -> Turn off all LEDs */
		else if (distance >= 20 && distance < 100)
		{
			LCD_displayString(" ");
			LCD_moveCursor(1, 6);
			LED_off(LED_RED);
			LED_off(LED_GREEN);
			LED_off(LED_BLUE);
		}
	}
}
