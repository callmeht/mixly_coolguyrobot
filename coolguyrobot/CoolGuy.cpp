#include <Arduino.h>
#include <MsTimer2.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "CoolGuyRobot.h"
#include "strbuf.h"
#include "iic.h"
#include "stdio.h"
#include "CoolGuy.h"

uint8_t Pin_Init::IOBitH;//variants  initialization
uint8_t Pin_Init::IOBitL;
uint8_t Pin_Init::IOBitH2;
uint8_t Pin_Init::IOBitL2;
uint8_t Pin_Init::pin2;


static volatile uint8_t *IO_Out;//pointer
static volatile uint8_t *IO_In;
static volatile uint8_t *IO_Reg;

static volatile uint8_t *IO_Out2;
static volatile uint8_t *IO_In2;
static volatile uint8_t *IO_Reg2;	
   


void Pin_Init::Start()
{

  *IO_Reg |= IOBitH;//����Ϊ���

  *IO_Out &= IOBitL;  //SDA ����͵�ƽ
  delayMicroseconds(100);//delay 100us
  
}
void Pin_Init::Send_Byte( unsigned char dat)
{
	
  unsigned char i,testb;
  for(i=0;i<8;i++)
  {
    *IO_Out2 &= IOBitL2; //SCL ���� 
    
    if(dat&0x01)//�ж��Ƿ񷢸ߵ�ƽ 
    {
      *IO_Out |= IOBitH;   //SDA ���� 
    } 
    else
    {
      *IO_Out &= IOBitL; //SDA ���� 
    }
    dat=dat>>1;
    
    delayMicroseconds(100);   //�ӳ�100us 
    *IO_Out2 |= IOBitH2;    //SCL ���� 
    delayMicroseconds(100);   //�ӳ�100us
  }
  
}
unsigned char Pin_Init::Read_Byte()
{

  unsigned char j,dat = 0;
  
  *IO_Reg &= IOBitL;  //SDA��������
  *IO_Out |= IOBitH;  
  
  for(j=0;j<8;j++)
  {
     *IO_Out2 &= IOBitL2;     //SCL ����
     delayMicroseconds(100);  //��ʱ 100us
;
     *IO_Out2 |= IOBitH2;    //SCL ����
    
     dat >>= 1;
     if(*IO_In&IOBitH)      //�������ߣ�����ϸߵ�ƽ�������� �����Ϊ�ͣ�������if��䣬������ 
     {
         dat |= 0x80;
     }
     delayMicroseconds(100);   
  }

  return dat;
}


void CoolGuy_Led::Set_Led(int pin, unsigned char num1, unsigned char num2)
{
	int i;
	
     //Pin_Init ledpin;
    Pin_Init::Pin_Set(pin);
	Pin_Init::Start();
    Pin_Init::Send_Byte(num1);
    Pin_Init::Send_Byte(num2);
    i = Pin_Init::Read_Byte(); 
   // Serial.println(i);
	delay(1); //������ʱ������һֱ������ 
	
}
/*void CoolGuy_DigitalShow::Set_DigitalNum(int pin, unsigned char num1, unsigned char num2)
{
	int i;
	
    //Pin_Init digitalpin;
	Pin_Init::Pin_Set(pin);
	//Pin_Set(pin);

	Pin_Init::Start();
    Pin_Init::Send_Byte(num1);
    Pin_Init::Send_Byte(num2);
    i =Pin_Init::Read_Byte(); 
  //  Serial.println(i);
	delay(1); //������ʱ������һֱ������ 
	
}*/

void CoolGuy_Digital::Set_Digital(int pin, double num)
{
	
	int i;
	long int num_int;
	unsigned char num1,num2,num3,num4,Digitalflag;
	num_int=(long int)(num*10);//change the double-type num to long-int-type num_int
    if(!(num_int%10))//to judge if the double-type num has zero decimals.
    {
    	num_int=num_int/10;
    	Digitalflag=0x01;//if the double-type num has zero decimals, then Digitalflag is 0x01
	}
	else
	{
		num_int=num_int%10000;
		Digitalflag=0x02;//if the double-type num has non-zero decimals, then Digitalflag is 0x02
	}
	num1=num_int/1000;//the first number to show
	num2=(num_int%1000)/100;//the second number to show
	num3=((num_int%1000)%100)/10;//the third number to show
	num4=((num_int%1000)%100)%10;//the fourth number to show
///}
	Pin_Init::Pin_Set(pin);
	Pin_Init::Start();
//	Pin_Init::Send_Byte(mode);
//	Pin_Init::Send_Byte((num_int>>8)&0xff);
//	Pin_Init::Send_Byte(num_int&0xff);
    Pin_Init::Send_Byte(0x05);//��ʾǰ�淢����5���ֽ� 
	Pin_Init::Send_Byte(num1);
	Pin_Init::Send_Byte(num2);
	Pin_Init::Send_Byte(num3);
	Pin_Init::Send_Byte(num4);
	Pin_Init::Send_Byte(Digitalflag);
	i=Pin_Init::Read_Byte(); 
//	Serial.println(i);
	delay(1); //������ʱ������һֱ������ 
	
}

