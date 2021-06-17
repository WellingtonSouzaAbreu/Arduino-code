 #include <Adafruit_Sensor.h>                       // Biblioteca DHT Sensor Adafruit 
#include <DHT.h> 
 // Bibliotecas aparentemente dispensáveis
#include <DHT_U.h>
 
int DHTTYPE = DHT11 ;                          // Sensor DHT11;
int DHTPIN = 3 ;                                  // Pino do Arduino conectado no Sensor(Data) 
int delayMS;                                  // variável para atraso no tempo

DHT_Unified dht(DHTPIN, DHTTYPE);                  // configurando o Sensor DHT - pino e tipo
void setup()
{
  Serial.begin(9600);                             // monitor serial 9600 bps
  dht.begin();                                    // inicializa a função
  
  sensor_t sensor; // Instancia o objeto 'sensor'
  
  dht.temperature().getSensor(&sensor);           // imprime os detalhes do Sensor de Temperatura
  Serial.println("------------------------------------");
  Serial.println("Temperatura");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
 
  dht.humidity().getSensor(&sensor);            // imprime os detalhes do Sensor de Umidade
  Serial.println("------------------------------------");
  Serial.println("Umidade");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  
  Serial.print("Delay: ");
  Serial.print(sensor.min_delay / 1000 );
  Serial.println("ms");
  Serial.println("------------------------------------");
  delayMS = sensor.min_delay / 1000;            // define o atraso entre as leituras
}
 
void loop()
{
  delay(delayMS);                               // atraso entre as medições

  getAndPrintTemperature();
  getAndPrintRelativeHumidity();
}

void getAndPrintTemperature(){
  sensors_event_t event; // inicializa o evento da Temperatura           
  
  dht.temperature().getEvent(&event);           // faz a leitura da Temperatura
  if (isnan(event.temperature)){                 // se algum erro na leitura
    Serial.println("Erro na leitura da Temperatura!");
  }
  else{                                          // senão
    Serial.print("Temperatura: ");              // imprime a Temperatura
    Serial.print(event.temperature);
    Serial.println(" ºC");
  }
};

void getAndPrintRelativeHumidity(){
  sensors_event_t event; 
  
  dht.humidity().getEvent(&event);              // faz a leitura de umidade
  if (isnan(event.relative_humidity)){           // se algum erro na leitura 
    Serial.println("Erro na leitura da Umidade!");
  }
  else{                                          // senão
    Serial.print("Umidade: ");                  // imprime a Umidade
    Serial.print(event.relative_humidity);
    Serial.println("%");
  }
};
