#include <Servo.h>
#include <LiquidCrystal.h>

const int servoPin = 6;
const int buzzerPin = 7;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

Servo myServo;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int currentAngle = 0;
unsigned long lastUpdateTime = 0;
const int interval = 1000;
int steps = 0;
const int totalSteps = 10;

void setup() {
  myServo.attach(servoPin);
  myServo.write(currentAngle);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Countdown:");
}

void loop() {
  unsigned long currentTime = millis();

  if (steps < totalSteps) {
    if (currentTime - lastUpdateTime >= interval) {
      lastUpdateTime = currentTime;
      currentAngle += 18;
      steps++;
      myServo.write(currentAngle);
      
      int remainingSeconds = totalSteps - steps;
      lcd.setCursor(0, 1);
      lcd.print("Timer: ");
      lcd.print(remainingSeconds);
      lcd.print(" sec     ");
    }
  } else if (steps == totalSteps) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time is up!");
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);

    steps = 0;
    currentAngle = 0;
    myServo.write(currentAngle);
    lastUpdateTime = currentTime;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Countdown:");
  }
}
