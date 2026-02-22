#include <ESP32Servo.h>

class Velo {
    private: 
    int Pin;
    int ID;
    static int count;
    int led_pin;
    Servo *Servo1;
    Servo *Servo2;
    int Target_S1_angle;
    int Target_S2_angle;
    
    public:
    Velo(int, int, Servo*, Servo*, int, int);
    bool Check();   
    void debug();
    void move();
    
};