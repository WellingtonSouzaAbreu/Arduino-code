int pinRele = 25;

void setup() {
  pinMode(pinRele, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  if(Serial.available()){
    String state = Serial.readString();

    if(state.indexOf("on")){
      digitalWrite(pinRele, HIGH);
    }else{
      digitalWrite(pinRele, LOW);
    }
  }
  delay(1000);

}
