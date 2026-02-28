#include "pump.h"
#include <Arduino.h>
#include "decalarations.h"

Pump::Pump(int pin) {
    Pin = pin;
}

void Pump::start(int time) {
    delay(2000);
    digitalWrite(Pin, HIGH);
    delay(time*1000);
    digitalWrite(Pin, LOW);
    delay(2000);
}

void Pump::stop() {
    digitalWrite(Pin, LOW);
}

void Pump::venting(){
    if(digitalRead(ButtonVenting) == LOW){
        digitalWrite(Pin, HIGH);
    }
    else digitalWrite(Pin, LOW);
}
