#include "Arduino.h"
#include "sensor_control.h"

/**
* Take an array of pins, set them as inputs, save them for use
* within sensor_control
*
* @param Array of pins
* @retVal None
*/
sensor_control::sensor_control(int pins[]) {
	int i = 0;
	for(i = 0; i < sizeof(pins); i++) {
        _pins[i] = pins[i];
		pinMode(pins[i], INPUT);
	}	
}

/**
* Take a pin, and get the accelerometer reading
* from this pin
*
* @param Pin to read from
* @retVal Reading, converted to a percentage of the max. reading
*/
int sensor_control::get_acc_reading(int pin) {
	int i = 0;
	int max_reading = 0, current_reading = 0, retVal;
	float temp_val;
	//read for 0.1 seconds, 100 times with frequency of 1000Hz
	//actual frequency required yet to be determined, as it was
	//not given with the accelerometer specs
	for(i = 0; i < 100; i++) { //read for 0.1 seconds
		current_reading = analogRead(pin);
		if(current_reading > max_reading) {
		//find the maximum reading, this can be switched with a filter if necessary
			max_reading = current_reading;
		}
		delay(1); //currently reading at 1000Hz, can change
	}
	//convert reading to percentage of maximum value
	temp_val = ((float)max_reading)/1023.0 * 100;
	//cast to int, to return value that can be used with subsequent functions
	retVal = (int)temp_val;
	return retVal;
}

/**
* Take the selected IR pin, get a reading from this pin
*
* @param Pin to read from
* @retVal Reading, converted to a percentage of the max. reading
*/
int sensor_control::get_ir_reading(int pin) {
	int i = 0;
	int max_reading = 0, current_reading = 0, retVal;
	float temp_val;
	//read for 0.1 seconds, 7700 readings in 0.1 seconds at frequency of 72kHz
	//36kHz frequency IR beacon, therefore Nyquist frequency = 72kHz
	for(i = 0; i < 7700; i++) {
		current_reading = analogRead(pin);
		if(current_reading > max_reading) {
		//currently returning maximum value in 0.1 seconds
		//can be changed to filter (and most likely will) if necessary
			max_reading = current_reading;
		}
		delayMicroseconds(13); //36kHz IR beacon, 72kHz reading
	}
	//convert reading to percentage of maximum reading
	temp_val = ((float)max_reading/1023.0) * 100;
	//cast percentage to int, to be used in subsequent functions
	retVal = (int)temp_val;
	return retVal;
}