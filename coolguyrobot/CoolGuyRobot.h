#if 0
version:V1.0 
#endif

#ifndef CoolGuyRobot_h
#define CoolGuyRobot_h
#endif

#include <Arduino.h>
#include "OneWire.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#ifndef F_CPU
#define  F_CPU 16000000UL
#endif
#include <util/delay.h>
#include <stdint.h>
//#include <avr/io.h>  底层IO口寄存器操作库

#define RIGHT 0x1
#define LEFT  0x0

#define R 0x1
#define L  0x0

/***********************IO口操作接口*************************/
#define SIGNSET_INPUT		*IO_Reg &= IOBitL
#define SIGNSET_OUTPUT  *IO_Reg |= IOBitH

#define READ_SIGN  			(*IO_In&IOBitH) 			

#define SETSIGN_HIGH  	*IO_Out |= IOBitH	
#define SETSIGN_LOW   	*IO_Out &= IOBitL

/***********************通讯时序时间 单位us*************************/
#define READ_IRSIGN  	(*IRIO_In&IRIOBitH) 
#define Communication_Wait_A	10
#define Communication_Wait_B	10
#define Communication_Wait_C	10-0
#define Communication_Wait_D	10
#define Communication_Wait_F	0


/*********************RTC**************************/
//const int RTC_DS1307_ADD 0x68;
#define RTC_DS1307_ADD 0x68

/*********************ElectroniccompassandThreeAxis**************************/
//const int ElectroniccompassandThreeAxis_adress 0x1E;
#define ElectroniccompassandThreeAxis_adress 0x1E

/*********************RGB**************************/
#define USE_GLOBAL_BRIGHTNESS

#ifdef RGB_ORDER_ON_RUNTIME
#define OFFSET_R(r) r+offsetRed
#define OFFSET_G(g) g+offsetGreen
#define OFFSET_B(b) b+offsetBlue
#else
// CHANGE YOUR STATIC RGB ORDER HERE
#define OFFSET_R(r) r+1
#define OFFSET_G(g) g
#define OFFSET_B(b) b+2
#endif

const byte dim_curve[] =
{
	0, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6,
	6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8,
	8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11,
	11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15,
	15, 15, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20,
	20, 20, 21, 21, 22, 22, 22, 23, 23, 24, 24, 25, 25, 25, 26, 26,
	27, 27, 28, 28, 29, 29, 30, 30, 31, 32, 32, 33, 33, 34, 35, 35,
	36, 36, 37, 38, 38, 39, 40, 40, 41, 42, 43, 43, 44, 45, 46, 47,
	48, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
	63, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 76, 78, 79, 81, 82,
	83, 85, 86, 88, 90, 91, 93, 94, 96, 98, 99, 101, 103, 105, 107, 109,
	110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
	146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
	193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};

#define w_zeropulse   350
#define w_onepulse    900
#define w_totalperiod 1250

		// Fixed cycles used by the inner loop
#define w_fixedlow    3
#define w_fixedhigh   6
#define w_fixedtotal  10

		// Insert NOPs to match the timing, if possible
#define w_zerocycles    (((F_CPU/1000)*w_zeropulse          )/1000000)
#define w_onecycles     (((F_CPU/1000)*w_onepulse    +500000)/1000000)
#define w_totalcycles   (((F_CPU/1000)*w_totalperiod +500000)/1000000)

		// w1 - nops between rising edge and falling edge - low
#define w1 (w_zerocycles-w_fixedlow)
		// w2   nops between fe low and fe high
#define w2 (w_onecycles-w_fixedhigh-w1)
		// w3   nops to complete loop
#define w3 (w_totalcycles-w_fixedtotal-w1-w2)

#if w1>0
#define w1_nops w1
#else
#define w1_nops  0
#endif

		// The only critical timing parameter is the minimum pulse length of the "0"
		// Warn or throw error if this timing can not be met with current F_CPU settings.
#define w_lowtime ((w1_nops+w_fixedlow)*1000000)/(F_CPU/1000)
#if w_lowtime>550
#error "Light_CoolGuyModule_WS2812: Sorry, the clock speed is too low. Did you set F_CPU correctly?"
#elif w_lowtime>450
		#warning "Light_CoolGuyModule_WS2812: The timing is critical and may only work on CoolGuyModule_WS2812B, not on CoolGuyModule_WS2812(S)."
			#warning "Please consider a higher clockspeed, if possible"
#endif

#if w2>0
#define w2_nops w2
#else
#define w2_nops  0
#endif

#if w3>0
#define w3_nops w3
#else
#define w3_nops  0
#endif

#define w_nop1  "nop      \n\t"
#define w_nop2  "rjmp .+0 \n\t"
#define w_nop4  w_nop2 w_nop2
#define w_nop8  w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8
//********************????************************

#define bin2bcd(val)   val + 6 * (val / 10) 
#define bcd2bin(val)   val - 6 * (val >> 4)

class CoolGuyModule_IR
{ 
	public:
		static void IR_Init(int pin);
		static int IR_KeyValueCmp(int key,int channel) ;
	  static unsigned char IRCode;
	  static unsigned char  IRData[2] ;	
	  static uint8_t IRIOBitH;
			
	private:
		static void NECIR_Scan();
	  	static void Remote_Task();
		static void IR_ClearFlay();
		static void IR_Scan();
		static int IRPin;
	  static unsigned char Errflay ;
	  static unsigned char IR_ID ;
	  static unsigned char Remote_Type ;	//????  0:????  1:????   ???????
	  
};





//********************????**********************

