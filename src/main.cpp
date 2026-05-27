#include <Adafruit_MCP23X17.h>

const uint8_t MCP23017_WRITE_ADDRESS = 0x40;
const uint8_t MCP23017_I2C_ADDRESS = MCP23017_WRITE_ADDRESS >> 1;

Adafruit_MCP23X17 mcp;

void setup() {

  Serial.begin(9600);

  mcp.begin_I2C(MCP23017_I2C_ADDRESS);

  // Configure all PORTA pins (0-15) as outputs

  for(int pin = 0; pin < 16; pin++) {

    mcp.pinMode(pin, OUTPUT);

  }

}

void loop() {

  // Running light effect

  for(int pin = 0; pin < 16; pin++) {

    mcp.digitalWrite(pin, HIGH);
    delay(100);

  }
  delay(2000);
    for(int pin = 0; pin < 16; pin++) {

    mcp.digitalWrite(pin, LOW);
    delay(100);

  }
}
