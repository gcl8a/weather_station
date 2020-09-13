#ifndef __COMM_H
#define __COMM_H

#include <RH_RF95.h>
#include <RHDatagram.h>

const float RFM_FREQ = 915.0;
//#define SerialUSB Serial

/////////////RFM69HCW radio
#define NETWORKID     155   // Must be the same for all nodes (0 to 255)
#define MYNODEID      1   // My node ID (0 to 255)
#define BASE_NODE     0   // My node ID (0 to 255)
#define FREQUENCY     RF69_915MHZ

// Create a library object for our RFM69HCW module:
//RFM69 radio(8, 3, false, digitalPinToInterrupt(3));
//RH_RF69 radio;//(10, 8, false, digitalPinToInterrupt(8));
RH_RF95 radio(12, 6);
RHDatagram manager(radio, MYNODEID);

int InitRadio(void)
{
  SerialUSB.println(F("Initializing radio..."));

  // Initialize the RFM69HCW:
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  
  radio.init();//ialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.setFrequency(RFM_FREQ);
//  radio.setHighPower(); //needed for RFM69HCW

  SerialUSB.println("Success");

  return 1;
}

int WriteRadio(String str)
{
  //SerialUSB.print(str);

  int length = str.length();
  char sendBuffer[62];
  str.toCharArray(sendBuffer, 62); //we can send up to 255 characters; need to check if str is too long

//  radio.setHeaderTo(BASE_NODE);
//  radio.sendTo(sendBuffer, length > 62 ? 62 : length, BASE_NODE);
//  radio.receiveDone(); //put us back into receive mode

  //return to receive mode???

  return 1;
}

String radioString;
//bool CheckRadio(void)
//{
//  bool retVal = false;
//  if(radio.receiveDone())
//  {
//    retVal = true;
//    //uint8_t recLength = radio.DATALEN;
//
//    radioString = "";
//    for (byte i = 0; i < radio.DATALEN; i++)
//    {
//      if((char)radio.DATA[i] != '\n' && (char)radio.DATA[i] != '\r')
//        radioString += (char)radio.DATA[i];
//    }
//
//    if (radio.ACKRequested())
//    {
//      radio.sendACK();
//    }
//  }
//
//  return retVal;
//}

void Report(const String& str)
{
  SerialUSB.print(millis());
  SerialUSB.print('\t');
  SerialUSB.println(str);
  //WriteRadio(str);
}

#endif
