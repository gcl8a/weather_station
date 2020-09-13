
//#define Serial SerialUSB

#include <sensor.h>
#include <sensor_weather.h>
#include "comm.h"

/*
 * BME280
 */
#include<BME280.h>

#define BME280_I2C_ADDRESS 0x77 //CHECK CHECK CHECK!!!
BME280 bme280(BME280_I2C_ADDRESS);

void setup() 
{
  Serial.begin(115200);
  while (!Serial) ; // Wait for serial port to be available
  if (!manager.init())
    Serial.println("Init failed");

  manager.setRetries(0); //we want an ACK, but we're testing reliability, so skip re-sending
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
  float frequency = 921.2;
  driver.setFrequency(frequency);

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  driver.setTxPower(23, false);

  //Initialize the BME280
  bme280.Init();

  //Here's where to set options, if you so choose...
  //Probably want serious oversampling
  bme280.writeRegister(BME280_CTRL_MEAS_REG, 0x00); //first, ensure sleep mode
  bme280.writeRegister(BME280_CTRL_HUMIDITY_REG, 0x03); //4x oversampling for humidity
  bme280.writeRegister(BME280_CTRL_MEAS_REG, 0x70); //4x oversampling for temperature; 8x pressure; sleep

  /*
   * SD initialization.
   */
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(CS_SD)) 
  {
    Serial.println("card failed, or not present.");
    while(1) {} //die in a sad, infinite loop
  }
  Serial.println("card initialized.");

  filename = CreateNewFile();

  Serial.print("Writing to file: ");
  Serial.println(filename);

  Serial.println("/setup()");
}

#define READ_INTERVAL 15000

void loop()
{
  static uint32_t lastRead = 0;
  uint32_t currTime = millis();
  if(currTime - lastRead > READ_INTERVAL)
  {
    BME280Reading reading = bme280.TakeReading();

    SensorReading temperature(BME280_T, reading.temperature);
    SensorReading humidity(BME280_H, reading.humidity);
    SensorReading pressure(BME280_P, reading.pressure);

    SendReading(BASE_NODE_ADDRESS, temperature);
    delay(3000); //we're sending "reliable" packets, so we need to wait for the responses -- this will have to go
    SendReading(BASE_NODE_ADDRESS, humidity);
    delay(3000);
    SendReading(BASE_NODE_ADDRESS, pressure);

    lastRead += READ_INTERVAL;
  }
}
