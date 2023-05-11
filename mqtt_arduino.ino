#include "DHT.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>

// MQTT CONFIGURATION
const char* mqtt_server = "44.198.48.90";
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_password = "";
const char* subscription_topic = "pump";
const char* publication_topic = "measurement";

// WIFI CONFIGURATION
const char* ssid = "Tec-IoT";
const char* password = "spotless.magnetic.bridge";

// Variables Globales
WifiClient espClient;
PubSubClient client(espClient);
char msg[80];

DHT dht(0, DHT11);
WifiServer server(80);

int D5 = 14; //Light sensor
int D6 = 12; //Soil humidity
int D7 = 13; // Water pump


void setup() {
    Serial.begin(115200);
}

void loop() {
}
