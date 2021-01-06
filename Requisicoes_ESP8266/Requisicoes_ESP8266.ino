#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Dumb";
const char* password = "pipocadoce";

void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  HTTPClient http;

  http.begin("http://192.168.2.251:80/on");
  int httpCodeGet = http.GET();

  if (httpCodeGet) {
    Serial.printf("[HTTP] GET... code: ", httpCodeGet);

    // file found at server
    if (httpCodeGet == 200) {
      String payload = http.getString();
      Serial.print("Payload: ");
      Serial.println(payload);
    }else{
      Serial.println("Erro ao gettar");
    }
  } else {
    Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
  }

  
  Serial.println("-----------------");
  http.end();
  delay(1000);

  http.begin("http://192.168.2.251:80/off");
  httpCodeGet = http.GET();

  if (httpCodeGet) {
    Serial.printf("[HTTP] GET... code: ", httpCodeGet);

    // file found at server
    if (httpCodeGet == 200) {
      String payload = http.getString();
      Serial.print("Payload: ");
      Serial.println(payload);
    }else{
      Serial.println("Erro ao gettar");
    }
  } else {
    Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
  }

  
  Serial.println("-----------------");
  http.end();
  delay(1000);

}
