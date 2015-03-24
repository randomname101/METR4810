#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

	extern void motor_init(void);
	extern void power_motor(int id, int duty_cycle);
	extern int get_motor_duty_cycle(int id);
	extern void emergency_stop(void);

#endif