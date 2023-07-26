#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>

// Libraries for additional sensors
#include <GY30.h> // GY-30 Light Sensor (BH1750)
#include <AS3935.h> // AS3935 Ray Sensor (Lightning Detector)
#include <AS5600.h> // AS5600 Hall Sensor (Wind Direction)
#include <HallSensor.h> // Hall Sensor (Wind Speed and Rain)

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define DHTPIN 2        // DHT22 data pin
#define DHTTYPE DHT22   // DHT22 sensor type
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP280 bmp;
// Initialize the object for the SY300 sensor if available

// Initialize GY-30 Light Sensor
GY30 gy30;

// Initialize AS3935 Ray Sensor
AS3935 as3935(0x00); // I2C address 0x00, change it if needed

// Initialize AS5060 Hall Sensor for Wind Direction
AS5600 as5060;

// Initialize 3144 Hall Sensor for Wind Speed and Rain Detection
HallSensor hallSensor(13); // GPIO 13 for Wind Speed and Rain Sensor

AsyncWebServer server(80);

void handleRoot() {
  String json = "{";
  
  // Read and include real-time sensor data (ray, wind direction, wind speed, rainfall)
  json += "\"lightning\": " + String(as3935.getStrikeDistanceKm()) + ",";
  json += "\"wind_direction\": " + String(as5060.getHeadingDegrees()) + ",";
  json += "\"wind_speed\": " + String(hallSensor.getPulseFrequency()) + ",";
  json += "\"rainfall\": " + (hallSensor.getPulseFrequency() > 0 ? "true" : "false") + ",";
  
  // Read and include sensor data with 1-minute update interval
  static unsigned long previousMillis = 0;
  const long interval = 60000; // 1 minute interval
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    json += "\"temperature\": " + String(dht.readTemperature()) + ",";
    json += "\"humidity\": " + String(dht.readHumidity()) + ",";
    json += "\"pressure\": " + String(bmp.readPressure()) + ",";
    json += "\"light\": " + String(gy30.readLightLevel()) + ",";
    // Add the sensor data for other sensors with 1-minute update interval
  }

  json += "}";
  server.send(200, "application/json", json);
}

void handleOn() {
  // Implement your control action here (e.g., turn on a device)
  server.send(200, "text/plain", "Control action 'On' executed.");
}

void handleOff() {
  // Implement your control action here (e.g., turn off a device)
  server.send(200, "text/plain", "Control action 'Off' executed.");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected!");
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
  bmp.begin(0x76);
  // Initialize the SY300 sensor if available

  // Initialize GY-30 Light Sensor
  gy30.begin(BH1750_CONTINUOUS_HIGH_RES_MODE);

  // Initialize AS3935 Ray Sensor
  as3935.powerUp();

  // Initialize AS5060 Hall Sensor for Wind Direction
  as5060.begin();

  // Initialize 3144 Hall Sensor for Wind Speed and Rain Detection
  hallSensor.begin();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  // Add any other necessary code here
}
