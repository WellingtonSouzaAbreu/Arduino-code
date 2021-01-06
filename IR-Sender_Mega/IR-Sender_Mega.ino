
#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(115200);
}

void loop() {


  uint8_t code = "A2FCA864";
  irsend.sendRC5(code,32);

  Serial.println("Mensagem enviada");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
}
