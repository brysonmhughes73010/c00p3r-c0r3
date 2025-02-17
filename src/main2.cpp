// Replace with your network credentials
const char* ssid = "COPPER-CORE";
const char* password = "c0pp3rmin3";

// Create an instance of the web server
WebServer server(80);

// TFT display settings
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// BLE server
BLEServer *pServer = NULL;
BLEAdvertising *pAdvertising = NULL;
BLECharacteristic *pCharacteristic = NULL;
bool deviceConnected = false;
uint8_t value = 0;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("deviceConnected = true");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("deviceConnected = false");
      // Restart advertising to be visible and connectable again
      BLEAdvertising* pAdvertising;
      pAdvertising = pServer->getAdvertising();
      pAdvertising->start();
      Serial.println("iBeacon advertising restarted");
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        Serial.println();
        Serial.println("*********");
      }
    }
};

void init_service() {
  pAdvertising->stop();
  
  // Create the BLE Service
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID));

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());
  pAdvertising->addServiceUUID(BLEUUID(SERVICE_UUID));

  // Start the service
  pService->start();
  pAdvertising->start();
}

void init_beacon() {
  pAdvertising->stop();

  // iBeacon
  BLEBeacon myBeacon;
  myBeacon.setManufacturerId(0x4c00);
  myBeacon.setMajor(5);
  myBeacon.setMinor(88);
  myBeacon.setSignalPower(0xc5);
  myBeacon.setProximityUUID(BLEUUID(BEACON_UUID_REV));
  BLEAdvertisementData advertisementData;
  advertisementData.setFlags(0x1A);
  advertisementData.setManufacturerData(myBeacon.getData());
  pAdvertising->setAdvertisementData(advertisementData);
  pAdvertising->start();
}

void setup() {
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Initialize TFT display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("K00P3R (C0PP3R-C0R3)");

  // Set up the WiFi access point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Initialize mDNS
  if (!MDNS.begin("k00p3r")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  // Initialize BLE
  BLEDevice::init("K00P3R");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLEUUID((uint16_t)0x1812)); // Example UUID
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  pAdvertising->start();

  // Initialize BLE service and beacon
  init_service();
  init_beacon();

  // Define the web server routes
  server.on("/", handleRoot);
  server.on("/scan", handleScan);
  server.on("/info", handleInfo);
  server.on("/restart", handleRestart);
  server.on("/ble_spam", handleBLESpam);
  server.on("/logo.png", handleLogo); // Route to serve the logo image
  server.onNotFound(handleNotFound);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
  MDNS.update();

  if (deviceConnected) {
    Serial.printf("*** NOTIFY: %d ***\n", value);
    pCharacteristic->setValue(&value, 1);
    pCharacteristic->notify();
    value++;
  }

  delay(2000);
}

void handleRoot() {
  String html = R"rawliteral(
  <html>
  <head>
    <title>K00P3R (C0PP3R-C0R3)</title>
    <style>
      body { font-family: Arial, sans-serif; text-align: center; padding: 50px; }
      h1 { color: #333; }
      button { padding: 10px 20px; margin: 10px; }
      .logo { width: 100px; }
      .dropdown { position: relative; display: inline-block; }
      .dropdown-content { display: none; position: absolute; background-color: #f9f9f9; min-width: 160px; box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2); z-index: 1; }
      .dropdown-content a { color: black; padding: 12px 16px; text-decoration: none; display: block; }
      .dropdown-content a:hover { background-color: #f1f1f1; }
      .dropdown:hover .dropdown-content { display: block; }
      .dropdown:hover .dropbtn { background-color: #3e8e41; }
      .toggle { position: absolute; top: 10px; left: 10px; }
    </style>
  </head>
  <body>
    <div class="toggle">
      <label for="mode">Mode:</label>
      <select id="mode" onchange="toggleMode()">
        <option value="light">Light</option>
        <option value="dark">Dark</option>
      </select>
    </div>
    <img src="/logo.png" alt="Logo" class="logo">
    <h1>Welcome to K00P3R (C0PP3R-C0R3)</h1>
    <p>K00P3R (C0PP3R-C0R3) is a versatile tool for managing and interacting with your ESP32 device. It provides various functionalities such as WiFi scanning, device information, BLE spam, and more.</p>
    <div class="dropdown">
      <button class="dropbtn">Select Function</button>
      <div class="dropdown-content">
        <a href="/scan">Scan for WiFi</a>
        <a href="/info">Device Info</a>
        <a href="/restart">Restart</a>
        <a href="/ble_spam">BLE Spam</a>
      </div>
    </div>
    <script>
      function toggleMode() {
        var mode = document.getElementById("mode").value;
        if (mode === "dark") {
          document.body.style.backgroundColor = "#333";
          document.body.style.color = "#fff";
        } else {
          document.body.style.backgroundColor = "#fff";
          document.body.style.color = "#000";
        }
      }
    </script>
  </body>
  </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void handleScan() {
  int n = WiFi.scanNetworks();
  String html = "<html><head><title>WiFi Scan</title><style>body { font-family: Arial, sans-serif; text-align: center; padding: 50px; } h1 { color: #333; }</style></head><body><h1>WiFi Networks</h1><ul>";
  for (int i = 0; i < n; ++i) {
    html += "<li>" + String(WiFi.SSID(i)) + " (" + String(WiFi.RSSI(i)) + " dBm)</li>";
  }
  html += "</ul><p><a href=\"/\">Back</a></p></body></html>";
  server.send(200, "text/html", html);
}

void handleInfo() {
  String html = "<html><head><title>Device Info</title><style>body { font-family: Arial, sans-serif; text-align: center; padding: 50px; } h1 { color: #333; }</style></head><body><h1>Device Info</h1>";
  html += "<p>Chip ID: " + String((uint32_t)ESP.getEfuseMac()) + "</p>";
  html += "<p>Flash Chip Size: " + String(ESP.getFlashChipSize() / 1024 / 1024) + " MB</p>";
  html += "<p>Free Heap: " + String(ESP.getFreeHeap()) + " bytes</p>";
  html += "<p><a href=\"/\">Back</a></p></body></html>";
  server.send(200, "text/html", html);
}

void handleRestart() {
  String html = "<html><head><title>Restarting</title><style>body { font-family: Arial, sans-serif; text-align: center; padding: 50px; } h1 { color: #333; }</style></head><body><h1>Restarting...</h1></body></html>";
  server.send(200, "text/html", html);
  delay(1000);
  ESP.restart();
}

void handleBLESpam() {
  String html = "<html><head><title>BLE Spam</title><style>body { font-family: Arial, sans-serif; text-align: center; padding: 50px; } h1 { color: #333; }</style></head><body><h1>BLE Spam Started</h1><p>Advertising BLE packets...</p><p><a href=\"/\">Back</a></p></body></html>";
  server.send(200, "text/html", html);
  for (int i = 0; i < sizeof(DEVICES) / sizeof(DEVICES[0]); i++) {
    BLEAdvertisementData advertisementData;
    advertisementData.setManufacturerData(std::string((char*)DEVICES[i], 31));
    pAdvertising->setAdvertisementData(advertisementData);
    pAdvertising->start();
    delay(100);
  }
}

void handleLogo() {
  File logo = SPIFFS.open("/images/logo.png", "r");
  if (!logo) {
    server.send(404, "text/plain", "Logo not found");
    return;
  }
  server.streamFile(logo, "image/png");
  logo.close();
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}
