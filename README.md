Soil Moisture Monitoring System with ESP32
Overview
This project involves using an ESP32 microcontroller to create a soil moisture monitoring system that can be accessed over a Wi-Fi network. The system reads moisture data from a 2-pin analog soil moisture sensor, processes the data, and displays it on a web page. The system also provides real-time feedback, indicating whether the soil needs watering based on the moisture level.

Key Features:
Real-time soil moisture data display via a web interface.

Wi-Fi-enabled for remote monitoring.

The analog soil moisture sensor provides continuous feedback about soil moisture.

Provides a gauge-style visual for the moisture level.

Status updates: The system shows whether the soil is in a healthy condition or needs watering.

Components Used
1. ESP32 Microcontroller
Purpose: The ESP32 is a low-power, high-performance microcontroller with integrated Wi-Fi and Bluetooth capabilities. It serves as the central processing unit in this project to collect sensor data, handle Wi-Fi communication, and serve the web page.

2. 2-pin Soil Moisture Sensor
Purpose: This sensor measures the moisture level of the soil and provides an analog voltage signal that corresponds to the soil's moisture content. The sensor is connected to an analog-to-digital converter (ADC) pin on the ESP32 for reading the moisture level.

3. Resistor (R)
Purpose: A 10kΩ pull-down resistor is used between the analog output pin of the sensor and ground (GND). This ensures a stable voltage reading and prevents floating values when the sensor is not active.

4. Power Supply
Purpose: The ESP32 requires a 3.3V or 5V supply, which powers the microcontroller and the connected soil moisture sensor.

Theory and Engineering Concepts
Soil Moisture Sensor: Working Principle
The soil moisture sensor typically works on the principle of resistivity or capacitance to measure the moisture content in the soil:

Resistive Type Sensors (commonly used in this project):

These sensors consist of two conductive probes that are placed in the soil.

The resistance between the probes decreases as the moisture content in the soil increases, because water is a good conductor of electricity.

The sensor outputs an analog voltage that is proportional to the resistance between the probes.

Capacitive Type Sensors (alternative):

These sensors measure the capacitance between two conductive plates, where the capacitance changes based on the moisture content of the soil.

In this project, we are using the resistive type soil moisture sensor, which provides an analog voltage output that is fed into the ADC (Analog to Digital Converter) pin of the ESP32.

Analog-to-Digital Conversion
The ESP32’s ADC (Analog-to-Digital Converter) reads the analog voltage from the soil moisture sensor and converts it to a digital value that can be processed by the microcontroller.

ADC Characteristics: The ESP32 has a 12-bit ADC, meaning the analog input is converted into a digital value between 0 to 4095 (corresponding to the voltage range of 0V to 3.3V).

Formula for Moisture Calculation:

cpp
Copy
Edit
moistureLevel = (sensorValue / 4095.0) * 100;
The sensorValue is the raw ADC value (between 0 and 4095), and dividing it by 4095.0 gives the normalized value in the range 0 to 1. By multiplying this by 100, we convert it to a percentage.

Wi-Fi Communication
The ESP32 is used to connect the system to a Wi-Fi network.

Once connected, the ESP32 hosts a web server that allows remote monitoring of the soil moisture levels.

Web Server: The ESP32’s web server listens on port 80 and serves HTML content to clients (e.g., web browsers) that connect to it.

Client-side JavaScript: The web page uses JavaScript to fetch the latest soil moisture data from the server every second and update the page dynamically.

Application Functionality
1. Wi-Fi Setup:
The ESP32 connects to a Wi-Fi network using the SSID (network name) and password.

It checks the connection status and prints the IP address to the serial monitor upon successful connection.

2. Reading Soil Moisture:
The soil moisture sensor continuously provides an analog signal, which is read by the ESP32’s ADC pin (GPIO 34 in the code).

The ADC value is processed to calculate the moisture percentage.

3. Web Server:
A simple HTML page is served, displaying the soil moisture data in a gauge-style format.

JavaScript is used to fetch the data from the ESP32 every second and update the page.

The moisture status is displayed as either “Soil is good!” or “Needs Watering!” based on the moisture level.

4. Control via Serial Monitor:
The system allows you to control whether serial output is active or not by sending START or STOP commands via the serial monitor.

Hardware Connections

Soil Moisture Sensor Pin	ESP32 Pin	Connection Description
VCC (Power)	3.3V or 5V	Connects the power pin of the soil moisture sensor to the 3.3V or 5V pin on the ESP32.
GND (Ground)	GND	Connects the ground pin of the soil moisture sensor to the GND on the ESP32.
Analog Output	GPIO 34	Connects the analog output pin from the sensor to the ADC pin on the ESP32 (GPIO 34).
Resistor (R)	Between Analog Output and GND	A 10kΩ resistor is placed between the analog output pin and ground for signal conditioning.
Software Explanation
1. Wi-Fi Connection:
In the connectWiFi() function, the ESP32 attempts to connect to the specified Wi-Fi network. The status of the connection is printed to the serial monitor.

2. Soil Moisture Calculation:
In the loop() function, the analogRead() function reads the raw value from the sensor connected to GPIO 34. This value is then converted into a percentage using the formula mentioned above.

3. Web Server:
The WebServer object listens for HTTP requests and responds with the appropriate data.

The /data.txt route sends the current moisture level as a text string.

The root route (/) sends an HTML page containing a gauge-style visualization of the moisture level and a status message.

Future Enhancements
More Sensors: Adding more sensors to monitor multiple plants.

Email Alerts: Send notifications via email when the moisture level falls below a certain threshold.

Mobile App Integration: Create a mobile app to control and monitor the system more effectively.

Data Logging: Store historical moisture data in a cloud database for long-term analysis and trends.

Conclusion
This project demonstrates the use of an ESP32 to build a Wi-Fi-enabled soil moisture monitoring system that can be accessed and controlled remotely. By understanding the electronics behind the soil moisture sensor and its integration with the ESP32, you can build a variety of IoT-based agricultural applications for smart farming.
