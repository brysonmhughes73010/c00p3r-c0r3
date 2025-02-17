THIS IS NOT FINSIHED!! YET TO BE TESTED!!!

MAKE BY AI AND A SKIDDY CODE STEALER
(yes i just exposed myself but idrc)
(have fun, USE RESPONSIBLY)
ANY POTENTIAL DAMAGE CAUSED BY THIS SOFTWARE IS NOT MY FAULT!
FOLLOW YOUR LAWS!!! (highly recommended lmao)
most credit goes out to the code makers of course

# K00P3R (C0PP3R-C0R3)

K00P3R (C0PP3R-C0R3) is a versatile tool for managing and interacting with your ESP32 device. It provides various functionalities such as WiFi scanning, device information, BLE spam, and more.

## Features

- **WiFi Scanning**: Scan for available WiFi networks.
- **Device Information**: Display information about the ESP32 device.
- **BLE Spam**: Advertise BLE packets from predefined devices.
- **BLE Beacon**: Set up an iBeacon with custom UUID, major, and minor values.
- **Light/Dark Mode**: Toggle between light and dark modes on the web interface.

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

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/brysonmhughes73010/k00p3r-c0r3.git
   cd k00p3r-c0r3
   ```

2. **Install PlatformIO**: Follow the instructions on the PlatformIO website to install PlatformIO.

3. **Open the Project**: Open the project folder in your preferred code editor (e.g., Visual Studio Code).

4. **Upload Files to SPIFFS**: Place the logo.png file in the data/images directory. Use the PlatformIO Upload File System image task to upload the files to the ESP32 filesystem.

5. **Build and Upload the Firmware**: Use the PlatformIO Build and Upload tasks to compile and upload the firmware to the ESP32.

## Usage

1. **Connect to the WiFi Access Point**: Connect to the WiFi access point created by the ESP32. The SSID is COPPER-CORE and the password is c0pp3rmin3.

2. **Access the Web Interface**: Open a web browser and navigate to http://k00p3r.local.

3. **Use the Features**:
   - **Scan for WiFi**: Click the "Scan for WiFi" button to scan for available WiFi networks.
   - **Device Info**: Click the "Device Info" button to display information about the ESP32 device.
   - **Restart**: Click the "Restart" button to restart the ESP32.
   - **BLE Spam**: Click the "BLE Spam" button to start advertising BLE packets.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request on GitHub.

## Acknowledgements

- PlatformIO
- Arduino
- ESPAsyncWebServer
- AsyncTCP

# Code Citations

## License: MIT
https://github.com/PleXone2019/ESP32Marauder/tree/c871b1b2abda33050a31567cec301ed917d64d69/esp32_marauder/MenuFunctions.cpp

```
menu_icons[][66] = {
    {0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0x37, 0xFF, 0xFF, 0x3A, // Attack: 0
    0xFF, 0xFF, 0x39, 0xFF, 0xBF, 0x3C, 0xFF, 0x7F, 0x3E
```

