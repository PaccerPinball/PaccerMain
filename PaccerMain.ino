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
#include <Servo.h>

// Other pins get connected to GND
#define MOTOR_PACMAN 5
#define SERVO_PIN 10

#define LED_RUNNING 12
#define LED_WARNING 13
#define WARNING_TIME 300

// Output
LiquidCrystal_I2C lcd(0x27, 16, 2);
PaccerSound sound(8, 105);
Adafruit_NeoPixel leds(35, 2, NEO_GRB + NEO_KHZ800);
Servo servo;

PaccerOutput output(&lcd, &sound, &leds, MOTOR_PACMAN, &servo);

// Common
PaccerCommon common(&output);

// Input
PaccerInput input(&common);


void setup() {
  Serial.begin(115200);
  Serial.println("-------- PACCER START --------");
  
  lcd.begin();
  lcd.backlight();
  leds.begin();
  leds.setBrightness(100);
  leds.fill(leds.Color(255, 255, 0));
  output.updateScore(0);
  output.sound(SOUND_STARTUP);
  output.led(LED_STARTUP);
  output.motor(150); // 100 should work for one motor; 150 for both?
  servo.write(54);
  servo.attach(SERVO_PIN);

  pinMode(LED_RUNNING, OUTPUT);
  pinMode(LED_WARNING, OUTPUT);
}

unsigned long lastMillis = 0;
unsigned long warningLedMillis = 0;
void loop() {
  if (lastMillis != 0 && millis() - lastMillis > 10) {
    Serial.print("!! WARNING !! - Long tick: ");
    Serial.print(millis() - lastMillis);
    Serial.println("ms");
    digitalWrite(LED_WARNING, HIGH);
    warningLedMillis = millis();
  }
  // Warning LED timer
  if (warningLedMillis + WARNING_TIME < millis() && warningLedMillis != 0) {
    warningLedMillis = 0;
    digitalWrite(LED_WARNING, LOW);
    Serial.println("Turning warning LED off");
  }
  // Blink running LED
  if (millis() % 1000 > 500) digitalWrite(LED_RUNNING, HIGH); 
  else digitalWrite(LED_RUNNING, LOW);
  
  lastMillis = millis();
  input.tick();
  common.tick();
  output.tick();
  sound.tick();
}
