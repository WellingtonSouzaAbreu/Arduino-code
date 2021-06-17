
void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);

  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
}

void loop() {
  if (Serial3.available()) {
    
    String state = Serial3.readString();
    Serial.println(state);

    if(state.indexOf("on") == 0){
      analogWrite(23, 255);
      digitalWrite(25, HIGH);
    }else{
      analogWrite(23, 0);
      digitalWrite(25, LOW);
    }

  }
}
