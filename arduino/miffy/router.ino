
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
  }
}

void routes_api_on( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
  Serial.println("On API");
  server.httpSuccess("application/json");
  
  if (type == WebServer::GET)
  {
    neomatrix_on();
    server.print("{ result: 'on' }");
  }
}

void routes_api_off( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
  Serial.println("Off API");
  server.httpSuccess("application/json");
  
  if (type == WebServer::GET)
  {
    neomatrix_off();
    server.print("{ result: 'off' }");
  }
}

void routes_api_status( WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete ) {
  server.httpSuccess("application/json");
  
  if (type == WebServer::GET)
  {
    server.print("{");
    server.print(" result: ");
    server.print(neomatrix_status());
    server.print("}");
  }
}

