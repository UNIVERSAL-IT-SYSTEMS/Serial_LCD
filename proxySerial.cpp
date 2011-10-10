//
// μLCD-32PT(SGC) 3.2” Serial LCD Display Module
// Arduino Library
//
// May 10, 2011 release 1 - initial release
// Jun 15, 2011 release 2 - features added and bugs fixed
// Jun 29, 2011 release 3 - setBackGroundColour added and SD card
// Jul 31, 2011 release 4 - stdint.h types for chipKIT compatibility
// Aug 04, 2011 release 5 - chipKIT compatibility with external proxySerial.h
// Aug 07, 2011 release 6 - playing sounds - up to 250 mA!
// Sep 18, 2011 release 7 - dialog window with up to 3 buttons
// Sep 23, 2011 release 8 - ms monitoring to avoid RX TX collapse
// Oct 10, 2011 release 9 - Stream.h class based i2cSerial library
//
// CC = BY NC SA
// http://sites.google.com/site/vilorei/
//
#include "WProgram.h"
//#include "Arduino.h"

#include "proxySerial.h"

// I2C case
#if defined(__i2cSerialPort__) 
#include "Wire.h"
#include "i2cSerial.h"
ProxySerial::ProxySerial(i2cSerial * port0) {
  _proxyPort = port0; 
}

// Arduino Case
#elif defined(__AVR__) 
#include "NewSoftSerial.h"
ProxySerial::ProxySerial(NewSoftSerial * port0) {
  _proxyPort = port0; 
}

// chipKIT Case
#elif defined(__PIC32MX__) 
ProxySerial::ProxySerial(HardwareSerial * port0) {
  _proxyPort = port0; 
}

#else
#error Non defined board
#endif


void ProxySerial::_checkSpeed() {  
//    while(!(millis()-_millis > 3));    // time in ms
  while((millis()-_millis < 3));    // time in ms, the same !> = <
  _millis=millis();
}

void ProxySerial::begin(uint16_t b) {
  _checkSpeed();  
  _proxyPort->begin(b); 
}

void ProxySerial::print(int8_t i) { 
  _checkSpeed();  
  _proxyPort->print(i); 
}

void ProxySerial::print(uint8_t ui) { 
  _checkSpeed();  
  _proxyPort->print(ui); 
};

void ProxySerial::print(int16_t i) { 
  _checkSpeed();  
  _proxyPort->print(highByte(i)); 
  _proxyPort->print(lowByte(i)); 
};

void ProxySerial::print(uint16_t ui) { 
  _checkSpeed();  
  _proxyPort->print(highByte(ui)); 
  _proxyPort->print(lowByte(ui)); 
};

void ProxySerial::print(char c) { 
  _proxyPort->print((uint8_t)c); 
};
void ProxySerial::print(String s) { 
  for (uint8_t i=0; i<s.length(); i++)         {
//  _checkSpeed();  
    _proxyPort->print(s.charAt(i));
}
}

uint8_t ProxySerial::read() { 
  _checkSpeed();  
  return _proxyPort->read(); 
}
int8_t ProxySerial::available() { 
  _checkSpeed();  
  return _proxyPort->available(); 
}
void ProxySerial::flush() {  
  _checkSpeed();  
  _proxyPort->flush(); 
}








