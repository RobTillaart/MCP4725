# MCP4725

Arduino library for 12 bit I2C DAC - MCP4725 

## Description

The MCP4725 is an I2C 12 bit Digital to Analog Converter. It is possible to have
up to 8 MCP4725 on one bus. 

* **MCP4725(deviceAddress)** Constructor, needs I2C address
* **begin(dataPin, clockPin)** for ESP32
* **begin()** for UNO and other boards with hard wired I2C pins.

* **setValue(value)** value = 0 .. 4095  // uses writeFastMode
* **getValue()** returns last value from cache, this is much faster than readDAC()
which gives the real value from the MCP4725. A difference can be caused by power
outage etc.

* **writeDAC(value, const bool EEPROM = false)** Writes to DAC and if bool is set to true 
also to the internal EEPROM for staretup / reset behavior. Check datasheet for detail behavior.
* **RDY()** depreciated, replaced by **ready()**
* **ready()** returns true if a new value can be written to the MCP4725.
* **readDAC()** reads the current value set in the MCP4725.
* **readEEPROM()** reads the current value in the EEPROM of the MCP4725.

## Experimental
Check datasheet for these functions.

* **writePowerDownMode(PDM, const bool EEPROM = false)**
* **readPowerDownModeEEPROM()**
* **readPowerDownModeDAC()**
* **powerOnReset()**
* **powerOnWakeUp()**

## Address Notes
The address of the MCP4725 in the demo sketches is set to 0x62 as that 
was the address of the sensor I had during writing. 
According to the datasheet the address has the following bit pattern: 

address  011000FFU   (so 0x6?)

         F = Factory set bit
         U = User configurable bit

This means you can have at most 8 MCP4725 in one I2C bus (without multiplexing).
You have to specify the factory bits in your order, but not all shops might
provide all versions of the MCP4725.
```
MCP4725A0T-E/CH:  0110 000U   0x60 - 0x61
MCP4725A1T-E/CH:  0110 001U   0x62 - 0x63
MCP4725A2T-E/CH:  0110 010U   0x64 - 0x65
MCP4725A3T-E/CH:  0110 011U   0x66 - 0x67
```
If one need more DAC's one might have a look at the MCP4728
It has 4 channels per chip (no experience /library yet)

## Operation

See examples
