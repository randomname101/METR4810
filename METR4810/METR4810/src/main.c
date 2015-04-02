#include<stdio.h>
#include<avr/interrupt.h>
#include "library/motor_control.h"
#include <util/delay.h>
#include <avr/io.h>

int main() {
	motor_init();
	while(1) {
		power_motor(1, 25);
		power_motor(2, 50);
		power_motor(3, 75);
	}
}
