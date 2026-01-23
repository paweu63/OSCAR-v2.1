#include <Arduino.h>
#include <ESP32Servo.h>
#include "Velostat.h"
#include "pump.h"


/////////////////////////////////////////////
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

bool startSignalFromPython = false;
const char* ssid = "Chrystusaowe_lacze";
const char* password = "Laski997";
/////////////////////////////////////////////
#define VeloPin1 39
#define VeloPin2 34
#define VeloPin3 35
#define VeloPin5 36 
#define ButtonMove 19
#define ButtonPump 18
#define PumpPin 21

const int SERVO_PIN_1 = 22;
const int SERVO_PIN_2 = 5;

Servo servo1;
Servo servo2;

Velo v1(VeloPin1);
Velo v2(VeloPin2);
Velo v3(VeloPin3);
Velo v5(VeloPin5);
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

  /////////////////////////////////
  WiFi.begin(ssid, password);
    Serial.print("Laczenie z WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP()); // TO IP WPISZESZ DO PYTHONA

    // --- 2. ENDPOINT DLA PYTHONA ---
    server.on("/start", []() {
      Serial.println("Python: START!");
      startSignalFromPython = true; // Ustawiamy flagę
      server.send(200, "text/plain", "OK"); 
    });

    // --- 3. BRAKOWAŁO STARTU SERWERA ---
    server.begin(); 
    Serial.println("Serwer HTTP wystartowal");
  ////////////////////////////////
  pinMode(VeloPin1, INPUT);
  pinMode(VeloPin2, INPUT);
  pinMode(VeloPin3, INPUT);
  pinMode(VeloPin5, INPUT);
  pinMode(PumpPin, OUTPUT);

  
  pinMode(ButtonMove, INPUT_PULLUP);
  pinMode(ButtonPump, INPUT_PULLUP);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  servo1.attach(SERVO_PIN_1, 500, 2400);
  servo2.attach(SERVO_PIN_2, 500, 2400);
  servo1.write(180);
  servo2.write(180);
}

void loop() {
  ///////////////////////////////
  server.handleClient();
  //////////////////////////
  switch (state)
  {
    case IDLE:
      servo1.write(0);
      servo2.write(0);
      p1.stop();
      startSignalFromPython = false;
      if(Any_Velo_Placed()) {state = WAITING_FOR_BUTTON;}
    break;

    case WAITING_FOR_BUTTON:
      if(digitalRead(ButtonMove) == LOW || startSignalFromPython == true) {state = MOVE;}
      if(!Any_Velo_Placed()) {state = IDLE;}
    break;

    case MOVE:
     if(Move() == true) {state = WAIT_FOR_EMPTY;}
    break;
    
    case WAIT_FOR_EMPTY:
      if(!Any_Velo_Placed()) {state = IDLE; startSignalFromPython = false;}
    break;
  }
  Serial.println(state);
  Serial.println(Any_Velo_Placed());
  

  //  if(digitalRead(ButtonPump) == LOW){
  //    digitalWrite(PumpPin, HIGH);
  //  }
  //  else digitalWrite(PumpPin, LOW);
  
}


bool Any_Velo_Placed() {
  bool Velo_state[] = {v1.Check(),v2.Check(), v3.Check(), v5.Check()};
  for(int i =0; i<4; i++) {
    if(Velo_state[i] == true) return true;
  }
  return false;
}
bool Move(){
  if(v1.Check()){
    servo1.write(25);
    servo2.write(28);
    delay(1000);
    p1.start(12);
    delay(1000);
  }
  if (v2.Check()){
    servo1.write(31);
    servo2.write(6);
    delay(1000);
    p1.start(12);
    delay(1000);
  }
  if (v3.Check()){
    servo1.write(52);
    servo2.write(0);
    delay(1000);
    p1.start(12);
    delay(1000);
  }

 if(v5.Check()){
   servo1.write(169);
   servo2.write(164);
   delay(2000);
   p1.start(12);
   delay(1000);
  }
  servo1.write(0);
  servo2.write(0);
  return true;
}

 
 
  

