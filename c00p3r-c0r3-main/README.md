# K00P3R (C0PP3R-C0R3)

K00P3R (C0PP3R-C0R3) is a versatile tool for managing and interacting with your ESP32 device. It provides various functionalities such as WiFi scanning, device information, BLE spam, and more.

## Features

- **WiFi Scanning**: Scan for available WiFi networks
- **WiFi Deauthentication**: Perform deauthentication attacks on WiFi networks
- **Device Information**: Display information about the ESP32 device
- **BLE Spam**: Advertise BLE packets from predefined devices
- **BLE Beacon**: Set up an iBeacon with custom UUID, major, and minor values
- **ESP32 Flasher**: Built-in firmware flashing capability
- **Cross-Platform Support**: Works on Windows, iOS, and Android
- **GitHub Pages Deployment**: Host the flasher on GitHub Pages

## Hardware Requirements

- ESP32 development board

## Software Requirements

- PlatformIO
- Arduino framework

## Libraries Used

- [NTPClient](https://platformio.org/lib/show/551/NTPClient)
- [ESPAsyncWebServer](https://platformio.org/lib/show/306/ESPAsyncWebServer)
- [AsyncTCP](https://platformio.org/lib/show/1826/AsyncTCP)
- [ArduinoJson](https://platformio.org/lib/show/64/ArduinoJson)
- [GyverDB](https://platformio.org/lib/show/1234/GyverDB)

## Setup Instructions

### Windows
1. Install Python 3.x
2. Install PlatformIO Core
3. Clone the repository:
   ```sh
   git clone https://github.com/brysonmhughes73010/k00p3r-c0r3.git
   cd k00p3r-c0r3
   ```
4. Install dependencies:
   ```sh
   pip install -r requirements.txt
   ```

### iOS
1. Install Pythonista from App Store
2. Clone the repository using Working Copy app
3. Install required Python packages

### Android
1. Install Termux from Play Store
2. Clone the repository:
   ```sh
   git clone https://github.com/brysonmhughes73010/k00p3r-c0r3.git
   cd k00p3r-c0r3
   ```
3. Install dependencies:
   ```sh
   pkg install python
   pip install -r requirements.txt
   ```

## ESP32 Flasher

The built-in ESP32 flasher allows you to:
- Flash firmware to ESP32 devices
- Manage multiple firmware versions
- Verify flash integrity

To use the flasher:
1. Connect your ESP32 via USB
2. Run the flasher:
   ```sh
   python flasher.py
   ```

## GitHub Pages Deployment

To deploy the flasher to GitHub Pages:
1. Create a new GitHub repository
2. Push the flasher code to the `gh-pages` branch
3. Enable GitHub Pages in repository settings

The flasher will be available at:
```
https://<your-username>.github.io/<repository-name>
```

## Usage

1. **Connect to the WiFi Access Point**: Connect to the WiFi access point created by the ESP32. The SSID is COPPER-CORE and the password is c0pp3rmin3.
2. **Access the Web Interface**: Open a web browser and navigate to http://k00p3r.local.
3. **Use the Features**:
   - **Scan for WiFi**: Click the "Scan for WiFi" button
   - **WiFi Deauthentication**: Select a network and click "Deauthenticate"
   - **Device Info**: Click the "Device Info" button
   - **Restart**: Click the "Restart" button
   - **BLE Spam**: Click the "BLE Spam" button
   - **Flasher**: Access the ESP32 flasher interface

## Contributing

Contributions are welcome! Please open an issue or submit a pull request on GitHub.

## Acknowledgements

- PlatformIO
- Arduino
- ESPAsyncWebServer
- AsyncTCP
