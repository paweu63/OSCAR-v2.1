#include <Arduino.h>
#include <ESP32Servo.h>
#include "Velostat.h"

#define VeloPin5 34
#define VeloPin1 2 
#define VeloPin2 15
#define VeloPin3 4 
#define VeloPin5 34 
#define ButtonJazda 19

const int SERVO_PIN_1 = 22;
const int SERVO_PIN_2 = 5;

Servo servo1;
Servo servo2;

Velo v1(VeloPin1);
Velo v2(VeloPin2);
Velo v3(VeloPin3);
Velo v5(VeloPin5);

void Jazda_z_kurawmi();


void setup() {
  pinMode(VeloPin1, INPUT);
  pinMode(VeloPin2, INPUT);
  pinMode(VeloPin3, INPUT);
  pinMode(VeloPin5, INPUT);

  Serial.begin(115200);
  pinMode(ButtonJazda, INPUT_PULLUP);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  servo1.attach(SERVO_PIN_1, 500, 2400);
  servo2.attach(SERVO_PIN_2, 500, 2400);
  servo1.write(180);
  servo2.write(180);
}

void loop() {
   if(digitalRead(ButtonJazda) == LOW){
    Jazda_z_kurawmi();
   }
}

void Jazda_z_kurawmi(){
  if(v1.Check() == HIGH){
    servo1.write(60);
    servo2.write(100);
  }
  if (v2.Check() == HIGH){
    servo1.write(60);
    servo2.write(10);
  }
  if (v3.Check() == HIGH){
    servo1.write(100);
    servo2.write(10);
  }

else if(v5.Check() == HIGH){
   servo1.write(150);
   servo2.write(10);
}
  
}

 
 
  

