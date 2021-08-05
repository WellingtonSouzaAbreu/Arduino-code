int sensor = A0;
int maxSensorValue = 0;
int minSensorValue = 1000;

int minValue = 470; // 720
int maxValue = 1024; // 910
int averageScale = 247;

void setup() {
  pinMode(sensor, INPUT);
  Serial.begin(115200);
}

double correction(double x) {
  return   2.202196968876e+02
           +   3.561383996027e-01 * x
           +   1.276218788985e-04 * pow(x, 2)
           +  -3.470360275448e-07 * pow(x, 3)
           +   2.082790802069e-10 * pow(x, 4)
           +  -5.306931174991e-14 * pow(x, 5)
           +   4.787659214703e-18 * pow(x, 6);
}

void loop() {
  int sensorValue = analogRead(sensor);

  sensorValue = sensorValue ; //+ correction(sensorValue)

  if (sensorValue > maxSensorValue) {
    maxSensorValue = sensorValue;
  }

  if (sensorValue < minSensorValue) {
    minSensorValue = sensorValue;
  }

  Serial.print("MaxValue: ");
  Serial.println(maxSensorValue);

  Serial.print("MinValuexValue: ");
  Serial.println(minSensorValue);

  Serial.print("Valor: ");
  Serial.println(sensorValue);

  float moisturePercentage = map(sensorValue, minValue, maxValue, 100, 0);

  Serial.print("Umidade: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  delay(1000);

}
