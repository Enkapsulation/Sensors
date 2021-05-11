#pragma once
#include "sensor_interface/sensor_interface.hpp"

/*============================================================================*\
* PIRsensor class declarations
\*============================================================================*/

class PIR : public Sensor
{
	private:
		uint8_t m_pin_number;
		uint8_t m_pin_mode;

		bool m_detect_move_flag;

		void set_detect_move_flag(const bool& detect_move_flag) { m_detect_move_flag = detect_move_flag; };

	public:
		PIR(uint8_t pin_sensor, uint8_t pin_mode, uint16_t serial_number);

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
		void Debug(bool& actual_state, size_t& iterator);

		~PIR() {};
};
