/*
 * PaccerMain
 * =========
 * 
 * Arduino sketch for managing the input, common and output libraries.
 * -> e.g. tick() each one every loop()
 *
 * Created 2022-05-20
 * 
 * https://github.com/PaccerPinball/PaccerMain
 */


#include <PaccerInput.h>
#include <PaccerCommon.h>
#include <PaccerOutput.h>
#include <PaccerSound.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Output
LiquidCrystal_I2C lcd(0x27, 16, 2);
PaccerSound sound(8, 105);

PaccerOutput output(&lcd, &sound);

// Common
PaccerCommon common(&output);

// Input
PaccerInput input(&common);


void setup() {
  Serial.begin(115200);
  Serial.println("-------- PACCER START --------");
  lcd.init();
  lcd.backlight();
  output.updateScore(0);
  output.sound(SOUND_STARTUP);
}

unsigned long lastMillis = 0;
void loop() {
  unsigned long tickTime = millis() - lastMillis;
  if (lastMillis != 0 && tickTime > 5) {
    Serial.print("!! WARNING !! - Long tick: ");
    Serial.print(millis() - lastMillis);
    Serial.println("ms");
  }
  lastMillis = millis();
  input.tick();
  common.tick();
  output.tick();
  sound.tick();
}
