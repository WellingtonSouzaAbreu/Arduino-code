
int speaker = 7;
int button = 30;

void setup() {
  Serial.begin(115200);
  pinMode(speaker, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(button) == LOW) {
    tone(speaker, 264, 100);
  } else {
    //Serial.println("Botão não pressionado");
  }

  

  delay(10700);
}
