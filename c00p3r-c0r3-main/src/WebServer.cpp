#include "WebServer.h"
#include "configs.h"
#include "WiFiScan.h"
#include "deauth.h"
#include "Blespam.h"
#include "BlueDucky.h"
#include <Arduino.h>

WebServer::WebServer() : server(80) {}

void WebServer::begin() {
    if (initialized) return;
    
    // Setup WiFi
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Copper_Core", "k00p3r124");
    
    // Initialize modules
    WiFiScan wifi_scan;
    wifi_scan.init();
    BlueDucky blueducky;
    blueducky.init();
    
    // Setup routes
    setupRoutes();
    
    // Start server
    server.begin();
    initialized = true;
    Serial.println("Web server started");
}

void WebServer::setupRoutes() {
    // Root route
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        handleRoot(request);
    });

    // WiFi scan route
    server.on("/scan", HTTP_GET, [this](AsyncWebServerRequest *request) {
        String result = "WiFi Scan Results:\n";
        // Add WiFi scan functionality here
        request->send(200, "text/plain", result);
    });

    // Deauth route
    server.on("/deauth", HTTP_POST, [this](AsyncWebServerRequest *request) {
        // Add deauth functionality here
        request->send(200, "text/plain", "Deauth started");
    });

    // BLE spam route
    server.on("/blespam", HTTP_POST, [this](AsyncWebServerRequest *request) {
        // Add BLE spam functionality here
        request->send(200, "text/plain", "BLE spam started");
    });

    // BlueDucky route
    server.on("/blueducky", HTTP_POST, [this](AsyncWebServerRequest *request) {
        if (request->hasParam("payload", true)) {
            String payload = request->getParam("payload", true)->value();
            // Execute BlueDucky payload
            request->send(200, "text/plain", "BlueDucky payload executed");
        } else {
            request->send(400, "text/plain", "Missing payload");
        }
    });

    // ESP32 Flasher route
    server.on("/flash", HTTP_POST, [this](AsyncWebServerRequest *request) {
        if (request->hasParam("firmware", true)) {
            String firmware = request->getParam("firmware", true)->value();
            // Handle firmware flashing
            request->send(200, "text/plain", "Firmware flashing started");
        } else {
            request->send(400, "text/plain", "Missing firmware file");
        }
    });

    // Evil Portal routes
    server.on("/evilportal/start", HTTP_POST, [this](AsyncWebServerRequest *request) {
        // Start Evil Portal
        request->send(200, "text/plain", "Evil Portal started");
    });

    server.on("/evilportal/stop", HTTP_POST, [this](AsyncWebServerRequest *request) {
        // Stop Evil Portal
        request->send(200, "text/plain", "Evil Portal stopped");
    });

    // 404 handler


    server.onNotFound([this](AsyncWebServerRequest *request) {
        handleNotFound(request);
    });
}

void WebServer::handleRoot(AsyncWebServerRequest *request) {
    String html = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <title>K00p3r UI</title>
            <style>
                body { font-family: Arial, sans-serif; text-align: center; }
                h1 { color: #4CAF50; }
                button { padding: 10px 20px; font-size: 16px; margin: 5px; }
                textarea { width: 80%; height: 100px; margin: 10px; }
            </style>
        </head>
        <body>
            <h1>Welcome to CC UI!</h1>
            <button onclick="startScan()">WiFi Scan</button>
            <button onclick="startDeauth()">Deauth</button>
            <button onclick="startBleSpam()">BLE Spam</button>
            <div>
                <textarea id="payload" placeholder="Enter BlueDucky payload"></textarea>
            <button onclick="startBlueDucky()">Run BlueDucky</button>
            </div>
            <div>
                <input type="file" id="firmware" accept=".bin">
            <button onclick="startFlashing()">Flash Firmware</button>
            </div>
            <div>
                <button onclick="startEvilPortal()">Start Evil Portal</button>
                <button onclick="stopEvilPortal()">Stop Evil Portal</button>
            </div>
            <script>


                async function startScan() {
                    const response = await fetch('/scan');
                    alert(await response.text());
                }
                async function startDeauth() {
                    const response = await fetch('/deauth', {method: 'POST'});
                    alert(await response.text());
                }
                async function startBleSpam() {
                    const response = await fetch('/blespam', {method: 'POST'});
                    alert(await response.text());
                }
                async function startBlueDucky() {
                    const payload = document.getElementById('payload').value;
                    const response = await fetch('/blueducky', {
                        method: 'POST',
                        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
                        body: 'payload=' + encodeURIComponent(payload)
                    });
                    alert(await response.text());
                }

                async function startFlashing() {
                    const fileInput = document.getElementById('firmware');
                    if (fileInput.files.length > 0) {
                        const formData = new FormData();
                        formData.append('firmware', fileInput.files[0]);
                        const response = await fetch('/flash', {
                            method: 'POST',
                            body: formData
                        });
                        alert(await response.text());
                    } else {
                        alert('Please select a firmware file');
                    }
                }

                async function startEvilPortal() {
                    const response = await fetch('/evilportal/start', {
                        method: 'POST'
                    });
                    alert(await response.text());
                }

                async function stopEvilPortal() {
                    const response = await fetch('/evilportal/stop', {
                        method: 'POST'
                    });
                    alert(await response.text());
                }
            </script>


        </body>
        </html>
    )";
    
    request->send(200, "text/html", html);
}

void WebServer::handleNotFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void WebServer::processRequests() {
    // Process incoming requests
    // AsyncWebServer handles this automatically
}

bool WebServer::isInitialized() const {
    return initialized;
}
