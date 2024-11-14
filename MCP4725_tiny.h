#ifndef _MCP4725_TINY_H_
#define _MCP4725_TINY_H_

#include <TinyWireM.h> // Use TinyWireM for ATtiny85
#include <stdint.h>

#define MCP4725_I2CADDR_DEFAULT (0x62) ///< Default i2c address
#define MCP4725_CMD_WRITEDAC (0x40)    ///< Writes data to the DAC
#define MCP4725_CMD_WRITEDACEEPROM (0x60) ///< Writes data to the DAC and the EEPROM

/**************************************************************************/
/*!
    @brief  Class for communicating with an MCP4725 DAC
*/
/**************************************************************************/
class MCP4725_tiny {
public:
  MCP4725_tiny();
  bool begin(uint8_t i2c_address = MCP4725_I2CADDR_DEFAULT);
  bool setVoltage(uint16_t output, bool writeEEPROM);

private:
  uint8_t _i2c_address;
};

#endif
