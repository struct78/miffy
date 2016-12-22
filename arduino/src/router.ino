/**
 * @name routes_default
 * @methods GET
 * @description The default route for the web server. Returns simple markup.
 * @param {WebServer} server - Pointer to the webserver object in {wifi.info}
 * @param {WebServer::ConnectionType} type - The HTTP request method
 * @param {char} url_tail - Contains the part of the URL that wasn't matched against the registered command table.
 * @param {bool} tail_complete - is true if the complete URL fit in url_tail, false if part of it was lost because the buffer was too small.
 * @return {void}
**/
void routes_default( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete )
{
	server.httpSuccess();

	if (type == WebServer::GET)
	{
		P(helloMsg) = "<h1>Miffy</h1>";
		server.printP(helloMsg);
	} else {
		server.httpFail();
		server.print("{ \"error\": \"Method not allowed\" }");
	}
}

/**
 * @name routes_api_status
 * @description Gets the status as a JSON object.
 * @methods GET
 * @param {WebServer} server - Pointer to the webserver object in {wifi.info}
 * @param {WebServer::ConnectionType} type - The HTTP request method
 * @param {char} url_tail - Contains the part of the URL that wasn't matched against the registered command table.
 * @param {bool} tail_complete - is true if the complete URL fit in url_tail, false if part of it was lost because the buffer was too small.
 * @return {void}
**/
void routes_api_status( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
	Serial.println("/api/status");
	server.httpSuccess("application/json");

	if (type == WebServer::GET)
	{
		server.print("{ \"result\": {");
		server.print("\"power\": ");
		server.print( get_neomatrix_power() );
		server.print(",");
		server.print("\"speed\": ");
		server.print( get_neomatrix_speed() );
		server.print(",");
		server.print("\"brightness\": ");
		server.print( get_neomatrix_brightness() );
		server.print(",");
		server.print("\"contrast\": ");
		server.print( get_neomatrix_contrast() );
		server.print("}");
		server.print("}");
	} else {
		server.httpFail();
		server.print("{ \"error\": \"Method not allowed\" }");
	}
}

/**
 * @name routes_api_speed
 * @description Sets the speed.
 * @methods POST, GET
 * @param {WebServer} server - Pointer to the webserver object in {wifi.info}
 * @param {WebServer::ConnectionType} type - The HTTP request method
 * @param {char} url_tail - Contains the part of the URL that wasn't matched against the registered command table.
 * @param {bool} tail_complete - is true if the complete URL fit in url_tail, false if part of it was lost because the buffer was too small.
 * @return {void}
**/
void routes_api_speed( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
	Serial.println("/api/speed");

	if (type == WebServer::POST)
	{
		set_neomatrix_speed( param_int( server, "speed" ) );

		server.httpSuccess("application/json");
		server.print("{ \"result\": ");
		server.print( (float)get_neomatrix_speed() );
		server.print(" }");
	} else {
		server.httpFail();
		server.print("{ \"error\": \"Method not allowed\" }");
	}
}

/**
 * @name routes_api_brightness
 * @description Sets the speed.
 * @methods POST
 * @param {WebServer} server - Pointer to the webserver object in {wifi.info}
 * @param {WebServer::ConnectionType} type - The HTTP request method
 * @param {char} url_tail - Contains the part of the URL that wasn't matched against the registered command table.
 * @param {bool} tail_complete - is true if the complete URL fit in url_tail, false if part of it was lost because the buffer was too small.
 * @return {void}
**/
void routes_api_brightness( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
	Serial.println("/api/brightness");

	if (type == WebServer::POST)
	{
		set_neomatrix_brightness( param_int( server, "brightness" ) );

		server.httpSuccess("application/json");
		server.print("{ \"result\": ");
		server.print( (float)get_neomatrix_brightness() );
		server.print(" }");
	} else {
		server.httpFail();
		server.print("{ \"error\": \"Method not allowed\" }");
	}
}



