#pragma once
#include "wiringPi.h"
#include "../MQTT/mqtt.hpp"
#include "sensor_interface.hpp"

/*============================================================================*\
* PIRsensor class declarations
\*============================================================================*/

class PIR : public Sensor, public MQTT
{
	private:
		uint8_t m_pin_number;
		uint8_t m_pin_mode;

		bool m_detect_move_flag;

		void set_detect_move_flag(const bool& detect_move_flag) { m_detect_move_flag = detect_move_flag; };

	public:
		PIR(uint8_t pin_sensor, uint8_t pin_mode, uint16_t serial_number, std::string server_adress, std::string topic, std::string client_ID, uint8_t QoS);

		/*
		 *	override methods
		 */
		void setup() override;
		void printInfo() override;

		/*
		 *	Gettery
		 */
		uint16_t getSerialNumber(void) const { return m_serial_number; }

		uint8_t getPinNumber() const { return m_pin_number; }
		uint8_t getPinMode() const { return m_pin_mode; }

		bool getPinState(void) const { return digitalRead(m_pin_number); }
		bool getDetectMoveFlag(void) const { return m_detect_move_flag; };

		/*
		 *	Method declarations
		 */
		void sendMsgOnStateChange();
		void Debug(bool actual_state, std::size_t& iterator);

		/*
		 *	MQTT Api
		 */
		void pushStatus();

		~PIR() {};
};
