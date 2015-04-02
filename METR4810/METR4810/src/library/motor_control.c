#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motor_control.h"

private void populate_motor_struct(void);
extern void motor_init(void);
extern void power_motor(int id, int duty_cycle);
extern int get_motor_duty_cycle(int id);
extern void emergency_stop(void);

int number_of_motors = 3;

typedef struct {
	volatile uint16_t duty_cycle;
	char pin_id[2];
	char register_location[5];
} motor_variables;
volatile motor_variables motors[number_of_motors];

/**
*	Populate motors struct with potentially useful information
*
*/
private void populate_motor_struct(void) {

	uint8_t i = 0;
	motors[0].duty_cycle = 0;
	motors[0].pin_id = "B1";
	motors[0].register_location = "OCR1A";
	
	motors[1].duty_cycle = 0;
	motors[1].pin_id = "B2";
	motors[1].register_location = "OCR1B";
	
	motors[2].duty_cycle = 0;
	motors[2].pin_id = "B3";
	motors[2].register_location = "OCR2A";
	
}

/**
*	Initialise pins and timers to allow pwm output through pins B1, B2 and B3
*
*/
extern void motor_init(void) {
		
		//set pwm pins required as outputs
	DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3);

		//set initial output to 0 for each pin;
	OCR1A = 0;
	OCR1B = 0;
	OCR2A = 0;
	
		//set up timers for phase corrected (WGM), non-inverting (COM) pwm with no prescaler (CS)
		//if you don't understand what's happening here, check the datasheet
		
		//note: pins B1 and B2 are connected to timer 1, pin B3 connected to timer 2
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
	TCCR1B |= (1 << CS10);
	TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20)
	TCCR2B |= (1 << CS20);

}

/**
*	Power selected motor, with selected duty cycle (from 0-100%)
*
*/
extern void power_motor(int id, int duty_cycle) {

	//max output (5V/100% duty cycle) occurs at OCRxx = 255;
	float output_decimal = 255 * (float)duty_cycle/100.0;
	int output_int = (int)output_decimal;
	
	switch(id) {
		case 1: 
			OCR1A = output_int;
			motors[0].duty_cycle = duty_cycle;
			break;
		case 2:
			OCR1B = output_int;
			motors[1].duty_cycle = duty_cycle;
			break;
		case 3:
			OCR2A = output_int;
			motors[2].duty_cycle = duty_cycle;
			break;
		default:
			break;
	}
}

/**
*	Get the current duty cycle of selected motor
*
*/
extern int get_motor_duty_cycle(int id) {
	int temp_duty_cycle = 0;
	switch(id) {
		case 1: 
			temp_duty_cycle = motors[0].duty_cycle;
			break;
		case 2:
			temp_duty_cycle = motors[1].duty_cycle;
			break;
		case 3:
			temp_duty_cycle = motors[2].duty_cycle;
			break;
		default:
			break;
	}
	return temp_duty_cycle;
}

/**
*	Stop all motors, set output to each to 0 and update duty cycle accordingly
*
*/
extern void emergency_stop(void) {

	OCR1A = 0;
	OCR1B = 0;
	OCR2A = 0;
	
	motors[0].duty_cycle = 0;
	motors[1].duty_cycle = 0;
	motors[2].duty_cycle = 0;
	
}