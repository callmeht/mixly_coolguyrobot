#if 0
version:V1.0
修改红外遥控数据协议
version:V1.1
修改了arduino 1.6版本，红外遥控不能使用
#endif



#include <Arduino.h>
#include <MsTimer2.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#include "CoolGuyRobot.h"
#include "strbuf.h"
#include "iic.h"
#include "stdio.h"






//********************红外模块*************************
int CoolGuyModule_IR::IRPin = 2;
unsigned char	CoolGuyModule_IR::IRData[2] = {0,0};
unsigned char CoolGuyModule_IR::Remote_Type ;	//遥控类型  0:为新遥控  1:为旧遥控   默认使用新遥控
unsigned char CoolGuyModule_IR::IRCode; //红外遥控返回
unsigned char CoolGuyModule_IR::IR_ID = 0;  //红外遥控返回

uint8_t CoolGuyModule_IR::IRIOBitH;

static volatile uint8_t *IRIO_In;


void CoolGuyModule_IR::IR_Init(int pin)
{
	IRPin = pin;
  pinMode(IRPin, INPUT);      // sets the digital pin as input

  if(pin == 2)
  {
  	 attachInterrupt(0, Remote_Task, FALLING);
  }
  else if(pin == 3)
  {
  	attachInterrupt(1, Remote_Task, FALLING);
  }


  IRIO_In  = portInputRegister(digitalPinToPort(pin));
  IRIOBitH = digitalPinToBitMask(pin);
 
}


int CoolGuyModule_IR::IR_KeyValueCmp(int key,int channel)    
{
  IR_ID = channel-1;  //获取通道
	/*if(key == IRCode && ((channel-1) == IRData[0] || Remote_Type == 1))
		return 1;
	else 
		return 0;*/
  if(IRData[0] == 0&&IRData[1] == 0)  //是否松开
  {
      if(key == 0) return 1;
  }
  else
  {
    if(key == IRCode && ((channel-1) == IRData[0] || Remote_Type == 1))
    {
        return 1;
    }
  }
  return 0;
}


void CoolGuyModule_IR::IR_ClearFlay()
{
	if(Remote_Type == 1)
	{
			IRData[1] = 0;
			IRCode = IRData[1];
	}
	MsTimer2::stop(); //停止计时 
}





void CoolGuyModule_IR::NECIR_Scan()
{
    unsigned char j,k;
    unsigned int N=0;
    unsigned char  IRCOM[4];
    
    N=0;
    while (READ_IRSIGN)           //等待IR 变为低电平，跳过4.5ms的前导高电平信号
    {
      delayMicroseconds(10);
      if(++N>=500)
      {
        goto IRloop;
      }
    }
    if(N<400)     //判断是不是4.5ms引导码
    {
      goto IRloop;
    }

    for (j=0;j<4;j++)         //收集四组数据
    { 

      for (k=0;k<8;k++)        //每组数据8位
      {

        N=0;
        while (!READ_IRSIGN)         
        { 
          delayMicroseconds(10);
          if(++N>=100)
          {
            goto IRloop;
          }
        }
        N=0;
        while (READ_IRSIGN)           
        {
          delayMicroseconds(10);
          if (++N>=200)
          { 
            goto IRloop;
          }                  
        }                                  
        IRCOM[j]=IRCOM[j] >> 1;                
        if (N>=100) 
        {
          IRCOM[j] = IRCOM[j] | 0x80;  //数据最高位补1
        }   
      }//end for k
    }//end for j

     

    if (IRCOM[2]+IRCOM[3] != 255)   //判断两个数是不是取反关系
    { 
      
      goto IRloop;
    }

    if(IRCOM[2]>1)
    {
      switch(IRCOM[2])
      {
        case 0x40: // '+'按键  代表上键
          IRData[1] = 1;
        break;

        case 0x19:  // '-'按键  代表下键
          IRData[1] = 2;
        break;

        case 0x07:  //前进按键 代表左键
          IRData[1] = 3;
        break;

        case 0x09:  //后退按键 代表右键
          IRData[1] = 4;
        break;

        case 0x18:  //2键对应 遥控 B+上键
          IRData[1] = 5;
        break;

        case 0x52:  //8键对应B+下键
          IRData[1] = 6;
        break;
        
        case 0x08:  //4键对应B+左键
          IRData[1] = 7;
        break;

        case 0x5A:  //6键对应B+右键
          IRData[1] = 8;
        break;
        
        default:
          IRData[1] = 0;
        break;
      }
    }
    if(Remote_Type==0)  Remote_Type = 1;
    

    IRloop:
      MsTimer2::set(100, IR_ClearFlay); //设置中断，每100ms进入一次中断服务程序
      MsTimer2::start();  //开始计时
}

