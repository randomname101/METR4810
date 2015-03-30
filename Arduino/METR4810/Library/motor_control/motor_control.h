class motor_control {
	public:
		motor_control(int pins[]);
		void power_motor(int pin, int duty_cycle);
		int get_motor_duty(int pin);
		void emergency_stop(int pins[]);
		
	private:
		int _pins[];
};
