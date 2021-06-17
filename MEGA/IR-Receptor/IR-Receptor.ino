/*
   IRremote: IRreceiveDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Initially coded 2009 Ken Shirriff http://www.righto.com/
*/

#include <IRremote.h>

int IR_RECEIVE_PIN = 11;
IRrecv IrReceiver(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  Serial.println("Enabling IRin");
  IrReceiver.enableIRIn();  // Start the receiver
  IrReceiver.blink13(true); // Enable feedback LED

  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
  
  
}

void loop() {
  if (IrReceiver.decode(&results)) {

    Serial.println(results.decode_type);


    if (results.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    }
    Serial.print(results.value, HEX);
    Serial.print(" ");
    Serial.print(" size: ");
    Serial.println(results.bits);
    
    IrReceiver.resume(); // Receive the next value

  }
  delay(100);
}
