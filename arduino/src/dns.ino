WiFiClient client;
IPAddress ip;

bool dns_finished = false;

/**
 * @name wifi_setup
 * @description Connects to the Wi-Fi and sets up API routes.
 * @param {IPAddress} addr - The local IP address.
 * @return {void}
**/
void update_dns( IPAddress addr ) {
	ip = addr;
	dns_finished = false;
	if (client.connect("api.dynu.com", 80)) {
		#if defined( DEVELOPMENT )
		Serial.println( F("Updating DNS") );
		#endif
		client.print( "GET /nic/update?hostname=" );
		client.print( dynamic_hostname );
		client.print( "&myip=" );
		client.print( ip );
		client.print( "&password=" );
		client.print( dynamic_hostname_password );
		client.println( " HTTP/1.1" );
		client.println( "Host: api.dynu.com" );
		client.println( "User Agent: Wi-Fi Nightlight/1.0" );
		client.println( "Connection: close" );
		client.println();
		#if defined( DEVELOPMENT )
		Serial.println( F("Updated dynamic DNS!") );
		#endif
	} else {
		#if defined( DEVELOPMENT )
		Serial.println( F("Updating dynamic DNS failed") );
		#endif
	}
}

/**
 * @name dns_loop
 * @description Updates the dynamic DNS again.
 * @return {void}
**/
void dns_loop() {
	if ( !dns_finished ) {
		while ( client.available() ) {
			char c = client.read();
		}

		// if the server's disconnected, stop the client:
		if ( !client.connected() ) {
			client.stop();
			dns_finished = true;
		}
	}

	if ( millis() % 60000 == 0 ) {
		update_dns( ip );
	}
}
