#ifndef __SENSOR_H
#define __SENSOR_H

#include <TList.h>

struct SensorReading
{
  enum TYPE { NONE, TEMPERATURE, HUMIDITY, VOLTAGE } ;
  
  uint8_t type = NONE;
  float value; = 0;

  uint32_t Encode(void)
  {
    //encoder fxn -- must use converse in TTN decoder
    //format (lsb) [0][1:2] = [type][(int16_t)(value * 100.)]
    encodedBytes[0] = type;

    //bytes  are reading times 100, which covers values from -327.68 <= value <= 327.67 (might need to be creative for pressure...)
    int16_t value_int = value * 100.0;
    memcpy (&encodedBytes[1], value_int, 2);
  }
};

TList<SensorReading> readingList;

TArray<SensorReading> readingArray();

#endif
