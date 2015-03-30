#include "Arduino.h"
#include "motor_control.h"

motor_control::motor_control(int pins[]) {
	int i = 0;
	for(i = 0; i < sizeof(pins); i++) {
                _pins[i] = pins[i];
		pinMode(pins[i], OUTPUT);
	}	
}

void motor_control::power_motor(int pin, int duty_cycle) {
	float temp_output;
	int integer_output;
	temp_output = ((float)duty_cycle/100.0) * 255;
	integer_output = (int)temp_output;
	analogWrite(pin, integer_output);
}

int motor_control::get_motor_duty(int pin) {
	int retVal, temp_input;
	float tempVal;
	temp_input = analogRead(pin);
	tempVal = ((float)temp_input/255.0) * 100.0;
	retVal = (int)tempVal;
	return retVal;
}

void motor_control::emergency_stop(int pins[]) {
	int i = 0;
	for(i = 0; i < sizeof(pins); i++) {
		analogWrite(i, 0);
	}
}
