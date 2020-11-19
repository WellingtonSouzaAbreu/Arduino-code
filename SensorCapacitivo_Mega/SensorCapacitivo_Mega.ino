int sensor = A7;
int maxSensorValue = 0;
int minSensorValue = 1000;
int minValue = 720;
int maxValue = 1023;
int averageScale = 315;

void setup() {
  pinMode(sensor, INPUT);
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(A7);

  Serial.print("Valor: ");
  Serial.println(sensorValue);

  if (sensorValue > maxSensorValue) {
    maxSensorValue = sensorValue;
  }

  if (sensorValue < minSensorValue) {
    minSensorValue = sensorValue;
  }

  //Serial.print("MaxValue: ");
  //Serial.println(maxSensorValue);
  
  //Serial.print("MinValuexValue: ");
  //Serial.println(minSensorValue);

  float moisturePercentage = 100 -  ((sensorValue - minValue) * 100 / averageScale);

  Serial.print("Umidade: ");
  Serial.print(moisturePercentage);
  Serial.println("%");
  
  delay(500);

}
