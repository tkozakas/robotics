#include <Arduino.h>
#include <EEPROM.h>

#define BUTTON_PIN 2
#define BUZZER_PIN 8
#define EEPROM_ADDR 0

volatile bool running = false;
volatile bool buttonPressed = false;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;

void handleButtonPress()
{
    buttonPressed = true;
}

void startStopwatch()
{
    startTime = millis() - elapsedTime;
    running = true;
    tone(BUZZER_PIN, 1000, 100); // Beep when starting
    Serial.println("Stopwatch started");
}

void stopStopwatch()
{
    elapsedTime = millis() - startTime;
    running = false;

    // Save the time to EEPROM
    EEPROM.write(EEPROM_ADDR, elapsedTime & 0xFF);
    EEPROM.write(EEPROM_ADDR + 1, (elapsedTime >> 8) & 0xFF);

    tone(BUZZER_PIN, 500, 100); // Beep when stopping
    Serial.print("Stopwatch stopped at: ");
    Serial.print(elapsedTime);
    Serial.println(" ms");
}

void displayTime(unsigned long time)
{
    // Replace this with code to update your display (LCD, 7-segment, etc.)
    Serial.print("Elapsed time: ");
    Serial.print(time);
    Serial.println(" ms");
}

void setup()
{
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);

    // Retrieve saved time from EEPROM
    elapsedTime = EEPROM.read(EEPROM_ADDR) | (EEPROM.read(EEPROM_ADDR + 1) << 8);

    Serial.print("Last recorded time: ");
    Serial.print(elapsedTime);
    Serial.println(" ms");
}

void loop()
{
    if (buttonPressed)
    {
        buttonPressed = false;

        if (!running)
        {
            startStopwatch();
        }
        else
        {
            stopStopwatch();
        }
    }

    if (running)
    {
        displayTime(millis() - startTime);
    }
}