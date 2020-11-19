#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Dumb";
const char* password = "pipocadoce";

ESP8266WebServer server(80);

void handleRoot() {

  String textoHTML;
  textoHTML = "Ola!! Aqui é o ESP8266 falando! ";

  server.send(200, "text/html", textoHTML);
}

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
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/on", []() {
    Serial.println(13);
    server.send(200, "text/plain", "Server online");
  });

  server.on("/light-switch", HTTP_GET, [](){
    String htmlPage = "";
    htmlPage += "<!DOCTYPE html>";
    htmlPage += "<head>";
    htmlPage += "    <meta charset=\"UTF-8\">";
    htmlPage += "    <title>Axios com arduino</title>";
    htmlPage += "    <script src=\"https://cdnjs.cloudflare.com/ajax/libs/axios/0.21.0/axios.js\"></script>";
    
    htmlPage += "    <script>";
    htmlPage +=          "function toggleSwitch(stateOfSwitch){";
    htmlPage += "        let state = new FormData();";
    htmlPage += "        state.append(\"state\", stateOfSwitch);";

    htmlPage += "        axios.post(\"http://192.168.2.14/light-switch\", state)";
    htmlPage += "             .then(res => setStateOfSwitchLabel(res.data))";
    htmlPage += "            .catch(err => console.log(err));";
    htmlPage += "    }; ";

    htmlPage += " function setStateOfSwitchLabel(state){";
        htmlPage += " let stateLabel = document.querySelector('#state');";
        htmlPage += " stateLabel.innerHTML = state == 'on' ? 'Ligado': 'Desligado';";
        htmlPage += " state == 'on' ? stateLabel.style.color = 'green': stateLabel.style.color = 'red';"; 
    htmlPage += " };";

    
    htmlPage += "    </script>";
    
    htmlPage += "</head>";
    htmlPage += "<body style=\"display: flex; justify-content: center; align-items: center;flex-direction: column;\">";
    htmlPage += "    <div>";
    htmlPage += "        <h2>Light Switch - <strong id='state' style=\"color: red;\">Desligado</h2>";
    htmlPage += "    </div>";
    htmlPage += "    <div>";
    htmlPage += "        <button onclick=\"toggleSwitch('on')\" style=\"background-color: green;color: white; padding: 1px 7px;\">Ligar</button>";
    htmlPage += "        <button onclick=\"toggleSwitch('off')\" style=\"background-color: red;color: white; padding: 1px 7px;\">Desligar</button>";
    htmlPage += "    </div>";
    
    htmlPage += "</body>";
    htmlPage += "</html>";
    
    server.send(200, "text/html", htmlPage);
  });

  server.on("/light-switch", HTTP_POST, []() {
    String state = server.arg("state");
    delay(100);
    digitalWrite(12, HIGH); // SOmente para teste do relé 3.3V
    analogWrite(12, 255); // SOmente para teste do relé 3.3V
    Serial.println(state);
    
    server.send(200, "text/plain", state);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
