#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Dumb";
const char* password = "pipocadoce";

void setup() {

  Serial.begin(115200);
  pinMode(12, OUTPUT);


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

  String payload = "";

  HTTPClient http;

  http.begin("http://192.168.2.183:3000/status-led");
  int httpCodeGet = http.GET();

  if (httpCodeGet) {
    Serial.printf("[HTTP] GET... code: ", httpCodeGet);

    // file found at server
    if (httpCodeGet == 200) {
      payload = http.getString();
      Serial.print("Payload: ");
      Serial.println(payload);

      if(payload == "ON"){
        digitalWrite(12, HIGH);
        Serial.println("Ligou!");
      }

      if(payload == "OFF"){
        digitalWrite(12, LOW);
        Serial.println("Desigou!");
      }
      
    }else{
      Serial.println("Erro ao gettar");
    }
  } else {
    Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
  }
  
  Serial.println("-----------------");
  http.end();
 
  delay(1000);

  http.begin("http://192.168.2.246:80/led-esp32");
  int httpCodePost = http.POST("{\"status\":\"" + payload + "\"}");
  http.addHeader("Connection", "close");

  if (httpCodePost) {
    Serial.printf("[HTTP] POST... code: ", httpCodePost);

    // file found at server
    if (httpCodePost == 200) {
      payload = http.getString();
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
