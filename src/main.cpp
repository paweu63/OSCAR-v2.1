#include <Arduino.h>
#include <ESP32Servo.h>
#include "Velostat.h"
#include "pump.h"
#include "decalarations.h"

Servo servo1;
Servo servo2;

Velo v1(VeloPin1, LedPin1, &servo1, &servo2,V1_S1_TARGET_ANGLE,V1_S2_TARGET_ANGLE);
Velo v2(VeloPin2, LedPin2, &servo1, &servo2,V2_S1_TARGET_ANGLE,V2_S2_TARGET_ANGLE);
Velo v3(VeloPin3, LedPin3, &servo1, &servo2,V3_S1_TARGET_ANGLE,V3_S2_TARGET_ANGLE);
Velo v4(VeloPin4, LedPin4, &servo1, &servo2,V4_S1_TARGET_ANGLE,V4_S2_TARGET_ANGLE);
Velo v5(VeloPin5, LedPin5, &servo1, &servo2,V5_S1_TARGET_ANGLE,V5_S2_TARGET_ANGLE);

Velo* all_glasses[] = {
  &v1,&v2,&v3,&v4,&v5
};
int current_glass_index;
Pump p1(PumpPin);


enum Robot_state {
  IDLE,
  WAITING_FOR_BUTTON,
  MOVE,
  POUR,
  WAIT_FOR_EMPTY,

};

Robot_state state = IDLE;

bool Any_Velo_Placed();


void setup() {
  Serial.begin(115200);
  pinMode(VeloPin1, INPUT);
  pinMode(VeloPin2, INPUT);
  pinMode(VeloPin3, INPUT);
  pinMode(VeloPin4, INPUT);
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
      current_glass_index = 0;
      if(Any_Velo_Placed()) {state = WAITING_FOR_BUTTON;}
    break;

    case WAITING_FOR_BUTTON:
      if(digitalRead(ButtonMove) == LOW ) {state = MOVE;}
      if(!Any_Velo_Placed()) {state = IDLE;}
    break;

    case MOVE:
      if (current_glass_index >= TOTAL_GLASSES) {
        state = WAIT_FOR_EMPTY;
      } 
      else if (all_glasses[current_glass_index]->Check())
         {
          all_glasses[current_glass_index]->move(); 
          delay(3000);
          state = POUR;
        } 
      else {
        current_glass_index++;
      }
    break;

    case POUR:
      p1.start(11);
      current_glass_index++;
      state = MOVE; 
    break;
    
    case WAIT_FOR_EMPTY:
      servo1.write(180);
      servo2.write(180);
      if(!Any_Velo_Placed()) {state = IDLE;}
    break;
  }
}


bool Any_Velo_Placed() {
  for (int i = 0; i < TOTAL_GLASSES; i++) {
    if (all_glasses[i]->Check()) {
      return true; 
    }
  }
  return false;
}


 
 
  

