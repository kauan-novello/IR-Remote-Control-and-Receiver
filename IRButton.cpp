#include "IRButton.h"
#include <IRremote.h>

IRButton::IRButton(int pin, long irCode) : pin(pin), irCode(irCode), lastState(HIGH) {}

void IRButton::begin() {
  pinMode(pin, INPUT_PULLUP);
}

void IRButton::update() {
  boolean currentState = digitalRead(pin);
  if (currentState != lastState) {
    if (currentState == LOW) {
      irsend.sendSony(irCode, 32);
      Serial.print("Sending IR code from pin ");
      Serial.println(pin);
    }
    lastState = currentState;
  }
}
