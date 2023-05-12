# MQTT IoT - Intelligent pot project
### Antonio Noguerón Bárcenas | A01423759
#### 05/11/2023

## MQTT
This is a project in which we use the MQTT Protocol to transfer data read from sensors to a dashboard that displays the data in real time.
- The broker is hosted on an EC2 instance in AWS with the mosquitto library.

## Arduino
- The board is a Node MCU and has the circuit to support 3 sensors, measuring 4 variables in real-time. 
- The circuit also has a water pump with a relay that is able to be turned on from a mqtt publication to the 'pump' topic.
- The 3 sensors are: Temperature and humidity, Soil moisture, and light.


