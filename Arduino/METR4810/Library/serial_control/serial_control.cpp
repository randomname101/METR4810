#include "Arduino.h"
#include "serial_control.h"
#include <WString.h>
#include <String.h>

/**
* Set up serial communication and confirm connection
*
* @param None
* @retVal None
*/
serial_control::serial_control(void) {
	// open serial communications
	Serial.begin(9600);
	// wait for serial port to connect
	while(!Serial) {
		;
	}
}

/**
* Take a message and print to serial
*
* @param String to print to serial
* @retVal None
*/
void serial_control::s_write(String output) {
	Serial.println(output);
}

/**
* Read a character from serial, return character
*
* @param None
* @retVal Character entered
*/
char serial_control::s_get_c(void) {
	char temp_char;
	if(Serial.available())
		temp_char = Serial.read();
	return temp_char;
}

/**
* Read a string from serial, return string
*
* @param None
* @retVal String entered
*/
String serial_control::s_get_s(void) {
	String temp_string = "";
	char temp_char;
	while(Serial.available()) {
		temp_char = Serial.read();
		temp_string.concat(temp_char);
	}
	return temp_string;
}