void CoolGuyModule_IR::IR_Scan()
{
  unsigned char j,k;
  unsigned int N=0;
  unsigned char IRCOM[2];
  unsigned int buf[8];
  
  

  N=0;
  while (READ_IRSIGN)         
  {
    delayMicroseconds(10);
    if(++N>=100)
    {
      goto IRloop;
    }
  }

  for (j=0;j<2;j++)         //收集2组数据
  { 
    for (k=0;k<8;k++)        //每组数据8位
    {
      N=0;
      while (!READ_IRSIGN)          //等待 IR 变为高电电平
      { 
        delayMicroseconds(10);
        if(++N>=100)
        {
          goto IRloop;
        }
      }
      N=0;
      while (READ_IRSIGN)           //计算IR高电平时间
      {
        delayMicroseconds(10);
        if (++N>=100)
        { 
          goto IRloop;
        }                  //0.14ms计数过长自动离开
      }                                
      IRCOM[j]=IRCOM[j] >> 1;                  
      buf[k] = N;
      if (N>=40) 
      {
        IRCOM[j] = IRCOM[j] | 0x80; //数据最高位补1
      }   
    }//end for k
  }//end for j
  
  if (IRCOM[0]!=(unsigned char)(~IRCOM[1]))
  { 
    goto IRloop;
  }
  

  if((IRCOM[0]&0x0f) == 0x0f)  
  {
    if(((IRCOM[0]>>4)&0xf) == IR_ID) 
    {
       IRData[0] = 0; 
       IRData[1] = 0;
    }
  }
  else
  {
    if(((IRCOM[0]>>4)&0xf) <= 7) 
    {
       IRData[0] = IRCOM[0]>>4; 
    } 
    if((IRCOM[0]&0x0f) <= 8)
    {
         IRData[1] = IRCOM[0]&0x0f; 
    }
  }


  if(Remote_Type==0)  Remote_Type = 2;
  
  IRloop:
    ;   

}

void CoolGuyModule_IR::Remote_Task()
{
	//noInterrupts();

  int N=0;
  while (!READ_IRSIGN)            //等IR变为高电平，跳过9ms的前导低电平信号
  {
    delayMicroseconds(10);
    if(++N>=1000)
    {
      return ;
    }
  }
 
  if(N>600&&(Remote_Type==0||Remote_Type==1)) //新的NEC遥控   引导信号N大概936
  {
   NECIR_Scan();     //新遥控器
   
  }
  else if(N>255&&(Remote_Type==0||Remote_Type==2))  //旧的遥控  引导信号N大概300
  {
    IR_Scan();  //旧遥控器

  }


  IRCode = IRData[1];
  
 // interrupts();
}
//********************************************





//********************巡线模块**********************
int CoolGuyModule_WalkLine::ColorComparison_Buf1 = 400;
int CoolGuyModule_WalkLine::ColorComparison_Buf2 = 400;
int CoolGuyModule_WalkLine::ColorComparison_Buf3 = 400;
int CoolGuyModule_WalkLine::ColorComparison_Buf4 = 400;
int CoolGuyModule_WalkLine::ColorComparison_Buf5 = 400;
	
int CoolGuyModule_WalkLine::ColorPin1Value = 0;
int CoolGuyModule_WalkLine::ColorPin2Value = 0;
int CoolGuyModule_WalkLine::ColorPin3Value = 0;
int CoolGuyModule_WalkLine::ColorPin4Value = 0;
int CoolGuyModule_WalkLine::ColorPin5Value = 0;
					
uint16_t CoolGuyModule_WalkLine::DATA_BUF[6] = {0,0,0,0,0,0};
			
uint8_t CoolGuyModule_WalkLine::IOBitH;
uint8_t CoolGuyModule_WalkLine::IOBitL;


static volatile uint8_t *IO_Out;
static volatile uint8_t *IO_In;
static volatile uint8_t *IO_Reg;


void CoolGuyModule_WalkLine::WalkLine_Init(int pin)
{
		IO_Reg = portModeRegister(digitalPinToPort(pin));
    IO_Out = portOutputRegister(digitalPinToPort(pin));
    IO_In  = portInputRegister(digitalPinToPort(pin));
    IOBitH = digitalPinToBitMask(pin);
    IOBitL = ~IOBitH;
   
    *IO_Out |= IOBitH;
    *IO_Reg |= IOBitL; //set io output
    
    ReadSensor_Gray();
}

//读取超声波
float CoolGuyModule_WalkLine::GetUltrasonicVal()
{
	ReadSensor_Gray();
  return DATA_BUF[5] / 10.0;
}


void CoolGuyModule_WalkLine::SetComparisonValue(int ColorComparison1,int ColorComparison2,int ColorComparison3,int ColorComparison4,int ColorComparison5)
{
		ColorComparison_Buf1 = ColorComparison1;
		ColorComparison_Buf2 = ColorComparison2;
		ColorComparison_Buf3 = ColorComparison3;
		ColorComparison_Buf4 = ColorComparison4;
		ColorComparison_Buf5 = ColorComparison5;
}

void CoolGuyModule_WalkLine::RunWalkLine(int LineNum,int MaxSpeed,float EndTime)
{
		int i;
		unsigned int temp;
		
		
		for(i=0;i<LineNum;i++)
		{					
				WalkLineFunction(MaxSpeed);
				delay(2);
		}


		temp = EndTime * 400;
		while(temp--)
		{
				WalkReadValue();	
				WalkLineMotorControl(MaxSpeed);		
				
				delay(3);
		}


		LeftMotorSpeed(-255);	//反正
		RightMotorSpeed(-255);
		delay(20);
		LeftMotorSpeed(0);	//停止
		RightMotorSpeed(0);
}

void CoolGuyModule_WalkLine::RunWalkLine_Timer(int MaxSpeed,float Cnt)
{
		unsigned int i = Cnt*200;

		while(i --)
		{
			WalkReadValue();

	    WalkLineMotorControl(MaxSpeed);
		}
		
		LeftMotorSpeed(0);	//停止
		RightMotorSpeed(0);
		
}



