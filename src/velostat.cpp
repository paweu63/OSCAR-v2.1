#include <iostream>
#include "Velostat.h"
#include <Arduino.h>


Velo::Velo(int pin, int l_pin) {
    Pin = pin;
    count++;
    ID = count;
    led_pin = l_pin;
    
}


int Velo::count = 0;

bool Velo::Check() {
    if(analogRead(Pin) < 3200) {
        digitalWrite(led_pin, LOW);
        return true;
    }
    else {
        digitalWrite(led_pin, HIGH);
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