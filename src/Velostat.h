#include <ESP32Servo.h>

class Velo {
    private: 
    int Pin;
    int ID;
    static int count;
    int led_pin;
    Servo *Servo1;
    Servo *Servo2;
    
    public:
    Velo(int, int, Servo*, Servo*);
    bool Check();   
    void debug();
    void move();
    
};