void CoolGuyModule_WalkLine::RunWalkLine_Turn(int Direction,int MaxSpeed,int LineNum)
{
		int i,j;
		j = LineNum;
		while(j --)
		{
				if(Direction == 0)   //左转
				{
						LeftMotorSpeed(1-MaxSpeed);
						RightMotorSpeed(MaxSpeed);
						
						i = 0;  
						if(WalkReadValue() != 0)	//判断车在线上
						{
								
								while(1)
								{
										delay(1);
										WalkReadValue();
										if(ColorPin5Value < ColorComparison_Buf5)
										{
												//if(++i > 1)
												{
															break;
												}	
										}
										else
										{
												i = 0;	
										}
								}
						}
						
						
						
						i = 0;
						while(1)
						{
								delay(1);
								WalkReadValue();
								if(ColorPin2Value < ColorComparison_Buf2)
								{
										//if(++i > 1)
										{
													break;
										}	
								}
								else
								{
										i = 0;	
								}
						}
						
						if(j == 0)
						{
								LeftMotorSpeed(MaxSpeed);  //反转实现急停
								RightMotorSpeed(1-MaxSpeed); 
								delay(20);
						}
						
				}
				else
				{
						LeftMotorSpeed(MaxSpeed);
						RightMotorSpeed(1-MaxSpeed); 
						i = 0;
						if(WalkReadValue() != 0)	//判断车在线上
						{
								while(1)
								{
										delay(1);
										WalkReadValue();
										if(ColorPin1Value < ColorComparison_Buf1)
										{
												//if(++i > 1)
												{
															break;
												}	
										}
										else
										{
												i = 0;	
										}
								}
						}
						
						i = 0;
						while(1)
						{
								delay(1);
								WalkReadValue();
								if(ColorPin4Value < ColorComparison_Buf4)
								{
										//if(++i >1)
										{
													break;
										}	
								}
								else
								{
										i = 0;	
								}
						}
						if(j == 0)
						{
								LeftMotorSpeed(1-MaxSpeed);
								RightMotorSpeed(MaxSpeed);
								delay(20);
						}
				}
		}
		
		
		
		LeftMotorSpeed(0);	//停止
		RightMotorSpeed(0); 
}


void CoolGuyModule_WalkLine::ReadSensor_Gray()
{
	uint16_t DATA=0;
  uint8_t i=0,j=0,Timeus;
  for(j=0;j<6;j++)
  {
    for(i=0;i<16;i++)
    {
      SETSIGN_LOW; //设置低电平
        
      /***************延时*******************/
      delayMicroseconds(Communication_Wait_A);   //微妙延时
			/***************延时*******************/
					
			SETSIGN_HIGH;		//设置高电平
			SIGNSET_INPUT;	//设置输入模式
						
			/***************延时*******************/
		  delayMicroseconds(Communication_Wait_B);    //微妙延时
			/**************延时*******************/
	
			DATA <<= 1;
			if(READ_SIGN) //判断是否高电平
			{
			  DATA |= 0x0001;
			}				
					
			/***************延时*******************/
		        delayMicroseconds(Communication_Wait_C);    //微妙延时
			/***************延时******************/
			
			SIGNSET_OUTPUT;	//设置输出模式	
			
			/***************延时******************/
		        delayMicroseconds(Communication_Wait_D);   //微妙延时
			/**************延时*******************/
      }
      DATA_BUF[j] = DATA;  //数据存入缓存
    }
}

int CoolGuyModule_WalkLine::GrayValue_ReadOne(int i)
{
		ReadSensor_Gray();
		return DATA_BUF[i-1];
}

int CoolGuyModule_WalkLine:: WalkReadValue()
{
		int Temp;
		ReadSensor_Gray();
		
	
		
		ColorPin1Value = DATA_BUF[0];
    ColorPin2Value = DATA_BUF[1];
    ColorPin3Value = DATA_BUF[2];
    ColorPin4Value = DATA_BUF[3];
    ColorPin5Value = DATA_BUF[4];
    
    
    
    Temp = 0;
    if(ColorPin1Value < ColorComparison_Buf1)
    {
        Temp ++;
    }
    if(ColorPin2Value < ColorComparison_Buf2)
    {
        Temp ++;
    }
    if(ColorPin3Value < ColorComparison_Buf3)
    {
        Temp ++;
    }
    if(ColorPin4Value < ColorComparison_Buf4)
    {
        Temp ++;
    }
    if(ColorPin5Value < ColorComparison_Buf5)
    {
        Temp ++;
    }
    return Temp;   
}

void CoolGuyModule_WalkLine::WalkLineMotorControl(int MaxSpeed)
{

			 if(ColorPin2Value < ColorComparison_Buf2)   //左边触发黑线
  		{
  				LeftMotorSpeed(0);
  				RightMotorSpeed(MaxSpeed);
  		}
  		else if(ColorPin4Value < ColorComparison_Buf4)  //右边触发黑线 
  		{
  				LeftMotorSpeed(MaxSpeed);
  				RightMotorSpeed(0);
  		}
			else if(ColorPin1Value < ColorComparison_Buf1)    //最左边触发黑线   
  		{	
  				LeftMotorSpeed(MaxSpeed);
  				RightMotorSpeed(MaxSpeed);
  		}
  		else if(ColorPin5Value < ColorComparison_Buf5)    //最右边触发黑线 
  		{
  				LeftMotorSpeed(MaxSpeed);
  				RightMotorSpeed(MaxSpeed);
  		}
  		else
  		{
  				LeftMotorSpeed(MaxSpeed);
  				RightMotorSpeed(MaxSpeed);
  		}
  		
  		
}



