#include "Arduino.h"
#include "sensor_control.h"

sensor_control::sensor_control(int pins[]) {
	int i = 0;
	for(i = 0; i < sizeof(pins); i++) {
        _pins[i] = pins[i];
		pinMode(pins[i], INPUT);
	}	
}

int sensor_control::get_acc_reading(int pin) {
	int i = 0;
	int max_reading = 0, current_reading = 0, retVal;
	float temp_val;
	for(i = 0; i < 100; i++) { //read for 0.1 seconds
		current_reading = analogRead(pin);
		if(current_reading > max_reading) {
			max_reading = current_reading;
		}
		delay(1); //currently reading at 1000Hz, can change
	}
	temp_val = ((float)max_reading)/1023.0 * 100;
	retVal = (int)temp_val;
	return retVal;
}

int sensor_control::get_ir_reading(int pin) {
	int i = 0;
	int max_reading = 0, current_reading = 0, retVal;
	float temp_val;
	for(i = 0; i < 3850; i++) { //read for 0.1 seconds
		current_reading = analogRead(pin);
		if(current_reading > max_reading) {
			max_reading = current_reading;
		}
		delayMicroseconds(26); //36kHz IR beacon
	}
	temp_val = ((float)max_reading/1023.0) * 100;
	retVal = (int)temp_val;
	return retVal;
}