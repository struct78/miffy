
void routes_default( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete )
{
  server.httpSuccess();
  
  if (type == WebServer::GET)
  {
    /* this defines some HTML text in read-only memory aka PROGMEM.
     * This is needed to avoid having the string copied to our limited
     * amount of RAM. */
    P(helloMsg) = "<h1>Miffy</h1>";

    /* this is a special form of print that outputs from PROGMEM */
    server.printP(helloMsg);
  } else {
    server.httpFail();
    server.print("{ \"error\": \"Method not allowed\" }");
  }
}

void routes_api_status( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
  server.httpSuccess("application/json");
  
  if (type == WebServer::GET)
  {
    server.print("{ \"power\": ");
    server.print( get_neomatrix_power() );
    server.print(",");
    server.print("\"speed\": ");
    server.print( get_neomatrix_speed() );
    server.print(",");
    server.print("\"brightness\": ");
    server.print( get_neomatrix_brightness() );
    server.print("}");
  } else {
    server.httpFail();
    server.print("{ \"error\": \"Method not allowed\" }");
  }
}

void routes_api_speed( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
  int speed = theta;

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


void routes_api_brightness( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
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


void routes_api_power( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
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


int param_bool( WebServer server, const char *key ) {
  bool returnValue = false;
  bool repeat;
  char name[16], value[16];

  do
  {
    repeat = server.readPOSTparam(name, 16, value, 16);
    if (strcmp(name, key) == 0)
    {
      returnValue = (bool)value;
    }

  } while (repeat);

  return returnValue;
}

