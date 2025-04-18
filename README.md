# Soil Moisture Monitoring System - ESP32

## Overview
This project is a soil moisture monitoring system using an ESP32 microcontroller and a 2-pin soil moisture sensor. The system connects to a WiFi network, reads soil moisture levels, and serves the data through a web server, displaying real-time information on the soil condition (whether it needs watering or is good).

## Components Needed
- **ESP32 Development Board**
- **2-pin Soil Moisture Sensor**
- **10k Ohm Resistor**
- **Jumper Wires**
- **Breadboard (Optional)**

## Circuit Diagram
### Soil Moisture Sensor Connection
| **Component**           | **ESP32 Pin**       | **Soil Moisture Sensor Pin** | **Description**                              |
|-------------------------|---------------------|-----------------------------|----------------------------------------------|
| **Soil Moisture Sensor**| VCC                 | VCC                         | Connect the VCC pin of the sensor to the **3.3V** pin of the ESP32 for power supply. |
| **Soil Moisture Sensor**| GND                 | GND                         | Connect the GND pin of the sensor to the **GND** pin of the ESP32 for grounding. |
| **Soil Moisture Sensor**| SIGNAL              | Signal Pin                  | Connect the Signal pin of the sensor to **GPIO34 (ADC)** of the ESP32 for analog input. |
| **Resistor (10kΩ)**     | Between SIGNAL Pin  | GND                         | Connect a 10kΩ resistor between the **Signal Pin** and **GND** to form a voltage divider. This helps ensure the sensor's output voltage is readable by the ADC pin of the ESP32. |

### Circuit Connections:
1. **VCC (Soil Moisture Sensor)** → **3.3V (ESP32)**
2. **GND (Soil Moisture Sensor)** → **GND (ESP32)**
3. **Signal Pin (Soil Moisture Sensor)** → **GPIO34 (ESP32)**
4. **10kΩ Resistor** → Connect between **Signal Pin** and **GND** (Ground).

## Software Setup

### Libraries Required
- **WiFi.h**: For connecting to WiFi.
- **WebServer.h**: To handle HTTP requests and serve web pages.

### WiFi Credentials
Make sure to replace the default WiFi credentials in the code with your own:

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

## Web Interface
The web interface displays the current soil moisture level as a percentage, updating every second. The status is shown as either "Soil is good" or "Needs Watering" based on the moisture level.

## Functionality
- **WiFi Setup**: The ESP32 will connect to the WiFi network using the provided credentials.
- **Soil Moisture Calculation**: The analog reading from the soil moisture sensor is converted to a percentage.
- **Web Server**: The ESP32 serves a webpage that displays the current moisture level and status.
- **Serial Monitoring**: The system provides real-time serial output, showing raw ADC values and calculated moisture percentage.

## Accessing the Web Server
Once connected to WiFi, the ESP32 will output its IP address to the Serial Monitor. Open this IP address in a browser to view the moisture levels in real-time.

## Code Explanation
- **WiFi Connection**: The `connectWiFi()` function connects the ESP32 to your WiFi network.
- **Soil Moisture Calculation**: The soil moisture level is calculated by reading the analog value from GPIO34. The formula used for calculation is:
    ```cpp
    moistureLevel = (sensorValue / 4095.0) * 100;
    ```
    where `sensorValue` is the raw ADC value, and `4095` is the maximum value for a 12-bit ADC.
- **Web Interface**: The ESP32 serves a webpage with the current moisture level and a visual gauge indicating the soil condition. The page updates every second.
- **Serial Output Control**: You can stop or start the serial output by sending "STOP" or "START" commands via the Serial Monitor.

## Conclusion
This system allows you to monitor soil moisture levels remotely, making it ideal for applications such as automated irrigation systems or garden monitoring.
