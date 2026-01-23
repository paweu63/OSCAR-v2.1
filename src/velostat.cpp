#include <iostream>
#include "Velostat.h"
#include <Arduino.h>


Velo::Velo(int pin) {
    Pin = pin;
    count++;
    ID = count;
}


int Velo::count = 0;

bool Velo::Check() {
    if(analogRead(Pin) < 2000) {
        return true;
    }
    else {
        return false;
    }
}

void Velo::debug() {
    Serial.print("V");
    Serial.print(ID);
    Serial.print(": ");
    Serial.print(Check());
    Serial.print(" amount: ");
    Serial.print(analogRead(Pin));
    Serial.print('\n');
    delay(500);
}