void CoolGuy_Digital2::Set_Digital2(int pin, unsigned char num1, unsigned char num2)
{
		int i;
		Pin_Init::Pin_Set(pin);
		Pin_Init::Start();
		Pin_Init::Send_Byte(0x02);//��ʾǰ�淢���������ֽ� 
		Pin_Init::Send_Byte(num1);
		Pin_Init::Send_Byte(num2);
		i=Pin_Init::Read_Byte(); 
	//	Serial.println(i);
		delay(1); //������ʱ������һֱ������ 
}
void CoolGuy_RGB::Set_RGB(int pin, unsigned char num, unsigned char red, unsigned char green, unsigned char blue)
{
	
	int i;
   // Pin_Init rgbpin;
    Pin_Init::Pin_Set(pin);
 	//Pin_Set(pin); 

	Pin_Init::Start();
    Pin_Init::Send_Byte(num);
    Pin_Init::Send_Byte(red);
    Pin_Init::Send_Byte(green);
    Pin_Init::Send_Byte(blue);
    i = Pin_Init::Read_Byte(); 
   // Serial.println(i);
	
	delay(1); //������ʱ������һֱ������ 
	
}

void CoolGuy_Motor::Set_Motor(int pin, unsigned char num, unsigned char direction, unsigned char speed)
{
	
	int i;
    //Pin_Init motorpin;
    Pin_Init::Pin_Set(pin);

	Pin_Init::Start();
    Pin_Init::Send_Byte(num);
    Pin_Init::Send_Byte(direction);
    Pin_Init::Send_Byte(speed);
    i =Pin_Init::Read_Byte(); 
    //Serial.println(i);
	
	delay(1); //������ʱ������һֱ������ 
	
}
unsigned int CoolGuy_IR::Read_IR_Val(int pin, unsigned char num)
{
    unsigned int IR_Value;
    unsigned char val1,val2;
    Pin_Init::Pin_Set(pin);
	Pin_Init::Start();
    Pin_Init::Send_Byte(num);
	val1  = Pin_Init::Read_Byte();
	val2 = (Pin_Init::Read_Byte()); 
	IR_Value=val1 | (val2<<8);
	//Serial.print(val1);
	//Serial.print(" ");
    //Serial.println(val2);
	//Serial.print(" ");
	//Serial.println(IR_Value);
	
	return IR_Value;	
	//return val2;	
}

void Pin_Init::Pin_Set(int pin)
{

  IO_Reg = portModeRegister(digitalPinToPort(pin));//these functions are used to operate register 
  IO_Out = portOutputRegister(digitalPinToPort(pin));
  IO_In  = portInputRegister(digitalPinToPort(pin));
  IOBitH = digitalPinToBitMask(pin);
  IOBitL = ~IOBitH;

  pin2=Pin_Map(pin);
  IO_Reg2 = portModeRegister(digitalPinToPort(pin2));//���Ǹ�Ϊpin2�� 
  IO_Out2 = portOutputRegister(digitalPinToPort(pin2));
  IO_In2  = portInputRegister(digitalPinToPort(pin2));
  IOBitH2 = digitalPinToBitMask(pin2);
  IOBitL2 = ~IOBitH2;

  *IO_Reg |= IOBitH;//output
  *IO_Out |= IOBitH;//output high

  *IO_Reg2 |= IOBitH2;//pin2 output
  *IO_Out2 |= IOBitH2;//pin2 output high
  
}
int Pin_Init:: Pin_Map(int pin)
{
	switch(pin)
    {
    	case A0:
    		pin2=A1;
    	break;
    	
    	case A2:
    		pin2=A3;
    	break;
    	
    	case A4:
    		pin2=A5;
    	break;
    	
    	case 0:
    		pin2=1;
    	break;
    	
    	case 5:
    		pin2=6;
    	break;
    	
    	case 9:
    		pin2=10;
    	break;		
	}
	return pin2;
	
}

/*void test()//֮ǰû�в��Ժ��� 
{
	IO_Reg = portModeRegister(digitalPinToPort(3));
    IO_Out = portOutputRegister(digitalPinToPort(3));
    IO_In  = portInputRegister(digitalPinToPort(3));
    IOBitH = digitalPinToBitMask(3);
    IOBitL = ~IOBitH;
    *IO_Reg |= IOBitH;
    
    while(1)
    {
    	*IO_Out |= IOBitH;
    	delayMicroseconds(50);
    	*IO_Out &= IOBitL;
    	delayMicroseconds(50);
    		//*IO_Reg &= IOBitL;
         	//*IO_Out |= IOBit;
	}
}*/









