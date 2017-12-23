#if 0
version:V1.0 
#endif

#ifndef CoolGuyRobot_h
#define CoolGuyRobot_h

#include <Arduino.h>
#include "OneWire.h"

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




//********************????************************
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
			static float Read_PM2_5(int pin);
			static float Read_UltrasonicVal(int pin);
			
	private:
};

//读温度
/*应用了OneWire库*/
class CoolGuyModule_Temperature_Read: public OneWire
{
	public:
		CoolGuyModule_Temperature_Read(int pin);
	    float readT();

};//读温度 结束

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






#endif