class CoolGuyModule_WalkLine
{
		public:
			static void WalkLine_Init(int pin);
			static void LeftMotorSpeed(int s);
			static void RightMotorSpeed(int s);
			static void SetComparisonValue(int ColorComparison1,int ColorComparison2,int ColorComparison3,int ColorComparison4,int ColorComparison5);
			static void RunWalkLine(int LineNum,int MaxSpeed,float EndTime);
			static void RunWalkLine_Timer(int MaxSpeed,float Cnt);
		  static void RunWalkLine_Turn(int Direction,int MaxSpeed,int LineNum);
		  
		  static int 	WalkReadValue();
		  static float GetUltrasonicVal();
		  
		  static int GrayValue_ReadOne(int i);
		  
		 	static void ReadSensor_Gray();
		  
		    static int ColorComparison_Buf1;
			static int ColorComparison_Buf2;
			static int ColorComparison_Buf3;
			static int ColorComparison_Buf4;
			static int ColorComparison_Buf5;
			
			static uint16_t DATA_BUF[6];
			
			static uint8_t IOBitH;
			static uint8_t IOBitL;
		private:
			static void WalkLineFunction(int MaxSpeed);
			static void WalkLineMotorControl(int MaxSpeed);

			static int 	ColorPin1Value;
			static int 	ColorPin2Value;
			static int 	ColorPin3Value;
			static int 	ColorPin4Value;
			static int 	ColorPin5Value;
};


//********************传感器模块**********************
class CoolGuyModule_Sensor
{
	public:
			static float Read_Temperature(int pin);
			static float Read_PM2_5(int pin);
			static float Read_UltrasonicVal(int pin);
			
	private:
};


//********************OLED模块**********************
class CoolGuyModule_OLED 
{
	public:
			CoolGuyModule_OLED();
				static void oleddelay(unsigned int z);
				static void OLED_WrDat(unsigned char IIC_Data);
				static void OLED_WrCmd(unsigned char IIC_Command);
			
				static void OLED_CLS();
				static void OLED_Fill(unsigned char bmp_dat);
				static void OLED_Set_Pos(unsigned char x, unsigned char y);
				static void OLED_P8x16Ch(unsigned char x,unsigned char y,unsigned char N);
				static void OLED_DrawString(unsigned char,unsigned char,String);
				static void OLED_DrawValue(unsigned char,unsigned char,float);
				
	private:


};

class CoolGuyModule_StringCmp
{
	public:
		static void SetString(String str);
		static bool Compare_StringEqual(String str);
		static bool Compare_IncludeString(String str);
	private:
		static String string;


};

/*读温度传感器*/
/*应用了OneWire库*/
class CoolGuyModule_Temperature_Read: public OneWire
{
	public:
		CoolGuyModule_Temperature_Read(int pin);
	    float readT();

};/*读温度传感器 结束*/

class CoolGuyModule_RTC
{
	public:
		static void initial();
		static void Set_Time(int Year, int Month, int Date, int Hour, int Minutes, int Seconds);
		static uint8_t Read_Time_Second();
		static uint8_t Read_Time_Minute();
		static uint8_t Read_Time_Hour();
		static uint8_t Read_Time_Date();
		static uint8_t Read_Time_Month();
		static uint16_t Read_Time_Year();
	private:
		static unsigned char rtctime[7];


};

class CoolGuyModule_ElectroniccompassandThreeAxis
{
public:
	static void initial();
	static int XYZandHeading_display_X();
	static int XYZandHeading_display_Y();
	static int XYZandHeading_display_Z();
	static double XYZandHeading_display_H();
private:
	static unsigned char xyz[7];

};


/*class CoolGuyModule_WS2812
{
public:
	CoolGuyModule_WS2812(uint16_t num_led);
	~CoolGuyModule_WS2812();

#ifndef ARDUINO
	void setOutput(const volatile uint8_t* port, volatile uint8_t* reg, uint8_t pin);
#else
	void setOutput(uint8_t pin);
#endif


	uint32_t getRGB(uint16_t index);
	uint8_t  getR(uint16_t index);
	uint8_t  getG(uint16_t index);
	uint8_t  getB(uint16_t index);
	uint8_t  getH(uint16_t index);
	uint8_t  getS(uint16_t index);
	uint8_t  getV(uint16_t index);
	void setRGB(uint16_t index, uint32_t rgb);
	void setRGB(uint16_t index, uint8_t r, uint8_t g, uint8_t b);
	void setHSV(uint16_t index, uint8_t hue, uint8_t sat, uint8_t val);  // hue between 0 and 191
#ifdef USE_GLOBAL_BRIGHTNESS
	void setBrightnessLinear(uint8_t _brightness)
	{
		brightness = dim_curve[_brightness];
	}
	void setBrightness(uint8_t _brightness)
	{
		brightness = _brightness;
	}
	uint8_t getBrightness()
	{
		return brightness;
	}
#endif


	void sync();

#ifdef RGB_ORDER_ON_RUNTIME
	void setColorOrderRGB();
	void setColorOrderGRB();
	void setColorOrderBRG();
#endif

private:
	uint16_t count_led;
	uint8_t *pixels;
#ifdef USE_GLOBAL_BRIGHTNESS
	uint8_t brightness;
#endif
	void CoolGuyModule_WS2812_sendarray_mask(uint8_t *array, uint16_t length, uint8_t pinmask, uint8_t *port, uint8_t *portreg);

	const volatile uint8_t *CoolGuyModule_WS2812_port;
	volatile uint8_t *CoolGuyModule_WS2812_port_reg;
	uint8_t pinMask;

#ifdef RGB_ORDER_ON_RUNTIME
	uint8_t offsetRed;
	uint8_t offsetGreen;
	uint8_t offsetBlue;
#endif
};


#endif
*/


