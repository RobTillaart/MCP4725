//
//    FILE: mcp4725_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.5
// PURPOSE: test mcp4725 lib
//    DATE: 2013-11-24
//     URL: https://github.com/RobTillaart/MCP4725
//

#include "Wire.h"
#include "MCP4725.h"

MCP4725 MCP(0x62);  // 0x62 or 0x63

volatile int x;
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);

  Serial.print("MCP4725 test program: ");
  Serial.println(MCP4725_VERSION);

  MCP.begin();
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
}

void test1()
{
  Serial.print("\nValue:\t");
  Serial.println(MCP.getValue());
  Serial.println();

  for (int i = 100; i < 500; i += 100)
  {
    Serial.print("setValue(");
    Serial.print(i);
    Serial.print(")\n");
    MCP.setValue(i);
    Serial.print("Value:\t");
    Serial.println(MCP.getValue());
  }
  Serial.println();
}

void test2()
{
  Serial.println("\n\nMCP4725_II\n\n");

  for (int i = 100; i < 500; i += 100)
  {
    Serial.print("writeMCP(");
    Serial.print(i);
    Serial.print(")\n");
    MCP.writeMCP(i);
    Serial.print("MCPValue:\t");
    Serial.println(MCP.readMCP());
    Serial.print("EEValue:\t");
    Serial.println(MCP.readEEPROM());
  }
  Serial.println();

  for (int i = 100; i < 500; i += 100)
  {
    Serial.print("writeMCP(");
    Serial.print(i);
    Serial.print(", true)\n");
    MCP.writeMCP(i, true);
    Serial.print("MCPValue:\t");
    Serial.println(MCP.readMCP());
    Serial.print("EEValue:\t");
    Serial.println(MCP.readEEPROM());
  }
  Serial.println();

  Serial.println("writeMCP(200)");
  MCP.writeMCP(200);
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readMCP());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());
  Serial.println();
}

void test3()
{
  Serial.println("\n\nMCP4725_POWERDOWNMODE\n\n");

  for (int i = 0; i < 4; i++)
  {
    Serial.print("MCP.writePowerDownMode(");
    Serial.print(i);
    Serial.println(")");
    MCP.writePowerDownMode(i);
    Serial.print("EPR PDM Value:\t");
    Serial.println(MCP.readPowerDownModeEEPROM());
    Serial.println();
  }

  Serial.println("\n\nEXPERIMENTAL");
  Serial.println("MCP.writePowerDownMode(3)");
  MCP.writePowerDownMode(3);
  MCP.writeMCP(305);
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println("MCP.powerOnReset()");
  Serial.println("Before");
  Serial.print("MCP PDM Value:\t");
  Serial.println(MCP.readPowerDownModeMCP());
  Serial.print("EPR PDM Value:\t");
  Serial.println(MCP.readPowerDownModeEEPROM());
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readMCP());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());
  MCP.powerOnReset();
  Serial.println("After");
  Serial.print("MCP PDM Value:\t");
  Serial.println(MCP.readPowerDownModeMCP());
  Serial.print("EPR PDM Value:\t");
  Serial.println(MCP.readPowerDownModeEEPROM());
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readMCP());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println();
}

void test4()
{
  Serial.println("\n\nEXPERIMENTAL");
  Serial.println("MCP.writePowerDownMode(2)");
  MCP.writePowerDownMode(2);
  MCP.writeMCP(405);
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println("MCP.powerOnWakeUp()");
  Serial.println("Before");
  Serial.print("MCP PDM Value:\t");
  Serial.println(MCP.readPowerDownModeMCP());
  Serial.print("EPR PDM Value:\t");
  Serial.println(MCP.readPowerDownModeEEPROM());
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readMCP());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());

  MCP.powerOnWakeUp();
  Serial.println("after");
  Serial.print("MCP PDM Value:\t");
  Serial.println(MCP.readPowerDownModeMCP());
  Serial.print("EPR PDM Value:\t");
  Serial.println(MCP.readPowerDownModeEEPROM());
  Serial.print("MCPValue:\t");
  Serial.println(MCP.readMCP());
  Serial.print("EEValue:\t");
  Serial.println(MCP.readEEPROM());
  Serial.print("Value:\t");
  Serial.println(MCP.getValue());
  Serial.println();
}

void test5()
{
  Serial.println("\n\nPERFORMANCE");
  Serial.println();

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = MCP.getValue();
  }
  stop = micros();
  Serial.print("1000x MCP.getValue():\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    MCP.setValue(i);
  }
  stop = micros();
  Serial.print("1000x MCP.setValue(i):\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    MCP.setValue(1000);
  }
  stop = micros();
  Serial.print("1000x MCP.setValue(1000):\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = MCP.readMCP();
  }
  stop = micros();
  Serial.print("1000x MCP.readMCP():\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = MCP.writeMCP(i);
  }
  stop = micros();
  Serial.print("1000x MCP.writeMCP(i):\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = MCP.writeMCP(i, true);
  }
  stop = micros();
  Serial.print("10x   MCP.writeMCP(i, true):\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    x = MCP.ready();
  }
  stop = micros();
  Serial.print("1000x MCP.ready():\t\t");
  Serial.println(stop - start);

  while (!MCP.ready());
  MCP.writeMCP(0, true);
  start = micros();
  while (!MCP.ready());
  stop = micros();
  Serial.print("EEPROM write latency:\t\t");
  Serial.println(stop - start);
}

void test6()
{
  Serial.println("\n\nEXPERIMENTAL II");

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = MCP.readPowerDownModeMCP();
  }
  stop = micros();
  Serial.print("10x MCP.readPowerDownModeMCP():\t\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = MCP.readPowerDownModeEEPROM();
  }
  stop = micros();
  Serial.print("10x MCP.readPowerDownModeEEPROM():\t");
  Serial.println(stop - start);

  start = micros();
  for (int i = 0; i < 10; i++)
  {
    x = MCP.writePowerDownMode(i & 0x03);
  }
  stop = micros();
  Serial.print("10x MCP.writePowerDownMode(i):\t\t");
  Serial.println(stop - start);

  Serial.print("\nDone... (start triangle mode)");
}

void loop()
{
  for (uint16_t i = 0; i < 4096; i++)
  {
    MCP.setValue(i);
    delay(10);
  }
  for (uint16_t i = 0; i < 4096; i++)
  {
    MCP.setValue(4096 - i);
    delay(10);
  }
}

// -- END OF FILE --
