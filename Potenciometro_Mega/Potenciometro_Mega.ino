const int pinPot = A7; 
const int pinLed1 = 22; 
const int pinLed2 = 24;
const int pinLed3 = 26;
const int pinLed4 = 28;
const int pinLed5 = 30;

int ledBrightness = 0; 
int dull = 0;

void setup(){
   Serial.begin(115200);  
   pinMode(pinPot, INPUT);
   pinMode(pinLed1, OUTPUT);
   pinMode(pinLed2, OUTPUT);
   pinMode(pinLed3, OUTPUT);
   pinMode(pinLed4, OUTPUT);
   pinMode(pinLed5, OUTPUT);
}

void loop(){
  Serial.println(analogRead(pinPot));
  ledBrightness = map(analogRead(pinPot), 0, 1023, 0, 255); 

  int rawPotentiometerPower = analogRead(pinPot);
  
  if(rawPotentiometerPower > 517){
    analogWrite(pinLed1, ledBrightness);
  }else{
    analogWrite(pinLed1, dull);
  }

  if(rawPotentiometerPower > 630){
    analogWrite(pinLed2, ledBrightness);
  }else{
    analogWrite(pinLed2, dull);
  }

  if(rawPotentiometerPower > 755){
    analogWrite(pinLed3, ledBrightness);
  }else{
    analogWrite(pinLed3, dull);
  }

  if(rawPotentiometerPower > 890){
    analogWrite(pinLed4, ledBrightness);
  }else{
    analogWrite(pinLed4, dull);
  }

  if(rawPotentiometerPower > 1010){
    analogWrite(pinLed5, ledBrightness);
  }else{
    analogWrite(pinLed5, dull);
  }
  
  
  
}
