
#include <IRremote.h>

IRsend irsend;
#define BTN_PHILIPS_VOLDOWN2 0x810

void setup()
{
  Serial.begin(115200);
}

void loop() {


  uint64_t code = "A2FCA864";
  char a[9] = "A2FCA864";
  irsend.sendRC6(BTN_PHILIPS_VOLDOWN2, 12);

  Serial.println("Mensagem enviada");
  digitalWrite(LED_BUILTIN, HIGH);
}
