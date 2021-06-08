#include <iostream>
#include <cstdlib>
#include <string>
#include <atomic>
#include <cstring>
#include <chrono>
#include "mqtt/async_client.h"

using namespace std;

const string DFLT_SERVER_ADDRESS	{ "tcp://192.168.0.103:1883" };
const string CLIENT_ID				{ "paho_cpp_async_publish" };
const string PERSIST_DIR			{ "./persist" };

const string TOPIC { "topic/test" };

const char* PAYLOAD1 = "Seba Ty Kociaku <3";
const char* PAYLOAD2 = "Hi there!";

const char* LWT_PAYLOAD = "Last will and testament.";

const int  QOS = 1;

const auto TIMEOUT = std::chrono::seconds(10);
/**
 * A callback class for use with the main MQTT client.
 */
class callback : public virtual mqtt::callback
{
public:
	void connection_lost(const string& cause) override {
		cout << "\nConnection lost" << endl;
		if (!cause.empty())
			cout << "\tcause: " << cause << endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		cout << "\tDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << endl;
	}
};

int main()
{
	string address = DFLT_SERVER_ADDRESS;
	string clientID = CLIENT_ID;

	cout << "Initializing for server '" << address << "'..." << endl;
	mqtt::async_client client(address, clientID, PERSIST_DIR);

	callback cb;
	client.set_callback(cb);

	auto connOpts = mqtt::connect_options_builder()
		.clean_session()
		.will(mqtt::message(TOPIC, LWT_PAYLOAD, QOS))
		.finalize();

	cout << "  ...OK" << endl;

	try {
		cout << "\nConnecting..." << endl;
		mqtt::token_ptr connection_token = client.connect(connOpts);
		cout << "Waiting for the connection..." << endl;
		connection_token->wait();
		cout << "  ...OK" << endl;

		// // First use a message pointer.

		cout << "\nSending message..." << endl;
		mqtt::message_ptr publish_message = mqtt::make_message(TOPIC, PAYLOAD1);
		publish_message->set_qos(QOS);
		client.publish(publish_message)->wait_for(TIMEOUT);
		cout << "  ...OK" << endl;

		// // Now try with itemized publish.

		// cout << "\nSending next message..." << endl;
		// mqtt::delivery_token_ptr pubtok;
		// pubtok = client.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2), QOS, false);
		// cout << "  ...with token: " << pubtok->get_message_id() << endl;
		// cout << "  ...for message with " << pubtok->get_message()->get_payload().size()
		// 	<< " bytes" << endl;
		// pubtok->wait_for(TIMEOUT);
		// cout << "  ...OK" << endl;

		// Now try with a listener

		// cout << "\nSending next message..." << endl;
		// action_listener listener;
		// pubmsg = mqtt::make_message(TOPIC, PAYLOAD3);
		// pubtok = client.publish(pubmsg, nullptr, listener);
		// pubtok->wait();
		// cout << "  ...OK" << endl;

		// // Finally try with a listener, but no token

		// cout << "\nSending final message..." << endl;
		// delivery_action_listener deliveryListener;
		// pubmsg = mqtt::make_message(TOPIC, PAYLOAD4);
		// client.publish(pubmsg, nullptr, deliveryListener);

		// while (!deliveryListener.is_done()) {
		// 	this_thread::sleep_for(std::chrono::milliseconds(100));
		// }
		// cout << "OK" << endl;

		// Double check that there are no pending tokens

		auto toks = client.get_pending_delivery_tokens();
		if (!toks.empty())
			cout << "Error: There are pending delivery tokens!" << endl;

		// Disconnect
		cout << "\nDisconnecting..." << endl;
		client.disconnect()->wait();
		cout << "  ...OK" << endl;
	}
	catch (const mqtt::exception& exc) {
		cerr << exc.what() << endl;
		return 1;
	}
}



#include <iostream>
#include <cstdlib>
#include <string>
#include <atomic>
#include <cstring>
#include <chrono>
#include "mqtt/async_client.h"

using namespace std;

const string DFLT_SERVER_ADDRESS	{ "tcp://192.168.0.103:1883" };
const string CLIENT_ID				{ "paho_cpp_async_publish" };
const string PERSIST_DIR			{ "./persist" };

const string TOPIC { "topic/test" };

const char* PAYLOAD1 = "Seba Ty Kociaku <3";
const char* PAYLOAD2 = "Hi there!";

const char* LWT_PAYLOAD = "Last will and testament.";

const int  QOS = 1;

const auto TIMEOUT = std::chrono::seconds(10);
/**
 * A callback class for use with the main MQTT client.
 */
class callback : public virtual mqtt::callback
{
public:
	void connection_lost(const string& cause) override {
		cout << "\nConnection lost" << endl;
		if (!cause.empty())
			cout << "\tcause: " << cause << endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		cout << "\tDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << endl;
	}
};

// int main()
// {
// 	string address = DFLT_SERVER_ADDRESS;
// 	string clientID = CLIENT_ID;

// 	cout << "Initializing for server '" << address << "'..." << endl;
// 	mqtt::async_client client(address, clientID, PERSIST_DIR);

// 	callback cb;
// 	client.set_callback(cb);

// 	auto connOpts = mqtt::connect_options_builder()
// 		.clean_session()
// 		.will(mqtt::message(TOPIC, LWT_PAYLOAD, QOS))
// 		.finalize();

// 	cout << "  ...OK" << endl;

// 	try {
// 		cout << "\nConnecting..." << endl;
// 		mqtt::token_ptr connection_token = client.connect(connOpts);
// 		cout << "Waiting for the connection..." << endl;
// 		connection_token->wait();
// 		cout << "  ...OK" << endl;

// 		// // First use a message pointer.

// 		cout << "\nSending message..." << endl;
// 		mqtt::message_ptr publish_message = mqtt::make_message(TOPIC, PAYLOAD1);
// 		publish_message->set_qos(QOS);
// 		client.publish(publish_message)->wait_for(TIMEOUT);
// 		cout << "  ...OK" << endl;

// 		// // Now try with itemized publish.

// 		// cout << "\nSending next message..." << endl;
// 		// mqtt::delivery_token_ptr pubtok;
// 		// pubtok = client.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2), QOS, false);
// 		// cout << "  ...with token: " << pubtok->get_message_id() << endl;
// 		// cout << "  ...for message with " << pubtok->get_message()->get_payload().size()
// 		// 	<< " bytes" << endl;
// 		// pubtok->wait_for(TIMEOUT);
// 		// cout << "  ...OK" << endl;

// 		// // // Double check that there are no pending tokens

// 		// auto toks = client.get_pending_delivery_tokens();
// 		// if (!toks.empty())
// 		// 	cout << "Error: There are pending delivery tokens!" << endl;

// 		// Disconnect
// 		cout << "\nDisconnecting..." << endl;
// 		client.disconnect()->wait();
// 		cout << "  ...OK" << endl;
// 	}
// 	catch (const mqtt::exception& exc) {
// 		cerr << exc.what() << endl;
// 		return 1;
// 	}
// }