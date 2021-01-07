//
//    FILE: MCP4725_wave_generator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo function generators
//    DATE: 2021-01-07
//     URL: https://github.com/RobTillaart/FunctionGenerator
//
//  depending on the platform, the range of "smooth" sinus is limited.
//  other signals are less difficult so have a slightly larger range.
//
//  PLATFORM     RANGE          Points/sec    Points/period
//  UNO          to be tested
//  ESP32        to be tested
//

#include "MCP4725.h"
#include "Wire.h"

uint16_t     freq = 100;
uint32_t   period = 0;
uint32_t   halvePeriod = 0;
float      amplitudo1 = 0;
float      amplitudo2 = 0;

// q = square
// s = sinus
// w = sawtooth
// t = stair
// r = random
char mode = 'q';

MCP4725 MCP(0x63);
uint16_t count;
uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);

  Wire.begin();
  MCP.begin();
  Wire.setClock(800000);

  MCP.setValue(0);
  if (!MCP.isConnected())
  {
    Serial.println("err");
    while (1);
  }
  period = 1e6 / freq;
  halvePeriod = period / 2;

  while (1)
  {
    uint32_t now = micros();

    // show # updates per 0.1 second
    // count++;

    if (now - lastTime > 100000)
    {
      lastTime = now;
      //      Serial.println(count);
      //      count = 0;
      if (Serial.available())
      {
        int c = Serial.read();
        switch (c)
        {
          case '+':
            freq++;
            break;
          case '-':
            freq--;
            break;
          case '*':
            freq *= 10;
            break;
          case '/':
            freq /= 10;
            break;
          case '0' ... '9':
            freq *= 10;
            freq += (c - '0');
            break;
          case 'c':
            freq = 0;
            break;
          case 'A':
            break;
          case 'a':
            break;
          case 'q':
          case 's':
          case 'w':
          case 't':
          case 'r':
          case 'z':
          case 'm':
          case 'h':
            mode = c;
            break;
          default:
            break;
        }
        period = 1e6 / freq;
        halvePeriod = period / 2;
        amplitudo1   = 4095.0 / period;
        amplitudo2   = 4095.0 / halvePeriod;
        Serial.print(freq);
              Serial.print('\t');
              Serial.print(period);
              Serial.print('\t');
              Serial.print(halvePeriod);
        Serial.println();
      }
    }

    uint32_t t = now % period;

    switch (mode)
    {
      case 'q':
        if (t < halvePeriod ) MCP.setValue(4095);
        else MCP.setValue(0);
        break;
      case 'w':
        MCP.setValue(t * amplitudo1 );
        break;
      case 't':
        if (t < halvePeriod) MCP.setValue(t * amplitudo2 );
        else MCP.setValue( (period - t) * amplitudo2 );
        break;
      case 'r':
        MCP.setValue(random(4096));
        break;
      case 'z':  // zero
        MCP.setValue(0);
        break;
      case 'h':  // high
        MCP.setValue(4095);
        break;
      case 'm':  // mid
        MCP.setValue(2047);
        break;
      default:
      case 's':
        MCP.setValue(0);
        break;
    }
  }
}


void loop()
{
}

// END OF FILE
