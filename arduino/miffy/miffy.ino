#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

void setup() {
  Serial.begin(115200); 
  neomatrix_setup();
  //wifi_setup();
}

void loop() {
  //wifi_loop();
  neomatrix_loop();
}

