#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13); 

void setup() {
  lcd.begin(16, 2);
  
  lcd.print("Hello World!");

  

}

void loop() {
  lcd.print("Hello World!");
  delay(30000);
}
