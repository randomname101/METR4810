#include <String.h>
#include <WString.h>
class serial_control {
	public:
		serial_control(void);
		void s_write(String output);
		char s_get_c(void);
		String s_get_s(void);
};
