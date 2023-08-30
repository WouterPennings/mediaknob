#include "Button2.h"

#define BUTTON_PIN 6

Button2 button;

void setup() {
  Serial.begin(9600);
  delay(50);
  Serial.println("\n\nMulti Handler Demo");

  button.begin(BUTTON_PIN);

  button.setClickHandler(click);
  button.setDoubleClickHandler(doubleClick);
  button.setTripleClickHandler(trippleClick);
  button.setLongClickDetectedHandler(LongClickDetected);
}

void loop() {
  button.loop();
}

void click(Button2& btn) {
  Serial.println("Single press");
}

void doubleClick(Button2& btn) {
  Serial.println("Double press");
}

void trippleClick(Button2& btn) {
  Serial.println("Tripple press");
}

void LongClickDetected(Button2& btn) {
  Serial.print("Long Pressed ");
  while (btn.isPressed()) {
    delay(100);
    Serial.print(".");
    button.loop();
  }
  Serial.println("Long Unpressed");
}