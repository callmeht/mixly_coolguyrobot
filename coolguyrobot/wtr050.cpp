#include "wtr050.h"
#define WTR050_RECORD_START 0x01
#define WTR050_RECORD_STOP  0x02
#define WTR050_PLAY         0x03
#define NONE				0xff

wtr050::wtr050(int pin)
{
	this->pin = pin;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
}

void wtr050::send_byte(uint8_t dat)
{
	uint8_t i;
	
	digitalWrite(pin, LOW);
	delayMicroseconds(104);
	for(i = 0; i < 8; i++)
	{
		if(dat & 0x01)
			digitalWrite(pin, HIGH);
		else
			digitalWrite(pin, LOW);
		delayMicroseconds(104);
		dat >>= 1;
	}
	digitalWrite(pin, HIGH);
	delayMicroseconds(104);
}

void wtr050::record_start(void)
{
	int i;
	for(i = 0; i < 3; i++)
	{
		send_byte(WTR050_RECORD_START);
		delay(10);
	}
}

void wtr050::record_stop(void)
{
	int i;
	for(i = 0; i < 3; i++)
	{
		send_byte(WTR050_RECORD_STOP);
		delay(10);
	}
}

void wtr050::play(void)
{
	int i;
	for(i = 0; i < 3; i++)
	{
		send_byte(WTR050_PLAY);
		delay(10);
	}
}