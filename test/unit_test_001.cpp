//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the MCP4725
//          https://github.com/RobTillaart/MCP4725
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>

#define assertEqualFloat(arg1, arg2, arg3)  assertOp("assertEqualFloat", "expected", fabs(arg1 - arg2), compareLessOrEqual, "<=", "actual", arg3)
#define assertEqualINF(arg)  assertOp("assertEqualINF", "expected", INFINITY, compareEqual, "==", "actual", arg)
#define assertEqualNAN(arg)  assertOp("assertEqualNAN", "expected", true, compareEqual, "==", "actual", isnan(arg))


#include "Arduino.h"
#include "MCP4725.h"



unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", MCP4725_VERSION);
  MCP4725 MCP(0x62);
  
  assertTrue(MCP.begin());
  assertTrue(MCP.isConnected());
  assertEqual(MCP4725_MAXVALUE, 4095);
}

unittest(test_get_setValue)
{
  MCP4725 MCP(0x62);
  
  assertTrue(MCP.begin());
  assertTrue(MCP.isConnected());
  uint16_t last = MCP.getValue();
  assertEqual(0, last);
  assertEqual(0, MCP.setValue(last));
  assertEqual(MCP4725_VALUE_ERROR, MCP.setValue(65535);
  assertEqual(MCP4725_VALUE_ERROR, MCP.setValue(4096);
}

unittest_main()

// --------
