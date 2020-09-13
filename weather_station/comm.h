#include <RHReliableDatagram.h>
#include <RH_RF95.h>

#include <SD.h>

const int CS_SD = 10;  //chip select for the SD card
String filename;      //for managing filenames
File dataFile;        //dataFile manager

#define BASE_NODE_ADDRESS 2
#define THIS_NODE_ADDRESS 1

// Singleton instance of the radio driver
//RH_RF95 driver(12, 6);
RH_RF95 driver(8, 3);

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, THIS_NODE_ADDRESS);

bool SendReading(uint8_t destination, const SensorReading& reading)
{
  Serial.print("Sending...");
  Serial.print(reading.TransferString());

  String transferString = reading.TransferString();
  const char* transferBuffer = transferString.c_str();
  uint8_t strLen = sizeof(transferBuffer);

  // Send a message to manager_server
  if (manager.sendtoWait((uint8_t*) transferBuffer, strLen, BASE_NODE_ADDRESS))
  {
    
  }
  
  else
    Serial.println("sendtoWait failed");


//  //write to SD card
//  dataFile = SD.open(filename, FILE_WRITE);
//
//  // if the file is available, write to it:
//  if (dataFile) 
//  {
//    dataFile.print(transferString + String("\r\n"));
//    dataFile.close();
//  }
//  
//  else
//  {
//    Serial.println("Error opening file!");
//    while(1) {} //die in a sad, infinite loop
//  }

  Serial.println(".../SendReading()");

  return true;
}


String CreateNewFile(void) //creates a new file of the form therm_##.csv; auto-increments so old files aren't clobbered
{
  Serial.println("Creating new file.");

  int fileCount = 0;
  bool fileSuccess = false;

  char filename[13]; //use 8.3 format 
  while(!fileSuccess)
  {
    sprintf(filename, "therm%03i.csv", fileCount);
    if(SD.exists(filename))
    {
      fileCount++;
    }
    
    else
    {
      fileSuccess = 1;
    }
  }

  return String(filename);
}
