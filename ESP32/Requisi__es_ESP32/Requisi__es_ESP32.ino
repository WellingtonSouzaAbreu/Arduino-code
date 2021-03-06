#include <WiFi.h>
#include <HTTPClient.h>

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

void httpPost(String data){
  HTTPClient http;
  
  http.begin("http://192.168.2.183:1000/esp32");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Connection", "close");

  int httpCodePost = http.POST(data);

  if (httpCodePost > 0) {
    Serial.printf("[HTTP] POST... code: ", httpCodePost);
  }

  if (httpCodePost > 0) {
    if (httpCodePost == HTTP_CODE_OK) {
      const String payload = http.getString();
      Serial.print("received payload: ");
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCodePost).c_str());
  }

  Serial.println("-----------------");

  http.end();
}

void loop() {

  HTTPClient http;

  http.begin("192.168.2.183", 1000, "/esp32");
  int httpCodeGet = http.GET();

  if (httpCodeGet) {
    Serial.printf("[HTTP] GET... code: ", httpCodeGet);

    // file found at server
    if (httpCodeGet == 200) {
      String payload = http.getString();
      Serial.print("Payload: ");
      Serial.println(payload);
    }
  } else {
    Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
  }

  http.end();
  Serial.println("-----------------");

  delay(1000);

  String data = "{\"hello\":\"Aooooooba!!\"}";
  httpPost(data);
}
