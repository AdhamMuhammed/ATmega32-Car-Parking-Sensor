/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the Ultrasonic Sensor driver
 *
 * Author: Adham Muhammed
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ULTRASONIC_TRIG_PORT_ID PORTD_ID
#define ULTRASONIC_TRIG_PIN_ID PIN7_ID

#define ULTRASONIC_ECHO_PORT_ID PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID PIN6_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: Function to initialize the Ultrasonic sensor.
 *              1. Initialize the ICU driver.
 *              2. Set the ICU callback function.
 *              3. Configure the trigger pin as output.
 */
void Ultrasonic_init(void);

/*
 * Description: Function to trigger the Ultrasonic sensor by sending
 *              a 10us pulse to the trigger pin.
 */
void Ultrasonic_Trigger(void);

/*
 * Description: Function to read the distance measured by the Ultrasonic sensor.
 *              1. Trigger the Ultrasonic sensor.
 *              2. Wait for the Echo signal.
 *              3. Calculate and return the distance.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description: Function to handle the edge processing of the Echo signal.
 *              This function is called in the ICU ISR.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