void CoolGuyModule_WalkLine::WalkLineFunction(int MaxSpeed)
{
    int Count;
    Count = 0;

    while(1)
    {
    		WalkReadValue();
      	
				
				if(!(ColorPin1Value < ColorComparison_Buf1 || ColorPin5Value < ColorComparison_Buf5)) //判断不在路口
        {
        		if(Count > 3)	//判断是否已经检测到黑线
						{
								//delay(50);
								return ;	
						}
						else
						{
							
									Count  = 0;
						}
        }
        else	//在黑线上
        {
						Count ++;
						
        }    
        WalkLineMotorControl(MaxSpeed);  
       delay(1);
    }
}

void CoolGuyModule_WalkLine::RightMotorSpeed(int s)
{
		if(s >= 0)
		{
    	analogWrite(5,s);
    	analogWrite(10,0);
		}
		else
		{
			s = 0-s;  //转为整数
    	analogWrite(5,0);
    	analogWrite(10,s);
		}
}

void CoolGuyModule_WalkLine::LeftMotorSpeed(int s)
{
		if(s >= 0)
		{
    	analogWrite(6,0);
    	analogWrite(11,s);
		}
		else
		{
			s = 0-s;  //转为整数
			analogWrite(6,s);
    	analogWrite(11,0);
		}
}

//***************************************************


//******************传感器模块*********************
//读取温度
float CoolGuyModule_Sensor::Read_Temperature(int pin)
{
	return analogRead(pin)*250.0/512-50;
}

//读取PM2.5
float CoolGuyModule_Sensor::Read_PM2_5(int pin)
{
	int InPin,OutPin;
	float voMeasured,calcVoltage,dustDensity;
	if(pin == A0)
	{
			InPin = A0;
			OutPin = A1;
	}
	else if(pin == A2)
	{
			InPin = A2;
			OutPin = A3;
	}
	else
	{
			InPin = A4;
			OutPin = A5;
	}
	pinMode(OutPin,OUTPUT);
	pinMode(InPin,INPUT);
	
	
	digitalWrite(OutPin,LOW); // power on the LED
  delayMicroseconds(280);
  voMeasured = analogRead(InPin); // read the dust value
  delayMicroseconds(40);
  digitalWrite(OutPin,HIGH); // turn the LED off
  delayMicroseconds(9680);
  
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 0.17 * calcVoltage - 0.1;
  if(dustDensity < 0 ) dustDensity = 0.1;
	
	return dustDensity;
}

//读取超声波
float CoolGuyModule_Sensor::Read_UltrasonicVal(int pin)
{
		float distance;
		int TrigPin,EchoPin;
		if(pin == A0)
		{
				TrigPin = A0;
				EchoPin = A1;
		}
		else if(pin == A2)
		{
				TrigPin = A2;
				EchoPin = A3;
		}
		else
		{
				TrigPin = A4;
				EchoPin = A5;
		}
		pinMode(TrigPin,OUTPUT);
		pinMode(EchoPin,INPUT);
		
		digitalWrite(TrigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(TrigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW); 
// 检测脉冲宽度，并计算出距离  设置超时10ms
    distance = pulseIn(EchoPin, HIGH,10000) / 58.00;
    return distance;
}

//***************************************************



//********************OLED模块***********************

//OLED初始化函数
CoolGuyModule_OLED::CoolGuyModule_OLED()
{
  I2C_init();
  oleddelay(3000);//初始化之前的延时很重要！
  OLED_WrCmd(0xae);//--turn off oled panel
  OLED_WrCmd(0x00);//---set low column address
  OLED_WrCmd(0x10);//---set high column address
  OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_WrCmd(0x81);//--set contrast control register
  OLED_WrCmd(0xCF); // Set SEG Output Current Brightness
  OLED_WrCmd(0xa1);//--Set SEG/Column Mapping      0xa0左右反置 0xa1正常
  OLED_WrCmd(0xc8);//Set COM/Row Scan Direction    0xc0上下反置 0xc8正常
  OLED_WrCmd(0xa6);//--set normal display
  OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
  OLED_WrCmd(0x3f);//--1/64 duty
  OLED_WrCmd(0xd3);//-set display offset  Shift Mapping RAM Counter (0x00~0x3F)
  OLED_WrCmd(0x00);//-not offset
  OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
  OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  OLED_WrCmd(0xd9);//--set pre-charge period
  OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_WrCmd(0xda);//--set com pins hardware configuration
  OLED_WrCmd(0x12);
  OLED_WrCmd(0xdb);//--set vcomh
  OLED_WrCmd(0x40);//Set VCOM Deselect Level
  OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  OLED_WrCmd(0x02);//
  OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
  OLED_WrCmd(0x14);//--set(0x10) disable
  OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
  OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
  OLED_WrCmd(0xaf);//--turn on oled panel

  OLED_Fill(0x00);//初始清屏
  OLED_Set_Pos(0,0);
} 

//OLED驱动程序用的延时程序
void CoolGuyModule_OLED::oleddelay(unsigned int z)
{
  while(z--);
}


//OLED写数据
void CoolGuyModule_OLED::OLED_WrDat(unsigned char IIC_Data)
{
  I2C_Start();
  I2C_SendWrDAdr(0x78);
  I2C_SendDat(0x40);      //write data
  I2C_SendDat(IIC_Data);
  I2C_Stop();
}


//OLED写命令
void CoolGuyModule_OLED::OLED_WrCmd(unsigned char IIC_Command)
{
  uchar i=50;
  while(i--)
  {
  	 if(I2C_Start())
	 	break;
  }
  i = 50;
   while(i--)
  {
  	  if(I2C_SendWrDAdr(0x78))    //Slave address,SA0=0
	 	break;
  }
   i = 50;
   while(i--)
  {
  	  if(I2C_SendDat(0x00))   //write command 
	 	break;
  }        
   i = 50;
   while(i--)
  {
  	  if(I2C_SendDat(IIC_Command))   //write command 
	 	break;
  }             
 
  I2C_Stop();
}


//OLED 设置坐标
void CoolGuyModule_OLED::OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
  OLED_WrCmd(0xb0+y);
  OLED_WrCmd(((x&0xf0)>>4)|0x10);
  OLED_WrCmd((x&0x0f)|0x01);
} 


