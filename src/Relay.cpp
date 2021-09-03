#include "Relay.h"
#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;

static uint32_t next_heap_millis = 0;
byte pinEnable;

Relay::Relay(byte pinEnable)
{
	// Use 'this->' to make the difference between the
	// 'pin' attribute of the class and the
	// local variable 'pin' created from the parameter.
	this->pinEnable = pinEnable;
}
void cha_switch_on_setter(const homekit_value_t value)
{
	bool on = value.bool_value;
	cha_switch_on.value.bool_value = on; //sync the value
	LOG_D("Switch: %s", on ? "ON" : "OFF");
	digitalWrite(pinEnable, on ? HIGH : LOW);
}
void Relay::init()
{
	pinMode(pinEnable, OUTPUT);
	digitalWrite(pinEnable, HIGH);
	this->currentState = false;
	cha_switch_on.setter = cha_switch_on_setter;
	arduino_homekit_setup(&config);
}
int Relay::read()
{
	return this->currentState;
}

void Relay::my_homekit_loop()
{
	arduino_homekit_loop();
	const uint32_t t = millis();
	if (t > next_heap_millis)
	{
		// show heap info every 5 seconds
		next_heap_millis = t + 5 * 1000;
		LOG_D("Free heap: %d, HomeKit clients: %d",
			  ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
	}
}
