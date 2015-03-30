#include <sensor_control.h>
#include <motor_control.h>

int o_pins[] = {11, 12, 16};
int i_pins[] = {28, 27, 26};
int suitable_reading = 0;
int i_readings[3];
int i;

motor_control mc(o_pins);
sensor_control sc(i_pins);

void setup() {
}

void loop() {
  
  for(i = 0; i < 3; i++) {
    i_readings[i] = sc.get_ir_reading(i_pins[i]);
    if(i_readings[i] > 50) {
     suitable_reading = 1; 
    }
  }
  
  mc.power_motor(o_pins[0], 50);
  mc.power_motor(o_pins[1], 50);
  mc.power_motor(o_pins[2], 50);
  delay(1000);
  
}