//刷屏函数
void CoolGuyModule_OLED::OLED_Fill(unsigned char bmp_dat) 
{
  unsigned char y,x;
  for(y=0;y<8;y++)
  {
    OLED_Set_Pos(0,y);
    for(x=0;x<128;x++)
    {
      OLED_WrDat(bmp_dat);
    }
  }
}

//OLED复位
void CoolGuyModule_OLED::OLED_CLS()
{
  unsigned char y,x;
  for(y=0;y<8;y++)
  {
    OLED_WrCmd(0xb0+y);
    OLED_WrCmd(0x01);
    OLED_WrCmd(0x10);
    for(x=0;x<128;x++)
    OLED_WrDat(0);
  }
}


/**************************
功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0~8  x: 0~127
f:是否取反显示
注意 需要使用的字符需要定义数组F8x16
****************************/
void CoolGuyModule_OLED::OLED_P8x16Ch(unsigned char x,unsigned char y,unsigned char N)
{
	unsigned char wm=0;
  unsigned int va=N<<4;

  OLED_Set_Pos(x , y);
  for(wm = 0;wm < 8;wm++)
  {
    OLED_WrDat(pgm_read_byte_near(F8x16 + va));
    va++;
  }
  OLED_Set_Pos(x,y + 1);
  for(wm = 0;wm < 8;wm++)
  {
    OLED_WrDat(pgm_read_byte_near(F8x16 + va));
    va++;
  }   
  
}

/*********************
字符串打印函�?
x:横坐�? 范围0-127
y:纵坐�? 范围0-6
该函数打印ascll码范围如下:

!"#$%&'()*+,-./0123456789:;<=>
?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]
^_`abcdefghijklmnopqrstuvwxyz{|}~

以上图标都可以打印显�?函数使用例子:
oled_puts(0,0,"123abcdfghijklmn6789:;<=>?@ABC'()*Z[\]^_`<=>#$%&");
**********************/
void CoolGuyModule_OLED::OLED_Print(unsigned char y,unsigned char x,String str)
{
  unsigned char x1=(x-1)*8,y1=(y-1)*2;
  unsigned int i,j;
  char c;
  j = str.length();
  	for(i=0;i<j;i++)
    {
    		c = str.charAt(i);
        if(x1>120||y1>6)  //判断是否超出屏幕显示范围
        {
            if(y1>=6)
            {
                return ;    //总坐标超出则退出函数
            }
            else
            {
               x1 = 0;      //未超出则纵坐标下移，横坐标清楚
               y1 +=2;
            }
        }
        if(!(c<0x20||c>0x7e))
        {
            OLED_P8x16Ch(x1,y1,c-0x20);    //ascll码最小为空格"0x20" 所有减�?x20就是字库所对应的序
        }
        x1 += 8;   //横坐标加8，因为每个字符横向占�?位显
    }
}

void CoolGuyModule_OLED::OLED_Print(unsigned char y,unsigned char x,float f)
{
	
		char Mem[15];
		char *buf = Mem;
		
		
		if ( f - (int) f == 0)
		{
					sprintf(buf,"%d",(int)f);
		}
		else
		{
				dtostrf(f,3,2,buf);
		}

  	String str = buf;
		OLED_Print(y,x,str);
  
}



//***************************************************


//************************字符串比较**************************
String CoolGuyModule_StringCmp::string;
void CoolGuyModule_StringCmp::SetString(String str)
{
    string = str;
}
bool CoolGuyModule_StringCmp::Compare_StringEqual(String str)
{
  
    if(string.equals(str))
    {
        return true;
    }
    
    return false;
}

bool CoolGuyModule_StringCmp::Compare_IncludeString(String str)
{   
  
    if(string.indexOf(str) != -1)
    {
        return true;
    }
    
    return false;
}

//***********************温度探头***************************
CoolGuyModule_Temperature_Read::CoolGuyModule_Temperature_Read(int pin)
  :OneWire(pin)
{
  
}

float CoolGuyModule_Temperature_Read::readT()
{

  byte data[12];
  byte addr[8];
 
  if ( !this->search(addr)) {
    this->reset_search();
    return -300; // if there is no sensor on OneWire Bus, return -300 value
  }
 
  this->reset();
  this->select(addr);
  this->write(0x44,1); // tell sensor to start converting
  this->reset();
  this->select(addr);
  this->write(0xBE); // tell sensor to start sending data
 
  for (int i = 0; i < 9; i++) { // we receive data in this loop
    data[i] = this->read();
  }
 
  this->reset_search();
 
  byte MSB = data[1];
  byte LSB = data[0];
 
  float raw = ((MSB << 8) | LSB); // move MSB left for 8 spaces, join that with LSB
  float realTempC = raw / 16; // move decimal point left for 4 spaces, result our temperature
  return realTempC;
}/*温度探头 结束*/


