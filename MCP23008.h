#include "spark_wiring_i2c.h"
#include "spark_wiring_usbserial.h"
#include "spark_wiring_constants.h"
#include "spark_wiring.h"

class MCP23008{
public:
    void setAddress(int a1, int a2, int a3);
    int readAllInputs();

    bool initialized;

private:
    int address = 0x20;
    unsigned long timeout = 100;
    bool inFailureMode = false;
    int address1;
    int address2;
    int address3;
};