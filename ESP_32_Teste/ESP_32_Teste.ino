inlcude <WiFi.h>

String ssid = "";
int intensidadeSinal = -9999;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);

  WiFi.disconnect();
}

void loop() {
  Serial.print("Hello World!");

  int numberOfNetworks = WiFi.scanNetworks(); //Numeros de redes;
  Serial.println("Escaneamento realizado!");

  if(n == 0){
    Serial.println("Nenhuma rede encontrada!");
  }else{
    ssid = "";
    intensidadeSinal = -9999;
    Serial.print("Redes online: ");
    Serial.println(n);

    for(int i = 0; i < n; ++i){
      Serial.print(WiFi.SSID(i)); // Nome da rede
      Serial.print(": ");
      Serial.print(WiFi.RSSI(i)); // Intensidade do sinal

      if(abs(WiFi.RSSI(i)) < abs(intensidadeSinal)){
        intensidadeSinal = WiFi.RSSI(i));
        ssid = WiFi.SSID(i);
        Serial.print("Rede com melhor sinal encontrada: ");
        Serial.print(ssid);
        Serial.print("Sinal: ");
        Serial.println(intensidadeSinal);
      }
    }
  } 

  Serial.println("-----------------------------------------------");
  delay(5000);
  

  /* Serial.write(27);       // Comando ESC
  Serial.print("[2J");    // comando para limpar a tela
  Serial.write(27);      // Comando ESC
  Serial.print("[H");     // cursor Home (início da tela) */

}
