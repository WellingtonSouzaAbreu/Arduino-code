#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

String ssid = "Dumb";
String password = "pipocadoce";

IPAddress serverAddress(192, 168, 2, 183);
char user[] = "root";
char pass[] = "";
char database[] = "USE bancoarduino";

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void connectWifi() {
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

void setup() {
  Serial.begin(115200);
  connectWifi();
}

void loop() {
  Serial.println("");
  Serial.print("Executando sentença...");

  char id[3] = "1";
  char nome[20] = "Wellington";
  int old = 20;

  char sql[100] = "insert into cliente values(%d)";
  char sql2[20] = "";

  sprintf(sql2, sql, id);

  Serial.println("Antes de conectar");
  if (conn.connect(serverAddress, 3307, user, pass)) {

    delay(1000);
    Serial.println("Antes de MySql cursor");
    MySQL_Cursor *cur_memc = new MySQL_Cursor(&conn);
    cur_memc->execute(database);
    delete cur_memc;

    delay(1000);
    Serial.println("Antes de MySql cursor 2");
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    Serial.println(sql2);
    cur_mem->execute(sql2);
    delete cur_mem;
  } else {
    Serial.println("A conexão falhou");
    conn.close();
  }

  delay(2000);




}
