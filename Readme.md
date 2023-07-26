## ESP8266/ESP32 Weather Monitoring and Control System


## Description

The ESP8266/ESP32 Weather Monitoring and Control System is a versatile IoT project that enables users to monitor real-time environmental data and control connected devices remotely. The system utilizes ESP8266 or ESP32 microcontrollers as the central processing units, providing Wi-Fi connectivity and hosting a web server to interact with users.

## Features

- Real-time Monitoring: The system can continuously monitor various environmental parameters in real-time, such as temperature, humidity, pressure, light intensity, lightning distance, wind direction, wind speed, and rain detection.

- Web Interface: A user-friendly web interface allows users to access sensor data and control connected devices from any web-enabled device, such as smartphones, tablets, or computers.

- Rain Detection: The system is equipped with a rain detection sensor (3144 Hall Sensor) to detect rain and display its status on the web interface.

- Control Actions: Users can remotely control connected devices using the web interface, enabling them to turn on or off devices based on sensor data or user preferences.

- Separation of Data: The web interface clearly separates real-time sensor data from data with a 1-minute update interval, providing a comprehensive and organized view of environmental conditions.

## Components

- ESP8266 or ESP32 microcontroller
- DHT22 Temperature and Humidity Sensor
- BMP280 Pressure Sensor
- GY-30 Light Sensor (BH1750)
- AS3935 Lightning Detector
- AS5600 Hall Sensor for Wind Direction
- 3144 Hall Sensor for Wind Speed and Rain Detection

## Setup and Usage

1. Install the Arduino IDE and ESP8266/ESP32 board support as per the instructions provided in the project documentation.

2. Upload the provided Arduino sketch (`main.ino`) to the ESP8266/ESP32 board.

3. Connect the sensors to the appropriate GPIO pins on the ESP8266/ESP32.

4. Power up the ESP8266/ESP32 board and connect it to your Wi-Fi network.

5. Access the web interface by entering the IP address of the ESP8266/ESP32 in a web browser.

6. The web interface will display real-time sensor data and control options for connected devices.
