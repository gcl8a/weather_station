#define Serial SerialUSB

#include <Wire.h>

#define EUI64_CHIP_ADDRESS 0x50
#define EUI64_MAC_ADDRESS 0xF8
#define EUI64_MAC_LENGTH 8  

void setup() 
{
  Serial.begin(115200);
  while(!Serial) {}
  Serial.println("Hi");
  
  Wire.begin();
  Wire.beginTransmission(EUI64_CHIP_ADDRESS);
  Wire.write(EUI64_MAC_ADDRESS);
  Wire.endTransmission();
  Wire.requestFrom(EUI64_CHIP_ADDRESS, EUI64_MAC_LENGTH);

  // Format needs to be little endian (LSB...MSB)
  while (Wire.available())
  {
    Serial.print( Wire.read(), HEX );
    Serial.print(' ');
  }

  Serial.print('\n');
}

void loop() 
{

}
