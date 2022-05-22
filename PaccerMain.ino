/*
 * PaccerMain
 * =========
 * 
 * Arduino sketch for managing the input, common and output libraries.
 * -> e.g. tick() each one every loop()
 *
 * Created 2022-05-20
 * 
 * https://github.com/PaccerPinball/PaccerCommon
 */


#include <PaccerInput.h>
#include <PaccerCommon.h>
#include <PaccerOutput.h>
#include <LiquidCrystal.h>

// Output
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

PaccerOutput output(&lcd, 16, 2);

// Common
PaccerCommon common(&output);

// Input
PaccerInput input(&common);


void setup() {
  Serial.begin(9600);
  Serial.println("-------- PACCER START --------");
}

void loop() {
  input.tick();
  common.tick();
  output.tick();
}
