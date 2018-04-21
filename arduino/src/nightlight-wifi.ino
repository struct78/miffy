#include <Arduino.h>
#include <SPI.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#define DEVELOPMENT 1
#define WEBDUINO_SERIAL_DEBUGGING 1
#define WEBDUINO_READ_TIMEOUT_IN_MS 250

void setup() {
	Serial.begin(115200);
	neomatrix_setup();
	wifi_setup();
}

void loop() {
	neomatrix_loop();
	wifi_loop();
	dns_loop();
}
