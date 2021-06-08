#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <atomic>
#include <cstring>
#include <chrono>
#include "mqtt/async_client.h"

class MQTT: public virtual mqtt::callback
{
	private:
		std::string m_server_address;
		std::string m_topic;
		std::string m_client_ID;
		std::string m_persist_dir {"./persist"};
		uint8_t m_QoS;

		
	public:
		MQTT(std::string server_address, std::string topic, std::string client_ID, uint8_t QoS);

	/*
	 *	Gettery
	 */
	std::string getServerAddress() const { return m_server_address; }
	std::string getTopc() const { return m_topic; }
	std::string getClientID() const { return m_client_ID; }

	/*
	 * Callback for main MQTT client
	 */
	void connectionLost(const std::string& cause) override;
	void deliveryComplete(mqtt::delivery_token_ptr tok) override;

	/*
	 * Init connection
	 */
	mqtt::async_client initClientServerConnection();

	/*
	 *	Push Info
	 */
	virtual void pushStatus() = 0;
	// virtual void receivedStatus() = 0;

	~MQTT () {};
};
