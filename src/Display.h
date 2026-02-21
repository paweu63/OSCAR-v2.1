#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>

class MyDisplay {
private:
    Adafruit_SH1106G display;
public:
    MyDisplay();
    void setupDisplay();
    void showMessage(String text);
     
};
