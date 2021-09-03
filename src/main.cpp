#include <Arduino.h>
#include "wifi_info.h"
#include "Relay.h"


Relay relayBombillo(5);

void setup()
{
	Serial.begin(115200);
	relayBombillo.init();
	wifi_connect();
}
void loop()
{
	relayBombillo.my_homekit_loop();
	delay(10);
}