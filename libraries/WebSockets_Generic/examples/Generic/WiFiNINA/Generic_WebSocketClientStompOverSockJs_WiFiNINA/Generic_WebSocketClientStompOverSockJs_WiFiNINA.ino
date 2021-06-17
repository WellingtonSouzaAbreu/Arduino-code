/****************************************************************************************************************************
  WebSocketClientStompOverSockJs_WiFiNINA.ino
  For Generic boards using WiFiNINA Shield/Module
  
  Based on and modified from WebSockets libarary https://github.com/Links2004/arduinoWebSockets
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.
  
  Built by Khoi Hoang https://github.com/khoih-prog/WebSockets_Generic
  Licensed under MIT license
  
  Example for connecting and maintining a connection with a SockJS+STOMP websocket connection.
  In this example, we connect to a Spring application (see https://docs.spring.io/spring/docs/current/spring-framework-reference/html/websocket.html).
  
  Created on: 18.07.2017
  Author: Martin Becker <mgbckr>, Contact: becker@informatik.uni-wuerzburg.de
 *****************************************************************************************************************************/

#define _WEBSOCKETS_LOGLEVEL_     3
#define WEBSOCKETS_NETWORK_TYPE   NETWORK_WIFININA

#include <WebSocketsClient_Generic.h>

// SETTINGS

const char* wlan_ssid             = "yourssid";
const char* wlan_password         = "somepassword";

const char* ws_host               = "the.host.net";
const int   ws_port               = 80;

// base URL for SockJS (websocket) connection
// The complete URL will look something like this(cf. http://sockjs.github.io/sockjs-protocol/sockjs-protocol-0.3.3.html#section-36):
// ws://<ws_host>:<ws_port>/<ws_baseurl>/<3digits>/<randomstring>/websocket
// For the default config of Spring's SockJS/STOMP support, the default base URL is "/socketentry/".
const char* ws_baseurl            = "/socketentry/"; // don't forget leading and trailing "/" !!!

// VARIABLES

WebSocketsClient webSocket;

int status = WL_IDLE_STATUS;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h

char ssid[] = "****";        // your network SSID (name)
char pass[] = "********";    // your network password (use for WPA, or use as key for WEP), length must be 8+

// FUNCTIONS

bool alreadyConnected = false;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length)
{
  switch (type)
  {
    case WStype_DISCONNECTED:
      if (alreadyConnected)
      {
        Serial.println("[WSc] Disconnected!");
        alreadyConnected = false;
      }
      
      break;
    case WStype_CONNECTED:
      {
        alreadyConnected = true;
        
        Serial.print("[WSc] Connected to url: ");
        Serial.println((char *) payload);
      }
      break;
    case WStype_TEXT:
      {
        // #####################
        // handle SockJs+STOMP protocol
        // #####################

        String text = (char*) payload;

        Serial.print("[WSc] get text: ");
        Serial.println((char *) payload);

        if (payload[0] == 'h')
        {
          Serial.println("Heartbeat!");
        }
        else if (payload[0] == 'o')
        {
          // on open connection
          String msg = "[\"CONNECT\\naccept-version:1.1,1.0\\nheart-beat:10000,10000\\n\\n\\u0000\"]";

          webSocket.sendTXT(msg);
        }
        else if (text.startsWith("a[\"CONNECTED"))
        {
          // subscribe to some channels
          String msg = "[\"SUBSCRIBE\\nid:sub-0\\ndestination:/user/queue/messages\\n\\n\\u0000\"]";

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
      Serial.print("[WSc] get binary length: ");
      Serial.println(length);
      //hexdump(payload, length);

      // send data to server
      webSocket.sendBIN(payload, length);
      break;
  }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void setup()
{
  // Serial.begin(921600);
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStart WebSocketClientStompOverSockJs_WiFiNINA on " + String(BOARD_NAME));
  Serial.println("Version " + String(WEBSOCKETS_GENERIC_VERSION));

  Serial.println("Used/default SPI pinout:");
  Serial.print("MOSI:");
  Serial.println(MOSI);
  Serial.print("MISO:");
  Serial.println(MISO);
  Serial.print("SCK:");
  Serial.println(SCK);
  Serial.print("SS:");
  Serial.println(SS);

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.println("[SETUP] BOOT WAIT " + String(t));
    Serial.flush();
    delay(1000);
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    //delay(10000);
  }

  printWifiStatus();

  // #####################
  // create socket url according to SockJS protocol (cf. http://sockjs.github.io/sockjs-protocol/sockjs-protocol-0.3.3.html#section-36)
  // #####################
  String socketUrl = ws_baseurl;
  socketUrl += random(0, 999);
  socketUrl += "/";
  socketUrl += random(0, 999999); // should be a random string, but this works (see )
  socketUrl += "/websocket";

  // connect to websocket
  webSocket.begin(ws_host, ws_port, socketUrl);
  webSocket.setExtraHeaders(); // remove "Origin: file://" header because it breaks the connection with Spring's default websocket config
  //    webSocket.setExtraHeaders("foo: I am so funny\r\nbar: not"); // some headers, in case you feel funny
  webSocket.onEvent(webSocketEvent);
}

void loop()
{
  webSocket.loop();
}
