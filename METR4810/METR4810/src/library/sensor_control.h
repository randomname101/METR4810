#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

	extern void sensors_init(void);
	extern int get_reading_unknown(int id);
	extern int get_reading_someOtherSensor(int whoKnowsRightNow);

#endif