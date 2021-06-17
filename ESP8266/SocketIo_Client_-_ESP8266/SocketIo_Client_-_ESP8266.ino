#include <Arduino.h>
//#include <Hash.h>

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>


const char* wlan_ssid             = "Dumb";
const char* wlan_password         = "pipocadoce";

const char* ws_host               = "http://192.168.2.183";
const int   ws_port               = 1000;

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n",  payload);
      }
      break;
    case WStype_TEXT:
      {

        String text = (char*) payload;

        Serial.printf("[WSc] get text: %s\n", payload);

        if (payload[0] == 'h') {

          Serial.println("Heartbeat!");

        } else if (payload[0] == 'o') {

          // on open connection
          char *msg = "[\"CONNECT\\naccept-version:1.1,1.0\\nheart-beat:10000,10000\\n\\n\\u0000\"]";
          webSocket.sendTXT(msg);

        } else if (text.startsWith("a[\"CONNECTED")) {

          // subscribe to some channels

          char *msg = "[\"SUBSCRIBE\\nid:sub-0\\ndestination:/user/queue/messages\\n\\n\\u0000\"]";
          webSocket.sendTXT(msg);
          delay(1000);

          // and send a message

          msg = "[\"SEND\\ndestination:/app/message\\n\\n{\\\"user\\\":\\\"esp\\\",\\\"message\\\":\\\"Hello!\\\"}\\u0000\"]";
          webSocket.sendTXT(msg);
          delay(1000);
        }

        break;
      }
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
  }

}

void setup() {

  Serial.begin(115200);
  Serial.println();

  Serial.print("Logging into WLAN: "); Serial.print(wlan_ssid); Serial.print(" ...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(wlan_ssid, wlan_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" success.");
  Serial.print("IP: "); Serial.println(WiFi.localIP());

  String socketUrl = "";
  Serial.println(ws_host);
  Serial.println(ws_port);
  Serial.println(socketUrl);
  // connect to websocket
  webSocket.begin(ws_host, ws_port, socketUrl);
  //webSocket.setExtraHeaders(); // remove "Origin: file://" header because it breaks the connection with Spring's default websocket config
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
}
