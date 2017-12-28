/* morpx.inc copyright */

#include <VisionSensor.h>


VisionSensor::VisionSensor(HardwareSerial &uart, uint32_t baud): m_puart(&uart)
{
	_baud = baud;
	_valid = false;
}

void VisionSensor::begin(void)
{
  m_puart->begin(_baud);
  while (m_puart->available() > 0)
  {
    m_puart->read();
  }
}

boolean VisionSensor::valid(void)
{
  return _valid;
}

void VisionSensor::search(void)
{
	//m_puart->print("tp0");
  while(m_puart->available() > 0)
  {
    uint8_t dataByte = m_puart->read();
    //m_puart->print("tp1");
	
    if (dataByte == 0xFE)
    { 
	 // m_puart->print("tp2");
      comdata[data_p] = dataByte;
	    uint8_t temp_p = data_p;
	    data_p = 0;
	  
      if (comdata[temp_p-1] == 0xFF)
      {
      	//m_puart->print("tp3");
		dataDetected = comdata[0];
        dataX = comdata[1];
        dataY = comdata[2];
        dataWidth = comdata[3];
        dataHeight = comdata[4];
        if (comdata[5] == 0xED)
        {
        	_valid = true;
        	//m_puart->print("tp4");
		}

      }
      else
      {
        _valid = false;
      }
    }
    else
    {
      comdata[data_p] = dataByte ;
      data_p++;
    }
  }
}

boolean VisionSensor::detected(void)
{
	if(dataDetected == 0x01 || dataDetected == 0x02 || dataDetected == 0x03 || dataDetected == 0x04 || dataDetected == 0x05 )
	//if(dataDetected == 0x05)
	{
		return true;
	}
	
	return false;
}

uint8_t VisionSensor::getX(void)
{
  return dataX;
}

uint8_t VisionSensor::getY(void)
{
  return dataY;
}

uint8_t VisionSensor::getWidth(void)
{
  return dataWidth;
}

uint8_t VisionSensor::getHeight(void)
{
  return dataHeight;
}

