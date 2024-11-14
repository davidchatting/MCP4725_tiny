#include "MCP4725_tiny.h"

/**************************************************************************/
/*!
    @brief  Instantiates a new MCP4725_tiny class
*/
/**************************************************************************/
MCP4725_tiny::MCP4725_tiny() {}

/**************************************************************************/
/*!
    @brief  Setups the hardware and checks the DAC was found
    @param i2c_address The I2C address of the DAC, defaults to 0x62
    @returns True if DAC was found on the I2C address.
*/
/**************************************************************************/
bool MCP4725_tiny::begin(uint8_t i2c_address) {
  _i2c_address = i2c_address;
  TinyWireM.begin(); // Initialize I2C for ATtiny85 (TinyWireM)

  // Test connection to the DAC
  TinyWireM.beginTransmission(_i2c_address);
  return (TinyWireM.endTransmission() == 0);
}

/**************************************************************************/
/*!
    @brief  Sets the output voltage to a fraction of source vref.  (Value
            can be 0..4095)
    @param[in]  output
                The 12-bit value representing the relationship between
                the DAC's input voltage and its output voltage.
    @param[in]  writeEEPROM
                If this value is true, 'output' will also be written
                to the MCP4725's internal non-volatile memory, meaning
                that the DAC will retain the current voltage output
                after power-down or reset.
    @returns True if able to write the value over I2C
*/
/**************************************************************************/
bool MCP4725_tiny::setVoltage(uint16_t output, bool writeEEPROM) {
  uint8_t packet[3];

  if (writeEEPROM) {
    packet[0] = MCP4725_CMD_WRITEDACEEPROM;
  } else {
    packet[0] = MCP4725_CMD_WRITEDAC;
  }
  packet[1] = output / 16;        // Upper data bits (D11.D10.D9.D8.D7.D6.D5.D4)
  packet[2] = (output % 16) << 4; // Lower data bits (D3.D2.D1.D0.x.x.x.x)

  TinyWireM.beginTransmission(_i2c_address);
  TinyWireM.write(packet, 3);
  return (TinyWireM.endTransmission() == 0);
}
