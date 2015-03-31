#include "Arduino.h"
#include "motor_control.h"

/**
* Takes array of pins, sets each pin as output, saves pins to
*	array, for functions within motor_control
*
* @param Array of pins required for output
* @retVal None
*/
motor_control::motor_control(int pins[]) {
	int i = 0;
	for(i = 0; i < sizeof(pins); i++) {
        _pins[i] = pins[i];
		pinMode(pins[i], OUTPUT);
	}	
}

/**
* Takes the pin output is required on, and outputs a pwm wave of
* selected duty cycle on selected pin.
*	
* @param Pin number, duty cycle pwm output
* @retVal None
*/
void motor_control::power_motor(int pin, int duty_cycle) {
	float temp_output;
	int integer_output;
	//duty cycle = 0-100% <-> 0-255 written to register
	//therefore, find percentage, and apply to max value
	temp_output = ((float)duty_cycle/100.0) * 255;
	//analogWrite takes integer input, therefore cast to int
	integer_output = (int)temp_output;
	analogWrite(pin, integer_output);
}

/**
* Takes selected pin and returns the current duty cycle that pin
* is outputting at
*
* @param Pin required
* @retVal current duty cycle of the pin
*/
int motor_control::get_motor_duty(int pin) {
	int retVal, temp_input;
	float tempVal;
	temp_input = analogRead(pin);
	//as above, maximum value on register is 255, therefore
	//compare reading to max value to determine % duty cycle
	tempVal = ((float)temp_input/255.0) * 100.0;
	//as functions are set up to take integers, cast to int before returning
	retVal = (int)tempVal;
	return retVal;
}

/**
* Emergency stop function, blocks power to all defined motors
* 
* @param Array of pins that are currently outputting
* @retVal None
*/
void motor_control::emergency_stop(int pins[]) {
	int i = 0;
	for(i = 0; i < sizeof(pins); i++) {
		analogWrite(i, 0);
	}
}

/**
* Function to handle fan outputs when glider is landing
* As IR is no longer necessary, this can be handled at this point too
*
* @param Array of pins fans and IR are located on
* @retVal None
*/
void motor_control::landing(int pins[], int readings[]) {
	int i = 0; 
	int x = 50; //temp value, algorithm will be determined later
	for(i = 0; i < sizeof(_pins); i++) {
		analogWrite(_pins[i], x);
	}
	//release_parachute(24); //release parachute if we decide to implement this
}

/**
* Function to allow the release of a parachute if we decide to go with this
*
* @param Pin that servo is connected to
* @retVal None
*/
void motor_control::release_parachute(int servo_pin) {
	int angle = 45; //temp value, assuming open at maximum rotation
					//and centred
	analogWrite(servo_pin, angle);
}