//***********************RTC时钟***************************
unsigned char CoolGuyModule_RTC::RtcTime[7];

void CoolGuyModule_RTC::Initial()
{
	I2C_init();  
}

void CoolGuyModule_RTC::Set_Time(int Year, int Month, int Date, int Hour, int Minutes, int Seconds)
{
	Year = Year % 1000;
	I2C_Start();
	I2C_SendWrDAdr_(RTC_DS1307_ADD<<1);
	I2C_SendDat(0);
	I2C_SendDat(bin2bcd(Seconds));
	I2C_SendDat(bin2bcd(Minutes));
	I2C_SendDat(bin2bcd(Hour));
	I2C_SendDat(0);
	I2C_SendDat(bin2bcd(Date));
	I2C_SendDat(bin2bcd(Month));
	I2C_SendDat(bin2bcd(Year));
	I2C_Stop();
  delay(1000);
}



uint16_t CoolGuyModule_RTC::Read_Time(int dat)
{
 if(dat==1)
 {uint16_t year;
  I2C_Read_(RTC_DS1307_ADD<<1, 6, (RTC_DS1307_ADD<<1) | 0x01, &RtcTime[6], 1);
 year =  RtcTime[6];
 year = bcd2bin(year) + 2000;
    return year; 
  }
  if(dat==2)
 {uint8_t month;
  I2C_Read_(RTC_DS1307_ADD<<1, 5, (RTC_DS1307_ADD<<1) | 0x01, &RtcTime[5], 1);
 month =  RtcTime[5];
    month = bcd2bin(month);
    return month;  
  }
  if(dat==3)
 { uint8_t date;
    I2C_Read_(RTC_DS1307_ADD<<1, 4, (RTC_DS1307_ADD<<1) | 0x01, &RtcTime[4], 1);
 date =  RtcTime[4];
    date = bcd2bin(date);
    return date; 
  }
  if(dat==4)
 { uint8_t hour;
  I2C_Read_(RTC_DS1307_ADD<<1, 2, (RTC_DS1307_ADD<<1) | 0x01, &RtcTime[2], 1);
  hour =  RtcTime[2];
    hour = bcd2bin(hour);
    return hour; 
  }
  if(dat==5)
 { uint8_t minute;
  I2C_Read_(RTC_DS1307_ADD<<1, 1, (RTC_DS1307_ADD<<1) | 0x01, &RtcTime[1], 1);
   minute =  RtcTime[1];
    minute = bcd2bin(minute);
    return minute; 
  }
  if(dat==6)
 { uint8_t second;
  I2C_Read_(RTC_DS1307_ADD<<1, 0, (RTC_DS1307_ADD<<1) | 0x01, &RtcTime[0], 1);
 second =  RtcTime[0];
    second = bcd2bin(second);
    return second; 
  }

}


//***********************ä¸‰è½´ä»¥åŠç”µå­ç½—ç›˜***************************
unsigned char CoolGuyModule_ElectroniccompassandThreeAxis::xyz[7];

void CoolGuyModule_ElectroniccompassandThreeAxis::Initial()
{
	I2C_init();
	I2C_Write(ElectroniccompassandThreeAxis_adress << 1, 0x02, 0);
	I2C_Write(ElectroniccompassandThreeAxis_adress << 1, 0x00, 0);
}

int CoolGuyModule_ElectroniccompassandThreeAxis::XYZandHeading_display(uint8_t ZXY)
{
  I2C_Read_(ElectroniccompassandThreeAxis_adress << 1, 03, ElectroniccompassandThreeAxis_adress << 1 | 1, xyz, 6);
  if(ZXY==1)
  {
	int x = xyz[0] << 8 | xyz[1];
	return x;
  }
  if(ZXY==2)
  {
  int z = xyz[2] << 8 | xyz[3];
  return z;
  }
  if(ZXY==3)
  {
  int y = xyz[4] << 8 | xyz[5];
  return y;
  }
}


double CoolGuyModule_ElectroniccompassandThreeAxis::XYZandHeading_display_H()
{
	double HX, HY, HZ, H;
	HX = XYZandHeading_display(1);
	HY = XYZandHeading_display(3);
	HZ = XYZandHeading_display(2);
	if (HX > 0x07FF) HX = 0xFFFF - HX;
	if (HZ > 0x07FF) HZ = 0xFFFF - HZ;
	if (HY > 0x07FF) HY = 0xFFFF - HY;
	H = 0;
	if (HY > 0) H = 90.0 - atan(HX / HY) * 180.0 / M_PI;
	if (HY < 0) H = 270.0 - atan(HX / HY) * 180.0 / M_PI;
	if (HY == 0 && HX < 0) H = 180;
	if (HY == 0 && HX > 0) H = 0;
	return H;
}



//*********************************************WiFi*****************************************


#ifdef _CoolGuyModule_iCloudMemory_BuildENABLE_
#pragma message("Please check command Line -> CoolGuyRobot.h 13:#define _CoolGuyModule_iCloudMemory_BuildENABLE_")
CoolGuyModule_iCloudMemory::CoolGuyModule_iCloudMemory()
{
	int i=0;
	for(i=1;i<21;i++)
	{
		RevBuf[i]="-1";
	}
  
}

