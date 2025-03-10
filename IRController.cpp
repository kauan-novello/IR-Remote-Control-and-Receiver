#include "IRController.h"

IRController::IRController(int recvPin) : irrecv(recvPin) {}

void IRController::begin() {
  irrecv.enableIRIn();
}

void IRController::checkReceiver() {
  if (irrecv.decode(&results)) {
    Serial.print("Código HEX: ");
    Serial.println(results.value, HEX);
    Serial.print("Código DEC: ");
    Serial.println(results.value);
    Serial.println();
    irrecv.resume();
  }
}
