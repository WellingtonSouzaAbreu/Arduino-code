/*
	Esp8266 Websockets Client

	This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server
        3. Sends the websockets server a message ("Hello Server")
        4. Prints all incoming messages while the connection is open

	Hardware:
        For this sketch you only need an ESP8266 board.

	Created 15/02/2019
	By Gil Maimon
	https://github.com/gilmaimon/ArduinoWebsockets

*/

#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

const char* ssid = "Dumb"; //Enter SSID
const char* password = "pipocadoce"; //Enter Password
const char* websockets_server_host = "192.168.2.183"; //Enter server adress
const uint16_t websockets_server_port = 777; // Enter server port

using namespace websockets;

WebsocketsClient client;
void setup() {

  pinMode(12, OUTPUT);
  
  Serial.begin(115200);
  // Connect to wifi
  WiFi.begin(ssid, password);

  // Wait some time to connect to wifi
  for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
    Serial.print(".");
    delay(1000);
  }

  // Check if connected to wifi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("No Wifi!");
    return;
  }

  Serial.println("Connected to Wifi, Connecting to server.");

  // try to connect to Websockets server
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/");

  if (connected) {
    Serial.println("Connected!");
    client.send("Hello Server");
  } else {
    Serial.println("Not Connected!");
  }

  // run callback when messages are received
  client.onMessage([&](WebsocketsMessage message) {
    

    if (message.data() == "on") {
      Serial.println(message.data());
      digitalWrite(12, HIGH);
    }
  });
}

void loop() {
  // let the websockets client check for incoming messages
  if (client.available()) {
    client.poll();

 
  }
  
  delay(500);
}
