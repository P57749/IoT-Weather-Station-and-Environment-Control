#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
// Include the library for the SY300 sensor if available

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

#define DHTPIN 2        // DHT22 data pin
#define DHTTYPE DHT22   // DHT22 sensor type
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP280 bmp;
// Initialize the object for the SY300 sensor if available

AsyncWebServer server(80);

void handleRoot() {
  String json = "{";
  json += "\"temperature\": " + String(dht.readTemperature()) + ",";
  json += "\"humidity\": " + String(dht.readHumidity()) + ",";
  json += "\"pressure\": " + String(bmp.readPressure());
  // Add the sensor data from the SY300 sensor if available
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
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected!");
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
  bmp.begin(0x76);
  // Initialize the SY300 sensor if available

  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
