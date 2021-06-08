/*============================================================================*\
* PIR class method
\*============================================================================*/
#include "pir_driver.hpp"
#include "dbg_trace.hpp"
#include "../MQTT/mqtt.hpp"
#include <wiringPi.h>

/*============================================================================*\
* PIR class method
\*============================================================================*/
PIR::PIR(uint8_t pin_sensor, uint8_t pin_mode, uint16_t serial_number, std::string server_adress, std::string topic, std::string client_ID, uint8_t QoS) : Sensor(serial_number), MQTT(server_adress, topic, client_ID, QoS), m_pin_number{pin_sensor}, m_pin_mode{pin_mode}, m_detect_move_flag{false} 
{
   setup();
}

/*============================[Override methods		]=====================================*/
void PIR::setup()
{
   pinMode(m_pin_number, m_pin_mode);
}


void PIR::printInfo()
{
   DbgTrace(DEBUG) << "[PIR HC-SR501]" << "\n\tID: " << std::hex << std::uppercase << "0x"  << getSerialNumber() << "\n\tPin number: " << getPinNumber() << "\n\tPin mode: " << getPinMode() << "\n\tDetect flag: " << getDetectMoveFlag();
}

/*============================[Method declarations	]=====================================*/
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

void PIR::Debug(bool actual_state, size_t& iterator)
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

/*============================[MQTT Api	]=====================================*/

void PIR::pushStatus(mqtt::async_client client, const std::string msg)
{
   try{
      DbgTrace(INFO) << "[?] Sending message" << "\n";
	   mqtt::message_ptr publish_message = mqtt::make_message(m_topic, msg);
	   publish_message->set_qos(m_QoS);
	   client.publish(publish_message);
	   DbgTrace(INFO) << "[+] Message sent" << "\n";
   }
   catch (const mqtt::exception& exc) {
		cerr << exc.what() << endl;
		return 1;
	}
	
}
