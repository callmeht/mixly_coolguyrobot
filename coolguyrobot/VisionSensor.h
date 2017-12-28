#ifndef VisionSensor_h
#define VisionSensor_h 

#include <inttypes.h>
#include <Arduino.h>

class VisionSensor
{
  public:
   VisionSensor(HardwareSerial &uart, uint32_t baud = 115200);
   void begin(void);
   boolean valid(void);
   void search(void);
   boolean detected(void);
   uint8_t getX(void);
   uint8_t getY(void);
   uint8_t getWidth(void);
   uint8_t getHeight(void);
   
  private:
   HardwareSerial *m_puart;
   uint8_t dataDetected;
   uint8_t dataX,dataY,dataWidth,dataHeight;
   uint8_t comdata[100], data_p = 0; 
   uint32_t _baud;
   boolean _valid;
};

#endif