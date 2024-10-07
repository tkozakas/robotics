#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <TimerOne.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonStart = 8;
const int buttonStop = 7;
const int buttonReset = 6;

volatile bool running = false;
unsigned long elapsedTime = 0;
unsigned long lastDebounceTimeStart = 0;
unsigned long lastDebounceTimeStop = 0;
unsigned long lastDebounceTimeReset = 0;
const int debounceDelay = 50;

void setup()
{
  lcd.begin(16, 2);
  lcd.print("00:00.000");

  pinMode(buttonStart, INPUT_PULLUP);
  pinMode(buttonStop, INPUT_PULLUP);
  pinMode(buttonReset, INPUT_PULLUP);

  EEPROM.get(0, elapsedTime);
  displayTime();

  Timer1.initialize(1000); // 1 millisecond
  Timer1.attachInterrupt(timerISR);
}

void loop()
{
  handleButtonPresses();

  if (running)
  {
    displayTime();
  }
}

void timerISR()
{
  if (running)
  {
    elapsedTime++;
  }
}

void handleButtonPresses()
{
  if (digitalRead(buttonStart) == LOW)
  {
    if ((millis() - lastDebounceTimeStart) > debounceDelay)
    {
      running = true;
      lastDebounceTimeStart = millis();
    }
  }

  if (digitalRead(buttonStop) == LOW)
  {
    if ((millis() - lastDebounceTimeStop) > debounceDelay)
    {
      running = false;
      EEPROM.put(0, elapsedTime);
      lastDebounceTimeStop = millis();
    }
  }

  if (digitalRead(buttonReset) == LOW)
  {
    if ((millis() - lastDebounceTimeReset) > debounceDelay)
    {
      resetStopwatch();
      lastDebounceTimeReset = millis();
    }
  }
}

void displayTime()
{
  int millisecs = elapsedTime % 1000;
  int seconds = (elapsedTime / 1000) % 60;
  int minutes = (elapsedTime / 60000) % 60;

  lcd.setCursor(0, 0);

  if (minutes < 10)
  {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");

  if (seconds < 10)
  {
    lcd.print("0");
  }
  lcd.print(seconds);
  lcd.print(".");

  if (millisecs < 100)
  {
    lcd.print("0");
  }
  if (millisecs < 10)
  {
    lcd.print("0");
  }
  lcd.print(millisecs);
}

void resetStopwatch()
{
  elapsedTime = 0;
  EEPROM.put(0, elapsedTime);
  lcd.clear();
  lcd.print("00:00.000");
}
