#include <analogWrite.h>

int touchPin = 32;
int ledPin = 26;
int touchCount = 0;
int averageValue = 25;
bool continuousTouch = false;

void setup() {
  Serial.begin(115200);

  pinMode(touchPin, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {

  int touchAmount = 0;

  //  for (int i = 0; i < 10; i++) {
  //    touchAmount += touchRead(touchPin);
  //  }

  int touchValue = touchRead(touchPin);

  if (touchValue < averageValue && continuousTouch == false) {
    continuousTouch = true;
    touchCount += 1;
    Serial.println("Tocando");
  } else {
    if (touchValue >= averageValue && continuousTouch == true) {
      continuousTouch = false;
      Serial.println("Não tocando");
    }
  }

  delay(100);

  Serial.println("TouchRead: " + String(touchRead(touchPin)));
  Serial.println("TouchCount: " + String(touchCount));



  if (continuousTouch == false) {
    switch (touchCount) {
      case 1: analogWrite(ledPin, 85);
        break;
      case 2: analogWrite(ledPin, 170);
        break;
      case 3: analogWrite(ledPin, 255);
        break;
      case 4: touchCount = 0;
        analogWrite(ledPin, 0);
    }
  }

}
