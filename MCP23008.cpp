#include "MCP23008.h"

void MCP23008::setAddress(int a0, int a1, int a2){
	address1 = a0;
	address2 = a1;
	address3 = a2;
    if(a0 == 1){
        address = address | 1;
    }
    if(a1 == 1){
        address = address | 2;
    }
    if(a2 == 1){
        address = address | 4;
    }
    //Start I2C port
    Wire.begin();
    //Open connection to specified address
    retryAddress1:
    Wire.beginTransmission(address);
    //Set all channel directions
    Wire.write(0x00);
    Wire.write(0xff);
    //Determine if device is present at that address
    byte status = Wire.endTransmission();
    if(status != 0){
        initialized = false;
        return;
    }else{
        initialized = true;
    }
    
    Wire.beginTransmission(address);
    Wire.write(0x06);
    Wire.write(0xff);
    status = Wire.endTransmission();
    if(status != 0){
        initialized = false;
        return;
    }else{
        initialized = true;
    }
}

int MCP23008::readAllInputs(){
    int inputStatus = 256;

	if(!initialized){
		//ReInitialize i2c chip.
		setAddress(address1, address2, address3);
	}

    Wire.beginTransmission(address);
    Wire.write(0x09);
    byte status = Wire.endTransmission();
    if(status != 0){
    	//Chip did not respond to write.
    	initialized = false;
    	Serial.println("Failed to write");
    	delay(1000);
        return 256;
    }else{
        initialized = true;
    }
    Wire.requestFrom(address, 1);
    unsigned long startTime = millis();
    while(Wire.available() != 1 && millis()<startTime+timeout);
    if(Wire.available() != 1){
    	return 256;
    }
    //All clear
    inputStatus = Wire.read();
    return inputStatus;
}