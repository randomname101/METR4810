#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "sensor_control.h"

extern void sensors_init(void);
extern int get_sensor_unknown(int id);

volatile int s1_reading = 0;
volatile int s2_reading = 0;
volatile int s3_reading = 0;
volatile int current_reading = 0;
volatile int max_reading = 0;
volatile int current_sensor = 0;

/**
* Initialise pins and ADC channels to allow analogue input to be read through
* 	selected pins.
*/
extern void sensors_init(void) {

	//set C pins 3,4 & 5 as input (chose opposite end of microchip, to reduce crowding)
	//unfortunately the opposite side of the microchip is not an option
	DDRC |= (0 << DDC5) | (0<<DDC4) | (0<<DDC3); 
	
	//set reference voltage to AVcc (5V)
	ADMUX |= (0<<REFS1) | (1<<REFS0);

	//enable ADC
	ADCSRA |= (1 << ADEN);
	//enable ADC interrupts
	ADCSRA |= (1 << ADIE);
	
	//set prescaler to 128, 16MHz microchip -> 16x10^6/128 = 125kHz
	//this frequency seemed to work best with IR sensors, however modifications
	//may be required
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	//left shift result (returns 8 bit instead of 10 bit)
	ADMUX |= (1 << ADLAR); 
	
}

/**
* Take selected sensor (1-3 <-> ADC3-5) and return maximum reading from sensor over 0.1s
*/
extern int get_sensor_unknown(int id) {
	max_reading = 0;
	current_reading = 0;
	int i = 0;
	
	//set ADC channel to be read from, see datasheet for values
	//sensor 1 = ADC3, sensor 2 = ADC4, sensor 3 = ADC5
	switch(id) {
		case 1:
			ADMUX |= (0<<MUX3) | (0<<MUX2) | (1<<MUX1) | (1<<MUX0);
			current_sensor = 1;
			break;
		case 2:
			ADMUX |= (0<<MUX3) | (1<<MUX2) | (0<<MUX1) | (0<<MUX0);
			current_sensor = 2;
			break;
		case 3:
			ADMUX |= (0<<MUX3) | (1<<MUX2) | (0<<MUX1) | (1<<MUX0);
			current_sensor = 3;
			break;
		default:
			printf("Error: selected sensor is not valid, must be 1-3\n");
			break;
	}

	for(i = 0; i < 100; i++) {
		//begin conversion
		ADCSRA |= (1 << ADSC);
		if(current_reading > max_reading) {
			max_reading = current_reading;
		}
		_delay_ms(1);
	}
	
	switch(current_sensor) {
		case 1:
			s1_reading = max_reading;
			break;
		case 2:
			s2_reading = max_reading;
			break;
		case 3:
			s3_reading = max_reading;
			break;
		default:
			printf("Error: transferring current sensor value\n");
			break;
	}
}

/**
*	Interrupt called every time ADC finishes conversion
*/
ISR(ADC_vect){ 
	current_reading = ADCH;
}