/**
 * @name routes_api_contrast
 * @description Sets the contrast.
 * @methods POST
 * @param {WebServer} server - Pointer to the webserver object in {wifi.info}
 * @param {WebServer::ConnectionType} type - The HTTP request method
 * @param {char} url_tail - Contains the part of the URL that wasn't matched against the registered command table.
 * @param {bool} tail_complete - is true if the complete URL fit in url_tail, false if part of it was lost because the buffer was too small.
 * @return {void}
**/
void routes_api_contrast( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
	Serial.println("/api/contrast");

	if (type == WebServer::POST)
	{
		set_neomatrix_contrast( param_int( server, "contrast" ) );

		server.httpSuccess("application/json");
		server.print("{ \"result\": ");
		server.print( (float)get_neomatrix_contrast() );
		server.print(" }");
	} else {
		server.httpFail();
		server.print("{ \"error\": \"Method not allowed\" }");
	}
}

/**
 * @name routes_api_power
 * @description Sets the power status.
 * @methods POST
 * @param {WebServer} server - Pointer to the webserver object in {wifi.info}
 * @param {WebServer::ConnectionType} type - The HTTP request method
 * @param {char} url_tail - Contains the part of the URL that wasn't matched against the registered command table.
 * @param {bool} tail_complete - is true if the complete URL fit in url_tail, false if part of it was lost because the buffer was too small.
 * @return {void}
**/
void routes_api_power( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
	Serial.println("/api/power");

	if (type == WebServer::POST)
	{
		set_neomatrix_power( param_bool( server, "power" ) );

		server.httpSuccess("application/json");
		server.print("{ \"result\": ");
		server.print( (bool)get_neomatrix_power() );
		server.print(" }");
	} else {
		server.httpFail();
		server.print("{ \"error\": \"Method not allowed\" }");
	}
}

/**
 * @name routes_api_pattern
 * @description Sets the pattern.
 * @methods POST
 * @param {WebServer} server - Pointer to the webserver object in {wifi.info}
 * @param {WebServer::ConnectionType} type - The HTTP request method
 * @param {char} url_tail - Contains the part of the URL that wasn't matched against the registered command table.
 * @param {bool} tail_complete - is true if the complete URL fit in url_tail, false if part of it was lost because the buffer was too small.
 * @return {void}
**/
void routes_api_pattern( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
	Serial.println("/api/pattern");

	if (type == WebServer::POST)
	{
		set_neomatrix_pattern( param_int( server, "pattern" ) );

		server.httpSuccess("application/json");
		server.print("{ \"result\": \"");
		server.print( (int)get_neomatrix_pattern() );
		server.print("\" }");
	} else {
		server.httpFail();
		server.print("{ \"error\": \"Method not allowed\" }");
	}
}

/**
 * @name param_int
 * @description Converts a form parameter to an integer.
 * @methods POST
 * @param {WebServer} server - Pointer to the webserver object in {wifi.info}.
 * @param {char*} key - The key of the form parameter to look for.
 * @return {void}
**/
int param_int( WebServer server, const char *key ) {
	int returnValue = 0;
	bool repeat;
	char name[16], value[16];

	do
	{
		repeat = server.readPOSTparam(name, 16, value, 16);
		if (strcmp(name, key) == 0)
		{
			returnValue = strtoul(value, NULL, 10);
		}

	} while (repeat);

	return returnValue;
}

/**
 * @name param_bool
 * @description Converts a form parameter to a boolean.
 * @methods POST
 * @param {WebServer} server - Pointer to the webserver object in {wifi.info}.
 * @param {char*} key - The key of the form parameter to look for.
 * @return {bool}
**/
bool param_bool( WebServer server, const char *key ) {
	bool returnValue = false;
	bool repeat;
	char name[16], value[16];

	do
	{
		repeat = server.readPOSTparam(name, 16, value, 16);
		if (strcmp(name, key) == 0)
		{
			if ( value == "true" ) {
				returnValue = true;
			}
		}

	} while (repeat);

	return returnValue;
}
