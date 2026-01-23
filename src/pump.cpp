#include "pump.h"
#include <Arduino.h>

Pump::Pump(int pin) {
    Pin = pin;
}

void Pump::start(int time) {
    digitalWrite(Pin, HIGH);
    delay(time*1000);
    digitalWrite(Pin, LOW);
}

void Pump::stop() {
    digitalWrite(Pin, LOW);
}
