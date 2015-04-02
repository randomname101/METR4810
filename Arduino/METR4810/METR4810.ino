#include <serial_control.h>
#include <sensor_control.h>

//#include <String.h>
#include <motor_control.h>


int o_pins[] = {21, 22, 23}; //A7, A8, A9
int i_pins[] = {14, 15, 16, 17}; //A0, A1, A2 = Accelerometer A3 = IR
int suitable_reading = 0;
int i_readings[3];
int i;

String temp_s = "safsdags";

motor_control mc(o_pins);
sensor_control sc(i_pins);

void setup() {
}

void loop() {
  
  for(i = 0; i < 3; i++) {
    i_readings[i] = sc.get_acc_reading(i_pins[i]);
  }
  i_readings[3] = sc.get_ir_reading(i_pins[3]);
  if(i_readings[3] > 50) {
    suitable_reading = 1; 
  }
  
  if(suitable_reading > 0) {
   mc.landing(o_pins, i_readings); 
  }
    
  /*mc.power_motor(o_pins[0], 50);
  mc.power_motor(o_pins[1], 50);
  mc.power_motor(o_pins[2], 50);*/
  delay(1000);
  
}
