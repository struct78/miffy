// Wi-Fi credentials are stored in a file called "credentials.ino". For the purposes of security this file has been excluded from Github.
// char ssid[] = "Your Network Name";
//char pass[] = "Your Network Password";   // your network password

#define PREFIX ""
WebServer webserver(PREFIX, 80);

int wifi_status = WL_IDLE_STATUS;

void wifi_setup() {
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( wifi_status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);   
    wifi_status = WiFi.begin(ssid, pass); 

    delay(5000);
  } 
  
  webserver.setDefaultCommand(&routes_default);
  webserver.addCommand("api/status", &routes_api_status);
  webserver.addCommand("api/power", &routes_api_power);
  webserver.addCommand("api/speed", &routes_api_speed);
  webserver.addCommand("api/brightness", &routes_api_brightness);
  //webserver.addCommand("api/pattern", &routes_api_pattern);
  webserver.begin();

  printWifiStatus();
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void wifi_loop() {
  char buff[64];
  int len = 64;

  webserver.processConnection(buff, &len);
}

