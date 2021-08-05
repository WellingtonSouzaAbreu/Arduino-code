int pinResistor = A0;
int pinLed = 10;
int minValueReaded = 1000;
int maxValueReaded = 0;

int maxValue = 1385;
int minValue = 361; // Com luz: 361
int averageScale = maxValue - minValue;

void setup() {
  pinMode(pinResistor, INPUT);
  pinMode(pinLed, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int resistorValue = analogRead(pinResistor);

  Serial.print("Value: ");
  Serial.println(resistorValue);

  if (resistorValue < 160) {
    digitalWrite(pinLed, HIGH);
  } else {
    digitalWrite(pinLed, LOW);
  }

  if (resistorValue < minValueReaded) {
    minValueReaded = resistorValue;
  }

  if (resistorValue > minValueReaded) {
    minValueReaded = resistorValue;
  }

  float brightnessValue = (float) resistorValue - 361;
  float brightnessPercentage = 100 - (brightnessValue / averageScale * 100);


  //  Serial.print("Luminosidade: ");
  //  Serial.print(brightnessPercentage);
  //  Serial.println(" %");
  //Serial.print("Max value readed: ");
  //Serial.println(minValueReaded);
  //Serial.print("Min value readed: ");
  //Serial.println(minValueReaded);

  //  Serial.println("-----------------------");

}
