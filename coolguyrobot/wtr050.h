#ifndef __WTR050_H_
#define __WTR050_H_

#include <Arduino.h>

class wtr050
{
public:
	wtr050(int pin);
	 void record_start(void);
	 void record_stop(void);
	 void play(void);
	 void wtr050Init(int pin);
private:
	 int pin;
 	 void send_byte(uint8_t dat);
};
#endif