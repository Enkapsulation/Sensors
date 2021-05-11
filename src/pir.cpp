#include <iostream>
#include "../WiringPi/wiringPi/wiringPi.h"
#include "sensor_interface.hpp"

#include "dbg_trace.hpp"

/* Take a look on gpio readall */
#define PIR_PIN 7U

int main()
{
	wiringPiSetup();
	PIR PIR_sensor(PIR_PIN, INPUT, 0xBEEF);
	size_t iterator { 0U };
	uint8_t actual_state { 0U };

	#if defined (_DEBUG_FLAG)
	PIR_sensor.Debug_PIR_Sensor(actual_state, iterator);
	#endif /* _DEBUG_FLAG  */

	PIR_sensor.printInfo();

	// PIR_sensor.Detect_Move(actual_state);
}
