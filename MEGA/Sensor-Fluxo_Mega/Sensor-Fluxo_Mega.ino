//definicao do pino do sensor e de interrupcao
const int INTERRUPCAO_SENSOR = 0; //interrupt = 0 equivale ao pino digital 2
const int PINO_SENSOR = 2;

//definicao da variavel de contagem de voltas
unsigned long contador = 0;

//definicao do fator de calibracao para conversao do valor lido
const float FATOR_CALIBRACAO = 38.5;

//definicao das variaveis de fluxo e volume
float fluxo = 0;
float volume = 0;
float volume_total = 0;
float volume_ml = 0;

int ledGreen = 5;
int ledOrange = 6;
int ledRed = 7;

//definicao da variavel de intervalo de tempo
unsigned long tempo_antes = 0;

void setup() {

  //inicializacao do monitor serial
  Serial.begin(115200);

  //mensagem de inicializacao
  Serial.println("Medidor de Fluxo e Volume de Liquidos\n");

  //configuracao do pino do sensor como entrada em nivel logico alto
  pinMode(PINO_SENSOR, INPUT_PULLUP);

}

void loop() {
  //executa a contagem de pulsos uma vez por segundo

  if ((millis() - tempo_antes) > 1000) {

    //desabilita a interrupcao para realizar a conversao do valor de pulsos
    detachInterrupt(INTERRUPCAO_SENSOR);

    //conversao do valor de pulsos para L/min
    fluxo = ((1000.0 / (millis() - tempo_antes)) * contador) / FATOR_CALIBRACAO;



    //exibicao do valor de fluxo
    Serial.print("Fluxo de: ");
    Serial.print(fluxo);
    Serial.println(" L/min");

    //calculo do volume em L passado pelo sensor
    volume = fluxo / 60;

    //armazenamento do volume
    volume_total += volume;

    volume_ml = volume_total * 1000;

    //exibicao do valor de volume
    Serial.print("Volume(L): ");
    Serial.print(volume_total);
    Serial.println(" L");
    Serial.print("Volume(ml): ");
    Serial.print(volume_ml);
    Serial.println(" ml");
    Serial.println("-----------------------");

    if (volume_ml < 150) {
      analogWrite(ledGreen, 255);
      analogWrite(ledOrange, 0);
      analogWrite(ledRed, 0);
    }

    if (volume_ml > 150 && volume_ml < 350) {
      analogWrite(ledGreen, 0);
      analogWrite(ledOrange, 255);
      analogWrite(ledRed, 0);
    }

    if (volume_ml > 350) {
      analogWrite(ledGreen, 0);
      analogWrite(ledOrange, 0);
      analogWrite(ledRed, 255);
    }

    //reinicializacao do contador de pulsos
    contador = 0;

    //atualizacao da variavel tempo_antes
    tempo_antes = millis();

    //contagem de pulsos do sensor
    attachInterrupt(INTERRUPCAO_SENSOR, contador_pulso, FALLING);
  }
}

//funcao chamada pela interrupcao para contagem de pulsos
void contador_pulso() {
  contador++;
}
