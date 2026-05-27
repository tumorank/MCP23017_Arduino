#include "MCP23017.h"

MCP23017::MCP23017(uint8_t address) {
  i2cAddress = address;
}

void MCP23017::begin() {
  // Initialize I2C
  Wire.begin();
  
  // Set default configuration
  // Disable sequential operation, enable addressing
  writeRegister(IOCON, 0x00);
  
  // Set all pins as inputs by default
  writeRegister(IODIRA, 0xFF);
  writeRegister(IODIRB, 0xFF);
}

void MCP23017::writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t MCP23017::readRegister(uint8_t reg) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(i2cAddress, (uint8_t)1);
  return Wire.read();
}

void MCP23017::pinMode(uint8_t pin, uint8_t mode) {
  uint8_t regAddr = (pin < 8) ? IODIRA : IODIRB;
  uint8_t bitPos = pin % 8;
  uint8_t currentValue = readRegister(regAddr);
  
  if (mode == OUTPUT) {
    currentValue &= ~(1 << bitPos);  // Clear bit for output
  } else {
    currentValue |= (1 << bitPos);   // Set bit for input
  }
  
  writeRegister(regAddr, currentValue);
}

void MCP23017::digitalWrite(uint8_t pin, uint8_t value) {
  uint8_t regAddr = (pin < 8) ? GPIOA : GPIOB;
  uint8_t bitPos = pin % 8;
  uint8_t currentValue = readRegister(regAddr);
  
  if (value == HIGH) {
    currentValue |= (1 << bitPos);   // Set bit high
  } else {
    currentValue &= ~(1 << bitPos);  // Clear bit low
  }
  
  writeRegister(regAddr, currentValue);
}

uint8_t MCP23017::digitalRead(uint8_t pin) {
  uint8_t regAddr = (pin < 8) ? GPIOA : GPIOB;
  uint8_t bitPos = pin % 8;
  uint8_t value = readRegister(regAddr);
  
  return (value >> bitPos) & 1;
}

void MCP23017::writePort(uint8_t port, uint8_t value) {
  uint8_t regAddr = (port == 0) ? GPIOA : GPIOB;
  writeRegister(regAddr, value);
}

uint8_t MCP23017::readPort(uint8_t port) {
  uint8_t regAddr = (port == 0) ? GPIOA : GPIOB;
  return readRegister(regAddr);
}

void MCP23017::pullUp(uint8_t pin, bool enable) {
  uint8_t regAddr = (pin < 8) ? GPPUA : GPPUB;
  uint8_t bitPos = pin % 8;
  uint8_t currentValue = readRegister(regAddr);
  
  if (enable) {
    currentValue |= (1 << bitPos);   // Enable pull-up
  } else {
    currentValue &= ~(1 << bitPos);  // Disable pull-up
  }
  
  writeRegister(regAddr, currentValue);
}
