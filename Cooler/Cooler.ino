#include <LiquidCrystal.h>
#include <EEPROM.h>

const int buttonIncreasePin = 2;
const int buttonDecreasePin = 3;
const int tempSensorPin = A1;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
volatile int threshold = 25;
float temperature = 0.0;

const char tempLabel[] = "Current Temp: ";
const char thresholdLabel[] = "Goal Temp: ";
const unsigned long TEMP_UPDATE_INTERVAL = 100;
const unsigned long DEBOUNCE_DELAY = 200;

volatile unsigned long lastIncreasePress = 0;
volatile unsigned long lastDecreasePress = 0;

void setup() {
  pinMode(buttonIncreasePin, INPUT_PULLUP);
  pinMode(buttonDecreasePin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonIncreasePin), increaseThreshold, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonDecreasePin), decreaseThreshold, FALLING);

  lcd.begin(16, 2);

  EEPROM.get(0, threshold);
  if (threshold < -40 || threshold > 125) {
    threshold = 25;
  }

  lcd.setCursor(0, 0);
  lcd.print(tempLabel);
  lcd.setCursor(0, 1);
  lcd.print(thresholdLabel);
  lcd.setCursor(12, 1);
  lcd.print(threshold);
  lcd.print("C     ");

  initializeTimer1();
}

void loop() {}

void increaseThreshold() {
  unsigned long currentTime = millis();
  if (currentTime - lastIncreasePress >= DEBOUNCE_DELAY) {
    lastIncreasePress = currentTime;
    threshold++;
    EEPROM.put(0, threshold);
    lcd.setCursor(12, 1);
    lcd.print(threshold);
    lcd.print("C     ");
  }
}

void decreaseThreshold() {
  unsigned long currentTime = millis();
  if (currentTime - lastDecreasePress >= DEBOUNCE_DELAY) {
    lastDecreasePress = currentTime;
    threshold--;
    EEPROM.put(0, threshold);
    lcd.setCursor(12, 1);
    lcd.print(threshold);
    lcd.print("C     ");
  }
}

void initializeTimer1() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 31249;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect) {
  int tempReading = analogRead(tempSensorPin);
  temperature = map(tempReading, 0, 1023, -40, 125);
  lcd.setCursor(14, 0);
  lcd.print(temperature);
  lcd.print("C     ");
}
