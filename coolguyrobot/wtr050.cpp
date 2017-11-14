#include "wtr050.h"
#define WTR050_RECORD_START 0x01
#define WTR050_RECORD_STOP  0x02
#define WTR050_PLAY         0x03
#define NONE				0xff
SoftwareSerial* sw_serial;

wtr050::wtr050(int pin)
{
	int i;
	sw_serial = new SoftwareSerial(22, pin);
	sw_serial->begin(9600);
}

void wtr050::record_start(void)
{
	int i;
	for(i = 0; i < 3; i++)
	{
		sw_serial->write(WTR050_RECORD_START);
		delay(10);
	
	}
}

void wtr050::record_stop(void)
{
	int i;
	for(i = 0; i < 3; i++)
	{
		sw_serial->write(WTR050_RECORD_STOP);
		delay(10);
	}
}

void wtr050::play(void)
{
	int i;
	for(i = 0; i < 3; i++)
	{
		sw_serial->write(WTR050_PLAY);
		delay(10);
	}
}