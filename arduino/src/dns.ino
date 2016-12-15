WiFiClient client;
IPAddress ip;

long lastDnsUpdate = 0;
long interval = 1000000;
bool dns_finished = false;

void update_dns( IPAddress addr ) {
	ip = addr;
	dns_finished = false;
	if (client.connect("api.dynu.com", 80)) {
		Serial.println("Updating DNS");
		client.print( "GET /nic/update?hostname=" );
		client.print( dynamic_hostname );
		client.print( "&myip=" );
		client.print( ip );
		client.print( "&password=" );
		client.print( dynamic_hostname_password );
		client.println( " HTTP/1.1" );
		client.println( "Host: api.dynu.com" );
		client.println( "User Agent: Miffy Lamp Arduino/1.0" );
		client.println( "Connection: close" );
		client.println();
	} else {
		Serial.println("Updating dynamic DNS failed");
	}
}


void dns_loop() {
	if ( !dns_finished ) {
		while (client.available()) {
			char c = client.read();
		}

		// if the server's disconnected, stop the client:
		if (!client.connected()) {
			client.stop();
			dns_finished = true;
		}
	}

	unsigned long current = millis();
	if ( current - lastDnsUpdate > interval) {
		lastDnsUpdate = current;
		update_dns( ip );
	}
}
