void setup() {
  pinMode(12, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if(Serial.available() > 0){
    String command = Serial.readString();

    if(command.indexOf("1") > -1){
      digitalWrite(12, HIGH);
    }else{
       digitalWrite(12, LOW);
    }
  }

}
