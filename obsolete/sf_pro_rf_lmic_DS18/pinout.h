#include <lmic.h>
#include <hal/hal.h>

#ifdef VINGAARD01
  #define USE_SF_PRO_RF

  // This EUI must be in little-endian format. 
  // For TTN issued EUIs the last bytes should be 0xD5, 0xB3, 0x70.
  static const u1_t PROGMEM APPEUI[8] = { 0x6E, 0x8B, 0x01, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };
  void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}
  
  // This should also be in little endian format.
  static const u1_t PROGMEM DEVEUI[8] = { 0x32, 0x84, 0xC0, 0x51, 0x83, 0xDF, 0xF4, 0x00 };
  void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}
  
  // This key should be in big endian format (or, since it is not really a
  // number but a block of memory, endianness does not really apply).
  static const u1_t PROGMEM APPKEY[16] = { 0x1F, 0x3A, 0xFE, 0x27, 0xD8, 0xD7, 0x2D, 0xBE, 0x2B, 0x33, 0xA8, 0xD6, 0x7E, 0xC1, 0x0B, 0x37 };
  void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

#endif

#ifdef USE_SF_PRO_RF
  #define Serial SerialUSB
  
  // Pin mapping for SparkFun Pro LoRa
  const lmic_pinmap lmic_pins = {
      .nss = 12,
      .rxtx = LMIC_UNUSED_PIN,
      .rst = 7,
      .dio = {6, 10, LMIC_UNUSED_PIN},
      .rxtx_rx_active = 0,
      .rssi_cal = 8,              // LBT cal for the Adafruit Feather M0 LoRa, in dB
      .spi_freq = 8000000,
  };
  
  #define BATTERY_PIN A5
#endif



