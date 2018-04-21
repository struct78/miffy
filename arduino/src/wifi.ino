#define PREFIX ""
WebServer webserver(PREFIX, 80);

int wifi_status = WL_IDLE_STATUS;

/**
 * @name wifi_setup
 * @description Connects to the Wi-Fi and sets up API routes.
 * @return {void}
**/
void wifi_setup() {
	// Check for the presence of the shield:
	if ( WiFi.status() == WL_NO_SHIELD ) {
		#if defined( DEVELOPMENT )
		Serial.println( F("WiFi shield not present") );
		#endif
		while(true);
	}

	// Attempt to connect to Wifi network:
	while ( wifi_status != WL_CONNECTED ) {
		#if defined( DEVELOPMENT )
		Serial.print( F("Attempting to connect to SSID: ") );
		Serial.println( ssid );
		#endif

		if ( strcmp(pass, "") != 0 ) {
			wifi_status = WiFi.begin(ssid, pass);
		} else {
			wifi_status = WiFi.begin(ssid);
		}

		delay(5000);
	}

	// Setup API HTTP routes
	webserver.setDefaultCommand(&routes_default);
	webserver.addCommand("api/status", &routes_api_status);
	webserver.addCommand("api/power", &routes_api_power);
	webserver.addCommand("api/speed", &routes_api_speed);
	webserver.addCommand("api/brightness", &routes_api_brightness);
	webserver.addCommand("api/contrast", &routes_api_contrast);
	webserver.addCommand("api/pattern", &routes_api_pattern);
	webserver.addCommand("api/health", &routes_api_health);
	webserver.begin();

	// The local IP address
	IPAddress ip = WiFi.localIP();
	#if defined( DEVELOPMENT )
	Serial.print( F("IP Address: ") );
	Serial.println( ip );
	#endif

	// Update the dynamic DNS
	update_dns( ip );
}

/**
 * @name wifi_loop
 * @description Listens for HTTP connections.
 * @return {void}
**/
void wifi_loop() {
	if (wifi_status != WL_CONNECTED)
		return;

	char buff[64];
	int len = 64;

	// Process any connections
	webserver.processConnection(buff, &len);
}
