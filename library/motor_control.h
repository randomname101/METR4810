#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

	extern void motor_init(void);
	extern void power_motor(char id, int duty_cycle);
	extern int get_motor_power(char id);
	extern void emergency_stop(void);

#endif