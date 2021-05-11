/*============================================================================*\
* PIR class method
\*============================================================================*/
#include "PIRClass.hpp"
#include <wiringPi.h>
#include "dbg_trace.hpp"

/*============================================================================*\
* PIR class method
\*============================================================================*/
PIR::PIR(uint8_t pin_sensor, uint8_t pin_mode, uint16_t serial_number) : Sensor(serial_number), m_pin_number{pin_sensor}, m_pin_mode{pin_mode}, m_detect_move_flag{false} 
{
   setup();
}

void PIR::setup()
{
   pinMode(m_pin_number, m_pin_mode);
}

// void PIR::printInfo()
// {
// 	std::cout << "[STATE] \n\tPin number: " << this->getPinNumber() << "\n\tPin mode: " << this->getPinMode() << "\n\tDetect flag: " << this->getDetectMoveFlag() << std::endl;
// }

void PIR::printInfo()
{
   DbgTrace(DEBUG) << "[PIR HC-SR501]" << "\n\tID: " << std::hex << std::uppercase << "0x"  << getSerialNumber() << "\n\tPin number: " << getPinNumber() << "\n\tPin mode: " << getPinMode() << "\n\tDetect flag: " << getDetectMoveFlag();
}

void PIR::sendMsgOnStateChange()
{
   bool actual_state = getPinState();

   if((actual_state) && (!m_detect_move_flag))
   {
      set_detect_move_flag(true);
      // sendStateMsg();
   }
   else if((!actual_state) && (m_detect_move_flag))
   {
      set_detect_move_flag(false);
   }
}

void PIR::Debug(bool& actual_state, size_t& iterator)
{
   while (1)
   {
      iterator = 0;
      actual_state = getPinState();
      
      if(actual_state)
      {
         while (getPinState())
         {
            iterator++;
         }

         DbgTrace(DEBUG) << "Ilość 1: " << iterator;
      }
      else
      {
         while (!(getPinState()))
         {
            iterator++;
         }
         
         DbgTrace(DEBUG) << "Ilość 0: " << iterator;
      }
   }
}

