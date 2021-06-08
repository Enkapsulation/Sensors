#include <iostream>
#include <cstdlib>
#include <string>
#include <atomic>
#include <cstring>
#include <chrono>

#include "mqtt.hpp"
#include "dbg_trace.hpp"
#include "mqtt/async_client.h"

MQTT::MQTT(std::string server_address, std::string topic, std::string client_ID, uint8_t QoS) : m_server_address{server_address}, m_topic{topic}, m_client_ID{client_ID}, m_QoS{QoS} {}


void MQTT::connection_lost(const std::string& cause) 
{
	DbgTrace(ERROR) << "[ERROR] Connection lost" << "\n";
       	if (!cause.empty())
	{
		DbgTrace(ERROR) << "[ERROR] " << cause << "\n";
	}
}

void MQTT::delivery_complete(mqtt::delivery_token_ptr tok) 
{
	DbgTrace(INFO) << "[+] Delivery complete for token: " 
	       << (tok ? tok->get_message_id() : -1) << "\n";	
}

mqtt::async_client MQTT::initClientServerConnection()
{
	DbgTrace(INFO) << "[+] Init for server" << m_server_address << "\n";
	mqtt::async_client client(m_server_address, m_client_ID, m_persist_dir);

	auto connestions_options = mqtt::connect_options_builder()
		.clean_session()
		.will(mqtt::message(m_topic, m_client_ID, m_persist_dir))
		.finalize

	try {
		
		DbgTrace(INFO) << "[+] Init succefull" << "\n";
		DbgTrace(INFO) << "[+] Connecting " << "\n";

		mqtt::token_ptr connection_token = client.connect(connOps);
		connection_token->wait();

		return client;
	}
	catch (const mqtt::exception& exc) {
		cerr << exc.what() << endl;
		return 1;
	}
}