void CoolGuyModule_iCloudMemory::Serial_Init()
{
	Serial.begin(9600);
}

String CoolGuyModule_iCloudMemory::iCloud_Read_String(String MACaddr,int addr)
{
	String rev = String();
	int Timeout=0;

	while(Serial.available()> 0){
	  Serial.read();
	}

	if(addr>0&&addr<21)
	{
		Serial.print(MACaddr);
		Serial.print("&R");
		Serial.println(addr);
		// delay(100);

		while(Serial.available() <= 0)
		{
			Timeout ++;
			if(Timeout>=30) 
			{
				return RevBuf[addr];
			}
			delay(3);
		}
		
		int index = 0;
		Timeout = 5;
		
		while(Timeout--)
		{
			if(Serial.available()>0)
			{
				rev += (char)Serial.read();
				Timeout = 5;
			}
			delay(1);
		}
		RevBuf[addr]=rev;
	}
	else
	{
		RevBuf[addr] = "-1";
	}
	
	return RevBuf[addr];
}

float CoolGuyModule_iCloudMemory::iCloud_Read_Float(String MACaddr,int addr)
{
	float rev_f = -1;
    String rev = String();
    int Time_out=0;

    while(Serial.available()> 0){
      Serial.read();
    }

    if(addr>0&&addr<21)
	{
		Serial.print(MACaddr);
		Serial.print("&R");
		Serial.println(addr);
		// delay(100);

		while(Serial.available() <= 0)
		{
			Time_out++;
			if(Time_out>=30) 
			{
				return RevBuf[addr].toFloat();
			}
			delay(3);
		}
 
		int index = 0;
		Time_out = 5;
	
		while(Time_out--)
		{
			if(Serial.available()>0)
			{
				rev += (char)Serial.read();
				Time_out = 5;
			}
			delay(1);
		}
		RevBuf[addr]=rev;

		/************************
		*以下代码是为了string转换成float
		*/
		int i;
		int digitsnum=0;
	  
		if(rev.length()>0){
			if(rev[0]>='0'&&rev[0]<='9'&&rev[0]!='.'){
		  
				for(i=1;i<rev.length();i++){
				  if(rev[i]=='.'){
					digitsnum++;
					continue;
				  }else if(rev[i]>='0'&&rev[i]<='9'){
					continue;
				  }else{
					return RevBuf[addr].toFloat();
				  }
				}
		  
				if(digitsnum>1){
					return RevBuf[addr].toFloat();
				}else{
					rev_f=rev.toFloat();
				}
	  
			}else{
				return RevBuf[addr].toFloat();
			}
	   
		}else{
			return RevBuf[addr].toFloat();
		}
	}
	return rev_f;
}

void CoolGuyModule_iCloudMemory::iCloud_Write(int addr,String data)
{
	int Time_out = 0;
	if(addr>0&&addr<21)
	{
		while(Serial.available()> 0){
		  Serial.read();
		}
		Serial.print("&W");
		Serial.print(addr);
		Serial.print(" ");
		Serial.println(data);
		while(Serial.available() <= 0)
		{
			Time_out++;
			if(Time_out>=30) 
			{
				return ;
			}
			delay(3);
		}
		while(Serial.available()> 0){
		  Serial.read();
		}
	}
}

void CoolGuyModule_iCloudMemory::iCloud_Write(int addr,float data)
{
	int Time_out = 0;
	if(addr>0&&addr<21)
	{	
		while(Serial.available()> 0){
		  Serial.read();
		}
		Serial.print("&W");
		Serial.print(addr);
		Serial.print(" ");
		Serial.println(data);
		while(Serial.available() <= 0)
		{
			Time_out++;
			if(Time_out>=30) 
			{
				return ;
			}
			delay(3);
		}
		while(Serial.available()> 0){
		  Serial.read();
		}
	}
}
//******************************************************************************************
#endif


//***********************RGB***************************
CoolGuyModule_WS2812::CoolGuyModule_WS2812(uint16_t num_leds)
{
	count_led = num_leds;

	pixels = (uint8_t*)malloc(count_led * 3);
#ifdef RGB_ORDER_ON_RUNTIME
	offsetGreen = 0;
	offsetRed = 1;
	offsetBlue = 2;
#endif
#ifdef USE_GLOBAL_Brightness
	Brightness = 255;
#endif
}

void CoolGuyModule_WS2812::SetRGB(uint8_t _Brightness, uint8_t r, uint8_t g, uint8_t b)
{
  uint16_t index =0;
	if (index < count_led)
	{
		uint16_t tmp = index * 3;
		pixels[OFFSET_R(tmp)] = r;
		pixels[OFFSET_G(tmp)] = g;
		pixels[OFFSET_B(tmp)] = b;
	}
  SetBrightness( _Brightness);
  CoolGuyModule_WS2812::Sync();
  delay(50);
}
void CoolGuyModule_WS2812::SetRGB(uint8_t _Brightness, uint32_t rgb)
{
    uint16_t index =0;
	if (index < count_led)
	{
		uint16_t tmp = index * 3;
		pixels[OFFSET_R(tmp)] = (rgb >> 16) & 0xFF;
		pixels[OFFSET_G(tmp)] = (rgb >> 8) & 0xFF;
		pixels[OFFSET_B(tmp)] = rgb & 0xFF;
	}
  SetBrightness( _Brightness);
  CoolGuyModule_WS2812::Sync();
  delay(50);
}
uint32_t CoolGuyModule_WS2812::GetRGB()
{ uint16_t index =0;
	if (index < count_led)
	{
		uint16_t tmp = index * 3;
		return ((uint32_t)(pixels[OFFSET_R(tmp)]) << 16) | (pixels[OFFSET_G(tmp)] << 8) | pixels[OFFSET_B(tmp)];
	}
	return 0;
}
uint8_t CoolGuyModule_WS2812::GetR()
{ uint16_t index =0;
	if (index < count_led)
	{
		uint16_t tmp = index * 3;
		return pixels[OFFSET_R(tmp)];
	}
	return 0;
}
uint8_t CoolGuyModule_WS2812::GetG()
{ uint16_t index =0;
	if (index < count_led)
	{
		uint16_t tmp = index * 3;
		return pixels[OFFSET_G(tmp)];
	}
	return 0;
}
uint8_t CoolGuyModule_WS2812::GetB()
{ uint16_t index =0;
	if (index < count_led)
	{
		uint16_t tmp = index * 3;
		return pixels[OFFSET_B(tmp)];
	}
	return 0;
}


