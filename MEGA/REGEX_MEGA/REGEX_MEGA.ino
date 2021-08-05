
#include <Regexp.h>

void setup () {
  Serial.begin (115200);

}  // end of setup

void loop () {

  MatchState ms;

  char buf[200] = "{\"waterConsumed\":\"0.00\", \"activeSector\": 2, \"waterConsumedMega\": 1}{\"airMoisture\": 21, \"temperatureAir\": 26, \"airData\": 1}  {\"waterConsumed\":\"0.00\", \"activeSector\": 2, \"waterConsumedMega\": 1}";

  ms.Target(buf);  // set its address
  Serial.println(buf);

  char toMatch =  ms.Match("{\"airMoisture(.+)airData\": 1}");

  if (toMatch > 0) {
    Serial.println("Found match at: " + String(ms.MatchStart));
    Serial.println("Match length: " + String(ms.MatchLength));
    Serial.println("teste: " + String(teste));
  } else {
  } else {
    Serial.println ("No match.");
  }

  String result = String(buf).substring(ms.MatchStart, ms.MatchStart + ms.MatchLength);
  Serial.println("Regex completa: " + result);

  Serial.println();
  Serial.println("-------------------------------------------");
  Serial.println();

  delay(4000);
}
