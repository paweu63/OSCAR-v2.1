#include <Arduino.h>
#include <ESP32Servo.h>
#include "Velostat.h"
#include "pump.h"
#include "decalarations.h"

Servo servo1;
Servo servo2;

Velo v1(VeloPin1, LedPin1, &servo1, &servo2);
Velo v2(VeloPin2, LedPin2, &servo1, &servo2);
Velo v3(VeloPin3, LedPin3, &servo1, &servo2);
Velo v4(VeloPin4, LedPin4, &servo1, &servo2);
Velo v5(VeloPin5, LedPin5, &servo1, &servo2);
Pump p1(PumpPin);


enum Robot_state {
  IDLE,
  WAITING_FOR_BUTTON,
  MOVE,
  WAIT_FOR_EMPTY,

};

Robot_state state = IDLE;

bool Move();
bool Any_Velo_Placed();


void setup() {
  Serial.begin(115200);

  pinMode(VeloPin2, INPUT);
  pinMode(VeloPin3, INPUT);
  pinMode(VeloPin5, INPUT);
  pinMode(PumpPin, OUTPUT);
  pinMode(LedPin1, OUTPUT);
  pinMode(LedPin2, OUTPUT);
  pinMode(LedPin3, OUTPUT);
  pinMode(LedPin5, OUTPUT);
  
  pinMode(ButtonMove, INPUT_PULLUP);
  pinMode(ButtonPump, INPUT_PULLUP);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  servo1.attach(SERVO_PIN_1, 500, 2400);
  servo2.attach(SERVO_PIN_2, 500, 2400);
  servo1.write(0);
  servo2.write(0);
}

void loop() {

  switch (state)
  {
    case IDLE:
      servo1.write(0);
      servo2.write(0);
      p1.stop();
      if(Any_Velo_Placed()) {state = WAITING_FOR_BUTTON;}
    break;

    case WAITING_FOR_BUTTON:
      if(digitalRead(ButtonMove) == LOW ) {state = MOVE;}
      if(!Any_Velo_Placed()) {state = IDLE;}
    break;

    case MOVE:
     if(Move() == true) {state = WAIT_FOR_EMPTY;}
    break;
    
    case WAIT_FOR_EMPTY:
      if(!Any_Velo_Placed()) {state = IDLE;}
    break;
  }

}


bool Any_Velo_Placed() {
  return v1.Check() || v2.Check() || v3.Check() || v5.Check();
}
bool Move(){
  if(v1.Check()){
    servo1.write(22);
    servo2.write(32);
    delay(1000);
    p1.start(11);
    delay(1000);
  }
  if (v2.Check()){
    servo1.write(26);
    servo2.write(6);
    delay(1000);
    p1.start(11);
    delay(1000);
  }
  if (v3.Check()){
    servo1.write(45);
    servo2.write(0);
    delay(1000);
    p1.start(11);
    delay(1000);
  }

 if(v5.Check()){
   servo1.write(165);
   servo2.write(164);
   delay(2000);
   p1.start(11);
   delay(1000);
  }
  servo1.write(0);
  servo2.write(0);
  return true;
}

 
 
  

