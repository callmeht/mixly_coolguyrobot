#if 0
version:V1.0 
#endif

#ifndef CoolGuyRobot_h
#define CoolGuyRobot_h
#endif


/*里增加宏开关 为了让编译固件库的时候串口不冲突
  屏蔽了 Scratch固件库就能编译，发送出正式版本的时候需要取消屏蔽，不然wifi的云内存不能使用
*/
#define _CoolGuyModule_iCloudMemory_BuildENABLE_
#ifndef _CoolGuyModule_iCloudMemory_BuildENABLE_
#pragma message("Not define _CoolGuyModule_iCloudMemory_BuildENABLE_ Please check command Line -> CoolGuyRobot.h 13")
#endif


#include <Arduino.h>
#include "OneWire.h"

#include "iic.h"
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
#define USE_GLOBAL_Brightness

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
				static void OLED_Print(unsigned char,unsigned char,String);
				static void OLED_Print(unsigned char,unsigned char,float);
				
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
		static void Initial();
		static void Set_Time(int Year, int Month, int Date, int Hour, int Minutes, int Seconds);
		static uint16_t Read_Time(int dat);
	private:
		static unsigned char RtcTime[7];


};

#ifdef _CoolGuyModule_iCloudMemory_BuildENABLE_
//*************************************WiFi******************************
class CoolGuyModule_iCloudMemory
{
	public:
		CoolGuyModule_iCloudMemory();
		String RevBuf[21];
		void Serial_Init();
		 String iCloud_Read_String(String MACaddr,int addr);
		 float iCloud_Read_Float(String MACaddr,int addr);
		void iCloud_Write(int addr,String data);
		 void iCloud_Write(int addr,float data);
	private:
};
#endif 


//*******************************************************

class CoolGuyModule_ElectroniccompassandThreeAxis
{
public:
	static void Initial();
	static int XYZandHeading_display(uint8_t ZXY);
	static double XYZandHeading_display_H();
private:
	static unsigned char xyz[7];

};


class CoolGuyModule_WS2812
{
public:
	CoolGuyModule_WS2812(uint16_t num_led);
	~CoolGuyModule_WS2812();

#ifndef ARDUINO
	void SetOutput(const volatile uint8_t* port, volatile uint8_t* reg, uint8_t pin);
#else
	void SetOutput(uint8_t pin);
#endif


	uint32_t GetRGB();
	uint8_t  GetR();
	uint8_t  GetG();
	uint8_t  GetB();
	uint8_t  GetH(uint16_t index);
	uint8_t  GetS(uint16_t index);
	uint8_t  GetV(uint16_t index);
	void SetRGB(uint8_t _Brightness, uint32_t rgb);
	void SetRGB(uint8_t _Brightness, uint8_t r, uint8_t g, uint8_t b);
#ifdef USE_GLOBAL_Brightness
	
	void SetBrightness(uint8_t _Brightness)
	{
		Brightness = _Brightness;
	}
	uint8_t GetBrightness()
	{
		return Brightness;
	}
#endif


	void Sync();

#ifdef RGB_ORDER_ON_RUNTIME
	void setColorOrderRGB();
	void setColorOrderGRB();
	void setColorOrderBRG();
#endif

private:
	uint16_t count_led;
	uint8_t *pixels;
#ifdef USE_GLOBAL_Brightness
	uint8_t Brightness;
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



