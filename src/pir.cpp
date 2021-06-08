#include <iostream>
#include <wiringPi.h>

#include "sensor_interface.hpp"
#include "dbg_trace.hpp"
#include "pir_driver.hpp"
#include "MQTT/mqtt.hpp"

/* Take a look on gpio readall */
#define PIR_PIN 7U

int main()
{
 	wiringPiSetup();
 	PIR PIR_sensor(PIR_PIN, INPUT, 0xBEEF, "tcp://192.168.0.103:1883", "topic/test", "pir_sensor_BEEF", 1);
 	size_t iterator { 0U };
 	uint8_t actual_state { 0U };

 	#if defined (_DEBUG_FLAG)
 	PIR_sensor.Debug(actual_state, iterator);
 	#endif /* _DEBUG_FLAG  */

 	PIR_sensor.printInfo();

	/* MQTT Connection */
	mqtt::async_client client = PIR_sensor.initClientServerConnection();
	PIR_sensor.

}
