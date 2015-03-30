class sensor_control {
	public:
		sensor_control(int pins[]);
		int get_acc_reading(int pin);
		int get_ir_reading(int pin);
	private:
		int _pins[];
};
