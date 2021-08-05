#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>

const char* ssid = "Dumb";
const char* password = "pipocadoce";

const int rele = 27;
int capacitiveSensor = 26;

int maxSensorValue = 0;
int minSensorValue = 5000;
int minValue = 0;
int maxValue = 4095;
int averageScale = 4095;
float moisture = 0;

WebServer server(80);

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {

  pinMode(rele, OUTPUT);
  pinMode(capacitiveSensor, INPUT);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/esp32/rele", HTTP_POST, []() {
    String state = server.arg("plain");

    if (state == "ON") {
      digitalWrite(rele, HIGH);
    } else {
      if (state == "OFF") {
        digitalWrite(rele, LOW);
      }
    }

    server.send(200, "text/plain", state);
  });

  server.on("/esp32/moisture", HTTP_GET, []() {

    Serial.print("/esp/moisture");
    //String moistureJson = "{\"moisture\": \" "  + String(moisture, 0) + " \"}";
    server.send(200, "text/plain", "molhado");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

}

void readCapacitiveSensor() {
  int sensorValue = analogRead(26);

  Serial.print("Valor: ");
  Serial.println(sensorValue);

  float moisturePercentage = 100 -  ((sensorValue - minValue) * 100 / averageScale);

  Serial.print("Umidade: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  moisture = moisturePercentage;

  delay(1000);
}

void loop(void) {
  server.handleClient();
  //  readCapacitiveSensor();


}
