#pragma once

/*============================================================================*\
* Includes headers
\*============================================================================*/
#include <iostream>
#include <string>
#include <wiringPi.h>


/*============================================================================*\
* Sensor class declarations
\*============================================================================*/

class Sensor
{
	protected:
		uint16_t m_serial_number;

	public:
		Sensor(uint16_t serial_number) : m_serial_number{serial_number} {};

		/*
		 *	Gettery
		 */
		virtual uint16_t getSerialNumber(void) const = 0;

		virtual void setup() = 0;
		virtual void printInfo() = 0;
		// virtual void sendStateMsg() = 0; // MQTT
		// virtual void getMsg(void* msg) = 0; // MQTT

		~Sensor() {};
};
