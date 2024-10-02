#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup()
{
  lcd.begin(16, 2);
  lcd.print(" Circuit Digest!");
  delay(2000);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++)
  {
    lcd.scrollDisplayRight();
    delay(150);
  }
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Count!");
}
void loop()
{
  for (int i = 0; i < 10; i++)
  {
    lcd.setCursor(8, 1);
    lcd.print(i);
    delay(1000);
  }
}