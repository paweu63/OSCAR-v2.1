#include <Arduino.h>
#include <ESP32Servo.h>
#include "Velostat.h"
#include "pump.h"
#include "Display.h"
#include "decalarations.h"

Servo servo1;
Servo servo2;
MyDisplay screen;

Velo v1(VeloPin1, LedPin1, &servo1, &servo2,V1_S1_TARGET_ANGLE,V1_S2_TARGET_ANGLE,VELO1_threshold);
Velo v2(VeloPin2, LedPin2, &servo1, &servo2,V2_S1_TARGET_ANGLE,V2_S2_TARGET_ANGLE,VELO2_threshold);
Velo v3(VeloPin3, LedPin3, &servo1, &servo2,V3_S1_TARGET_ANGLE,V3_S2_TARGET_ANGLE,VELO3_threshold);
Velo v4(VeloPin4, LedPin4, &servo1, &servo2,V4_S1_TARGET_ANGLE,V4_S2_TARGET_ANGLE,VELO4_threshold);
Velo v5(VeloPin5, LedPin5, &servo1, &servo2,V5_S1_TARGET_ANGLE,V5_S2_TARGET_ANGLE,VELO5_threshold);

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
void Servo_debug();
void goToState(Robot_state newState, String msg);

void setup() {
  Serial.begin(115200);
  screen.setupDisplay();
  goToState(IDLE, "Chlusniem bo usniem");
  pinMode(VeloPin1, INPUT);
  pinMode(VeloPin2, INPUT);
  pinMode(VeloPin3, INPUT);
  pinMode(VeloPin4, INPUT);
  pinMode(VeloPin5, INPUT);
  pinMode(PumpPin, OUTPUT);
  pinMode(LedPin1, OUTPUT);
  pinMode(LedPin2, OUTPUT);
  pinMode(LedPin3, OUTPUT);
  pinMode(LedPin4, OUTPUT);
  pinMode(LedPin5, OUTPUT);
  
  pinMode(ButtonMove, INPUT_PULLUP);
  pinMode(ButtonVenting, INPUT_PULLUP);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  servo1.attach(SERVO_PIN_1,  300, 2600);
  servo2.attach(SERVO_PIN_2, 300, 2600);
  servo1.write(0);
  servo2.write(0);
  p1.stop();
}

void loop() {
  // Servo_debug();
  // v1.debug();
  // v2.debug();
  // v3.debug();
  // v4.debug();
  // v5.debug();

  switch (state)
  {
    case IDLE:
      servo1.write(0);
      servo2.write(0);
      p1.venting();
      current_glass_index = 0;
      if(Any_Velo_Placed()) {goToState(WAITING_FOR_BUTTON, "DAWAJ \nPODJEZDZAJ");}
    break;

    case WAITING_FOR_BUTTON:
      if(digitalRead(ButtonMove) == LOW ) {goToState(MOVE, "Mlocek\nchuj");}
      if(!Any_Velo_Placed()) {goToState(IDLE, "Chlusniem bo usniem");}
    break;

    case MOVE:
      if (current_glass_index >= TOTAL_GLASSES) {
        goToState(WAIT_FOR_EMPTY, "Ciach\nbabke\nw piach!");
      } 
      else if (all_glasses[current_glass_index]->Check())
         {
          all_glasses[current_glass_index]->move(); 
          goToState(POUR, "Mlocek\nchuj");
        } 
      else {
        current_glass_index++;
      }
    break;

    case POUR:
      p1.start(10);
      current_glass_index++;
      goToState(MOVE, "Mlocek\nchuj"); 
    break;
    
    case WAIT_FOR_EMPTY:
      servo1.write(180);
      servo2.write(180);
      if(!Any_Velo_Placed()) {delay(3000); goToState(IDLE, "Chlusniem bo usniem");}
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


 void Servo_debug() {
  if (Serial.available() > 0) {
    int num = Serial.parseInt();
    int pos = Serial.parseInt();  

    if (num == 1) {
      servo1.write(pos);
      Serial.print(">>> Servo 1 -> "); Serial.println(pos);
    } 
    else if (num == 2) {
      servo2.write(pos);
      Serial.print(">>> Servo 2 -> "); Serial.println(pos);
    }
    
   
    while(Serial.available() > 0) Serial.read();
  }
 }
 
void goToState(Robot_state newState, String msg) {
  state = newState;
  screen.showMessage(msg);
}
 
