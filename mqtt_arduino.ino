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
    setup_sensors();
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    } else {
        // We create the humidity and temperature variables and read from the sensor
        float h = dht.readHumidity();
        float t = dht.readTemperature();

        //Turns on the light sensor
        digitalWrite(D5, HIGH);
        delay(100);
        //Reads
        float l = analogRead(A0);
        //Turns off
        digitalWrite(D5, LOW);

        
        digitalWrite(d6, HIGH);
        delay(100);
        float tierra = analogRead(A0);
        digitalWrite(d6, LOW);

        String data = "Humedad: " + String(h) + "% ";
        data = data + "Temperatura: " + String(t) + "°C ";
        tierra = map(tierra, 0, 1023, 100, 0);
        l = map(l, 0, 1023, 100, 0);

        data = data + " Humedad en Tierra: " + String(tierra) + "% ";
        data = data + " Luz: " + String(l) + "%";
        Serial.println(data);
        data.toCharArray(msg, 80);

        client.publish(publication_topic, msg);
    }
    client.loop();
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

//MQTT Connection

void reconnect() {
    while(!client.connected()) {
        Serial.print("Attempting to connect to MQTT...");
        // Creamos un cliente ID
        String clientId = "Planty_";
        clientId += String(random(0xffff), HEX);
        // Intentamos conectar
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
            Serial.println("Connected!");
            // Nos suscribimos
            if (client.subscribe(subscription_topic)) {
                Serial.println("Successfully subsribed to " + subscription_topic);
            } else {
                Serial.println("There was an error subscribing to " + subscription_topic);
            }
        } else {
            Serial.print("Failed with error:  ");
            Serial.print(client.state());
            Serial.println(" Trying again in 5 seconds");
            delay(5000);
        }
    }
}

// Callback function that executes when something gets published 
void callback(char* topic, byte* payload, unsigned int length) {
    String incoming = "";
    Serial.print("Message received from: ");
    Serial.print(topic);
    Serial.println("");
    for (int i = 0; i < length; i++) {
        incoming += (char)payload[i];
    }
    incoming.trim();
    Serial.println("Message: " + incoming);
    if (incoming == "prender") {
        // Activate the pump
        digitalWrite(D7, HIGH);
        delay(5000);
        digitalWrite(D7, LOW);
    }
}


// Setting up the sensor ports and pinModes
void setup_sensors() {
    dht.begin();
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(A0, INPUT);
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
}
