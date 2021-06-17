#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>

#include <WiFi.h>

String ssid = "";
int intensidadeSinal = -9999;

void setup() {
  Serial.begin(115200);

  pinMode(39, OUTPUT);

  WiFi.mode(WIFI_STA);

  WiFi.disconnect();
}

void loop() {
  Serial.print("Hello World!");

  Serial.print("Digital: ");
  digitalWrite(39, HIGH);



  delay(4000);

  digitalWrite(39, LOW);

  int numberOfNetworks = WiFi.scanNetworks(); //Numeros de redes;
  Serial.println("Escaneamento realizado!");

  if (numberOfNetworks == 0) {
    Serial.println("Nenhuma rede encontrada!");
  } else {
    ssid = "";
    intensidadeSinal = -9999;
    Serial.print("Redes online: ");
    Serial.println(numberOfNetworks);

    for (int i = 0; i < numberOfNetworks; ++i) {
      Serial.print(WiFi.SSID(i)); // Nome da rede
      Serial.print(": ");
      Serial.print(WiFi.RSSI(i)); // Intensidade do sinal

      if (abs(WiFi.RSSI(i)) < abs(intensidadeSinal)) {
        intensidadeSinal = WiFi.RSSI(i);
        ssid = WiFi.SSID(i);
      }
    }
  }
  Serial.print("Rede com melhor sinal encontrada: ");
  Serial.print(ssid);
  Serial.print("Sinal: ");
  Serial.println(intensidadeSinal);
  Serial.println("-----------------------------------------------");
  delay(5000);

}
