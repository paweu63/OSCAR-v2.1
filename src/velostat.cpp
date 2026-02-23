#include <iostream>
#include "Velostat.h"
#include <Arduino.h>
#include <ESP32Servo.h>


Velo::Velo(int pin, int l_pin, Servo* s1, Servo* s2,int t_a1,int t_a2) {
    Pin = pin;
    count++;
    ID = count;
    led_pin = l_pin;
    Servo1 = s1;
    Servo2 = s2;
    Target_S1_angle = t_a1;
    Target_S2_angle = t_a2;
}


int Velo::count = 0;

bool Velo::Check() {
    if(analogRead(Pin) < 3300) {
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

void Velo::move() {
    Servo1->write(Target_S1_angle);
    Servo2->write(Target_S2_angle);
}