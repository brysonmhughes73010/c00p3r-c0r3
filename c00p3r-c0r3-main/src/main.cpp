#include "EvilPortal.h"
#include "WiFiScan.h"
#include "configs.h"
#include <Arduino.h>

// Global instances
EvilPortal evil_portal;
WiFiScan wifi_scan;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize WiFi scan
  wifi_scan.init();
  
  // Initialize Evil Portal
  evil_portal.setup();
  
  // Create empty lists for SSIDs and Access Points
  LinkedList<ssid> ssids;
  LinkedList<AccessPoint> access_points;
  
  // Start the Evil Portal
  if (evil_portal.begin(&amp;ssids, &amp;access_points)) {
