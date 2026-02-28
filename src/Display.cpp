#include <Arduino.h>
#include "Display.h"

MyDisplay::MyDisplay() : display(128, 64, &Wire, -1) {}

void MyDisplay::setupDisplay() {
    display.begin(0x3C, true);
    display.setRotation(0);
    display.setTextColor(SH110X_WHITE);
    display.clearDisplay();
    display.display();
}

void MyDisplay::showMessage(String text) {
    display.clearDisplay();      
    // display.setCursor(0, 0);    
    // display.setTextSize(1);
    // display.println("STATUS:");  
    display.setTextSize(2);      
    display.setCursor(0, 0);
    display.println(text);      
    display.display();          
}