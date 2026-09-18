/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the Ultrasonic Sensor driver
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#include "gpio.h"
#include "icu.h"
#include "ultrasonic.h"
#include <util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* ICU configuration structure with prescaler F_CPU/8 and initial edge detection as rising */
static ICU_ConfigType ICU_Configurations = {F_CPU_8, RAISING};

/* Timer count flag to track the edge detection state */
static uint8 g_timercount = 0;

/* Variable to store the timer value corresponding to the high pulse width */
static uint16 g_timerhigh = 0;

/* Flag to indicate that a measurement is complete */
static uint8 g_timerdone = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description: Function to initialize the Ultrasonic sensor.
 *              1. Initialize the ICU driver with the required configurations.
 *              2. Set the ICU callback function to handle edge processing.
 *              3. Configure the trigger pin as output.
 */
void Ultrasonic_init(void)
{
	ICU_init(&ICU_Configurations);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(ULTRASONIC_TRIG_PORT_ID, ULTRASONIC_TRIG_PIN_ID, PIN_OUTPUT);
}

/*
 * Description: Function to trigger the Ultrasonic sensor by sending
 *              a 10us pulse to the trigger pin.
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIG_PORT_ID, ULTRASONIC_TRIG_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIG_PORT_ID, ULTRASONIC_TRIG_PIN_ID, LOGIC_LOW);
}

/*
 * Description: Function to read the distance measured by the Ultrasonic sensor.
 *              1. Trigger the Ultrasonic sensor.
 *              2. Wait for the Echo signal to be processed.
 *              3. Calculate and return the distance based on the timer value.
 */
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	while (g_timerdone == 0); /* Wait for the measurement to complete */

	/* Calculate distance in cm using the speed of sound and the timer value */
	float value = ((1.0 / (F_CPU / 8)) * 17000);
	uint16 distance = (uint16)((g_timerhigh * value) + 1);

	g_timerdone = 0; /* Reset flag for next measurement */

	return distance;
}

/*
 * Description: Function to handle the edge processing of the Echo signal.
 *              This function is called in the ICU ISR.
 *              1. On the first rising edge, reset the timer and set to detect falling edge.
 *              2. On the falling edge, store the timer value, reset for the next reading.
 */
void Ultrasonic_edgeProcessing(void)
{
	if (g_timercount == 0)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
		g_timercount++;
	}
	else
	{
		g_timerhigh = ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RAISING);
		g_timercount = 0;
		g_timerdone = 1;
	}
}
