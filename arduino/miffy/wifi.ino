char ssid[] = "Axolotl";      // your network SSID (name) 
char pass[] = "sZFLMHovpz";   // your network password

//char ssid[] = "Dave's Phone";
//char pass[] = "Evelyn23";

//char ssid[] = "IE Guest";
//char pass[] = "triangle";

#define PREFIX ""
WebServer webserver(PREFIX, 80);

int wifi_status = WL_IDLE_STATUS;

void wifi_setup() {
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( wifi_status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    wifi_status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  } 
  
  webserver.setDefaultCommand(&routes_default);

  webserver.addCommand("api/on", &routes_api_on);
  webserver.addCommand("api/off", &routes_api_off);
  webserver.addCommand("api/status", &routes_api_status);
  
  /* start the server to wait for connections */
  webserver.begin();

  // you're connected now, so print out the status:
  printWifiStatus();
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void wifi_loop() {
  // listen for incoming clients
  char buff[64];
  int len = 64;

  /* process incoming connections one at a time forever */
  webserver.processConnection(buff, &len);
}

