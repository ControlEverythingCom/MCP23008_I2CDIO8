// This #include statement was automatically added by the Particle IDE.
#include "MCP23008.h"

MCP23008 inputBoard;

void setup() {
    inputBoard.setAddress(1,0,0);
    if(!inputBoard.initialized){
        Serial.println("Expansion not initialized");
    }else{
        Serial.println("Expansion ready");
    }
}

void loop() {
    Serial.printf("Input Status %i \n", inputBoard.readAllInputs());
}