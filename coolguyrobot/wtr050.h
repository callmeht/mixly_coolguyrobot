#ifndef __WTR050_H_
#define __WTR050_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

class wtr050
{
public:
	wtr050(int pin);
	void record_start(void);
	void record_stop(void);
	void play(void);
};
#endif