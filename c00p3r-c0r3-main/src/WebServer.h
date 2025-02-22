#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESPAsyncWebServer.h>
#include <WiFi.h>

class WebServer {
private:
    AsyncWebServer server;
    bool initialized = false;

    void setupRoutes();
    void handleRoot(AsyncWebServerRequest *request);
    void handleNotFound(AsyncWebServerRequest *request);

public:
    WebServer();
    void begin();
    void processRequests();
    bool isInitialized() const;
};

#endif