void CoolGuyModule_WS2812::Sync()
{
	*CoolGuyModule_WS2812_port_reg |= pinMask; // Enable DDR
	CoolGuyModule_WS2812_sendarray_mask(pixels, 3 * count_led, pinMask, (uint8_t*)CoolGuyModule_WS2812_port, (uint8_t*)CoolGuyModule_WS2812_port_reg);
}

#ifdef RGB_ORDER_ON_RUNTIME
void CoolGuyModule_WS2812::setColorOrderGRB()   // Default color order
{
	offsetGreen = 0;
	offsetRed = 1;
	offsetBlue = 2;
}

void CoolGuyModule_WS2812::setColorOrderRGB()
{
	offsetRed = 0;
	offsetGreen = 1;
	offsetBlue = 2;
}

void CoolGuyModule_WS2812::setColorOrderBRG()
{
	offsetBlue = 0;
	offsetRed = 1;
	offsetGreen = 2;
}
#endif
void  CoolGuyModule_WS2812::CoolGuyModule_WS2812_sendarray_mask(uint8_t *data, uint16_t datlen, uint8_t maskhi, uint8_t *port, uint8_t *portreg)
{
	uint8_t curbyte, ctr, masklo;
	uint8_t sreg_prev;

	masklo = ~maskhi & *port;
	maskhi |= *port;
	sreg_prev = SREG;
	cli();

	while (datlen--) {
		curbyte = *data++;
#ifdef USE_GLOBAL_Brightness
		curbyte = (int)((curbyte)*(int)(Brightness)) >> 8;
#endif
		asm volatile(
			"       ldi   %0,8  \n\t"
			"loop%=:            \n\t"
			"       st    X,%3 \n\t"    //  '1' [02] '0' [02] - re
#if (w1_nops&1)
			w_nop1
#endif
#if (w1_nops&2)
			w_nop2
#endif
#if (w1_nops&4)
			w_nop4
#endif
#if (w1_nops&8)
			w_nop8
#endif
#if (w1_nops&16)
			w_nop16
#endif
			"       sbrs  %1,7  \n\t"    //  '1' [04] '0' [03]
			"       st    X,%4 \n\t"     //  '1' [--] '0' [05] - fe-low
			"       lsl   %1    \n\t"    //  '1' [05] '0' [06]
#if (w2_nops&1)
			w_nop1
#endif
#if (w2_nops&2)
			w_nop2
#endif
#if (w2_nops&4)
			w_nop4
#endif
#if (w2_nops&8)
			w_nop8
#endif
#if (w2_nops&16)
			w_nop16
#endif
			"       brcc skipone%= \n\t"    //  '1' [+1] '0' [+2] -
			"       st   X,%4      \n\t"    //  '1' [+3] '0' [--] - fe-high
			"skipone%=:               "     //  '1' [+3] '0' [+2] -

#if (w3_nops&1)
			w_nop1
#endif
#if (w3_nops&2)
			w_nop2
#endif
#if (w3_nops&4)
			w_nop4
#endif
#if (w3_nops&8)
			w_nop8
#endif
#if (w3_nops&16)
			w_nop16
#endif

			"       dec   %0    \n\t"    //  '1' [+4] '0' [+3]
			"       brne  loop%=\n\t"    //  '1' [+5] '0' [+4]
			:	"=&d" (ctr)
			//    :	"r" (curbyte), "I" (_SFR_IO_ADDR(CoolGuyModule_WS2812_PORTREG)), "r" (maskhi), "r" (masklo)
			: "r" (curbyte), "x" (port), "r" (maskhi), "r" (masklo)
			);
	}

	SREG = sreg_prev;
}

CoolGuyModule_WS2812::~CoolGuyModule_WS2812()
{
}

#ifndef ARDUINO
void CoolGuyModule_WS2812::SetOutput(const volatile uint8_t* port, volatile uint8_t* reg, uint8_t pin)
{
	pinMask = (1 << pin);
	CoolGuyModule_WS2812_port = port;
	CoolGuyModule_WS2812_port_reg = reg;
}
#else
void CoolGuyModule_WS2812::SetOutput(uint8_t pin)
{
	pinMask = digitalPinToBitMask(pin);
	CoolGuyModule_WS2812_port = portOutputRegister(digitalPinToPort(pin));
	CoolGuyModule_WS2812_port_reg = portModeRegister(digitalPinToPort(pin));
}
#endif

