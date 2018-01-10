#ifndef CoolGuy_h
#define CoolGuy_h

#include <Arduino.h>
#include <avr/io.h>  µ×²ãIO¿Ú¼Ä´æÆ÷²Ù×÷¿â

class CoolGuy_Led
{
	public:
			static void Set_Led(int pin, unsigned char num1, unsigned char num2 );//the second argument num1 means choose which led, the 
		//third argument num2 means the action,0x01 means light the led, 0x00 means lighting-off
	private:
};
class CoolGuy_IR
{
	public:
		    static unsigned int Read_IR_Val(int pin, unsigned char num);//the second argument num means choose which IR tube to read
	        //static void IR_Init(int pin);
	private:
}; 
/*class CoolGuy_DigitalShow
{
   public:
   			static void Set_DigitalNum(int pin, unsigned char num1, unsigned char num2);
	
   private:
	
};//Íü¼Ç¼Ó·ÖºÅ */ //this function is useless

class CoolGuy_Digital
{
	public:
			static void Set_Digital(int pin, double num);//there are two modes about the digital tube. This function can let you write a 
	private:      //double-type number, and the tube can display the number
	
};

class CoolGuy_Digital2
{
	public:
			static void Set_Digital2(int pin, unsigned char num1, unsigned char num2);//this mode is clock-mode. The argument num1 is the 
	private:// the number on the left of the colon, the argument num2 is the number on the right of the colon
};




class CoolGuy_RGB
{
	public:
		    static void Set_RGB(int pin,unsigned char num, unsigned char red,unsigned char green,unsigned char blue);//the sencond arugment num
	private://means choose which RGB light, the left arugments means the amount of the corresponding color in the RGB light.
};
class CoolGuy_Motor
{
    public:
			static void Set_Motor(int pin, unsigned char num, unsigned char direction, unsigned char speed);//the second argument num means choose
	private:// which motor, the direction means the direction of the running motor, the speed means how fast the motor runs
};


class Pin_Init
{

	public:
		static uint8_t IOBitH;//define some variants to operate the register
		static uint8_t IOBitL;
		static uint8_t IOBitH2;
		static uint8_t IOBitL2;

		static uint8_t pin2;//we need two pins(pin and pin2) to communicate with the stm8.
	 	
	    static void Pin_Set(int pin);//pin initialization
	    static int Pin_Map(int pin);//pick another pin according to the first pin
	    static void Start();//remind stm8 that commnuication is going to start
        static void Send_Byte(unsigned char dat);//send data function
        static unsigned char Read_Byte();//receive data function
   
	private:
};





#endif
