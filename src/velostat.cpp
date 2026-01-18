#include <iostream>
#include "Velostat.h"
#include <Arduino.h>


bool Velo::Check() {
    if(analogRead(Pin) < 2000) {
        return true;
    }
    else {
        return false;
    }
}

Velo::Velo(int pin) {
    Pin = pin; 
}