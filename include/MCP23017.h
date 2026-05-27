#ifndef MCP23017_H
#define MCP23017_H

#include <Arduino.h>
#include <Wire.h>

// MCP23017 Register Addresses
#define IODIRA   0x00  // I/O Direction Register A
#define IODIRB   0x01  // I/O Direction Register B
#define IPOLA    0x02  // Input Polarity Register A
#define IPOLB    0x03  // Input Polarity Register B
#define GPINTENA 0x04  // Interrupt-on-Change Register A
#define GPINTENB 0x05  // Interrupt-on-Change Register B
#define DEFVALA  0x06  // Default Value Register A
#define DEFVALB  0x07  // Default Value Register B
#define INTCONA  0x08  // Interrupt Control Register A
#define INTCONB  0x09  // Interrupt Control Register B
#define IOCON    0x0A  // I/O Expander Configuration Register
#define GPPUA    0x0C  // Pull-Up Resistor Register A
#define GPPUB    0x0D  // Pull-Up Resistor Register B
#define INTFA    0x0E  // Interrupt Flag Register A
#define INTFB    0x0F  // Interrupt Flag Register B
#define INTCAPA  0x10  // Interrupt Captured Value Register A
#define INTCAPB  0x11  // Interrupt Captured Value Register B
#define GPIOA    0x12  // General Purpose I/O Port Register A
#define GPIOB    0x13  // General Purpose I/O Port Register B
#define OLATA    0x14  // Output Latch Register A
#define OLATB    0x15  // Output Latch Register B

class MCP23017 {
private:
  uint8_t i2cAddress;
  
public:
  // Constructor
  MCP23017(uint8_t address = 0x20);
  
  // Initialize the MCP23017
  void begin();
  
  // Set pin direction (0 = OUTPUT, 1 = INPUT)
  void pinMode(uint8_t pin, uint8_t mode);
  
  // Write to a pin
  void digitalWrite(uint8_t pin, uint8_t value);
  
  // Read from a pin
  uint8_t digitalRead(uint8_t pin);
  
  // Write to entire port
  void writePort(uint8_t port, uint8_t value);
  
  // Read entire port
  uint8_t readPort(uint8_t port);
  
  // Enable pull-up resistor
  void pullUp(uint8_t pin, bool enable);
  
  // Write to a register
  void writeRegister(uint8_t reg, uint8_t value);
  
  // Read from a register
  uint8_t readRegister(uint8_t reg);
};

#endif
