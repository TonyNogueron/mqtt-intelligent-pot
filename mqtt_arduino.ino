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

// FUNCTION Headers
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setup_wifi();
void setup_sensors();

void setup() {
    Serial.begin(115200);
}

void loop() {
}

void setup_wifi() {
    delay(10);
    //Connection to the Wifi
    Serial.println();
    Serial.print("Connecting to ssid: ");
    Serial.println(ssid);

    WiFi.begin(ssid,password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("Successful connection!");
    Serial.println("Ip Address: ");
    Serial.println(WiFi.localIP());
}



