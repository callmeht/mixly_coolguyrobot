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

#include "CoolGuyRobot.h"
#include "strbuf.h"
#include "iic.h"
#include "stdio.h"




//********************红外模块************************
int CoolGuyModule_IR::IRPin = 2;
unsigned char	CoolGuyModule_IR::IRData[2] = {0,0};
unsigned char CoolGuyModule_IR::Remote_Type ;	//遥控类型  0:为新遥控  1:为旧遥控   默认使用新遥控
unsigned char CoolGuyModule_IR::IRCode; //红外遥控返回值
unsigned char CoolGuyModule_IR::IR_ID = 0;  //红外遥控返回值

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
  IR_ID = channel-1;  //获取通道值
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
    while (READ_IRSIGN)            //等 IR 变为低电平，跳过4.5ms的前导高电平信号。
    {
      delayMicroseconds(10);
      if(++N>=500)
      {
        goto IRloop;
      }
    }
    if(N<400)     //判断是不是 4.5ms引导码，如果是 则进入
    {
      goto IRloop;
    }

    for (j=0;j<4;j++)         //收集四组数据
    { 

      for (k=0;k<8;k++)        //每组数据有8位
      {

        N=0;
        while (!READ_IRSIGN)          //等 IR 变为高电平  最长560
        { 
          delayMicroseconds(10);
          if(++N>=100)
          {
            goto IRloop;
          }
        }
        N=0;
        while (READ_IRSIGN)           //计算IR高电平时长  最长1690
        {
          delayMicroseconds(10);
          if (++N>=200)
          { 
            goto IRloop;
          }                  //0.14ms计数过长自动离开。
        }                        //高电平计数完毕                
        IRCOM[j]=IRCOM[j] >> 1;                  //数据最高位补“0”
        if (N>=100) 
        {
          IRCOM[j] = IRCOM[j] | 0x80; //数据最高位补“1”
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

        case 0x07:  //'前一级'按键 代表左键
          IRData[1] = 3;
        break;

        case 0x09:  //'后一级'按键 代表右键
          IRData[1] = 4;
        break;

        case 0x18:  //'2'键  对应 遥控 B+上键
          IRData[1] = 5;
        break;

        case 0x52:  //'8'键  B+下键
          IRData[1] = 6;
        break;
        
        case 0x08:  //'4'键  B+左键
          IRData[1] = 7;
        break;

        case 0x5A:  //'6'键  B+右键
          IRData[1] = 8;
        break;
        
        default:
          IRData[1] = 0;
        break;
      }
    }
    if(Remote_Type==0)  Remote_Type = 1;
    

    IRloop:
      MsTimer2::set(100, IR_ClearFlay); //设置中断，每100ms进入一次中断服务程序 onTimer()  
      MsTimer2::start(); //开始计时 
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
    for (k=0;k<8;k++)        //每组数据有8位
    {
      N=0;
      while (!READ_IRSIGN)          //等 IR 变为高电平
      { 
        delayMicroseconds(10);
        if(++N>=100)
        {
          goto IRloop;
        }
      }
      N=0;
      while (READ_IRSIGN)           //计算IR高电平时长
      {
        delayMicroseconds(10);
        if (++N>=100)
        { 
          goto IRloop;
        }                  //0.14ms计数过长自动离开。
      }                        //高电平计数完毕                
      IRCOM[j]=IRCOM[j] >> 1;                  //数据最高位补“0”
      buf[k] = N;
      if (N>=40) 
      {
        IRCOM[j] = IRCOM[j] | 0x80; //数据最高位补“1”
      }   
    }//end for k
  }//end for j
  
  if (IRCOM[0]!=(unsigned char)(~IRCOM[1]))
  { 
    goto IRloop;
  }
  

  if((IRCOM[0]&0x0f) == 0x0f) //按键抬起数据 低4位为f 高4位为通道
  {
    if(((IRCOM[0]>>4)&0xf) == IR_ID)  //判断是否和制定通道一致
    {
       IRData[0] = 0;  //清零按键值
       IRData[1] = 0;
    }
  }
  else
  {
    if(((IRCOM[0]>>4)&0xf) <= 7)  //最大7个通道
    {
       IRData[0] = IRCOM[0]>>4; //高4位是地址
    } 
    if((IRCOM[0]&0x0f) <= 8)  //最多8个按键值
    {
         IRData[1] = IRCOM[0]&0x0f; //低4位是数据
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
  while (!READ_IRSIGN)            //等IR变为高电平，跳过9ms的前导低电平信号。
  {
    delayMicroseconds(10);
    if(++N>=1000)
    {
      return ;
    }
  }
 
  if(N>600&&(Remote_Type==0||Remote_Type==1)) //新的NEC遥控   引导信号N大概936
  {
   NECIR_Scan();    //新遥控
   
  }
  else if(N>255&&(Remote_Type==0||Remote_Type==2))  //旧的遥控  引导信号N大概300
  {
    IR_Scan();   //旧遥控

  }


  IRCode = IRData[1];
  
 // interrupts();
}
//********************************************





//********************巡线模块**********************
//初始化灰度传感器比较值全部500
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


		temp = EndTime * 500;
		while(temp--)
		{
				WalkReadValue();	
				WalkLineMotorControl(MaxSpeed);		
				
				//delay(1);
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
								LeftMotorSpeed(MaxSpeed);	//反转实现急停
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
			/***************延时*******************/
	
			DATA <<= 1;
			if(READ_SIGN) //判断是否高电平
			{
			  DATA |= 0x0001;
			}				
					
			/***************延时*******************/
		        delayMicroseconds(Communication_Wait_C);    //微妙延时
			/***************延时*******************/
			
			SIGNSET_OUTPUT;	//设置输出模式		
			
			/***************延时*******************/
		        delayMicroseconds(Communication_Wait_D);    //微妙延时
			/***************延时*******************/
      }
      DATA_BUF[j] = DATA;   //数据存入缓存
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

			 if(ColorPin2Value < ColorComparison_Buf2)  //左边触发黑线   右加速
  		{
  				LeftMotorSpeed(0);
  				RightMotorSpeed(MaxSpeed);
  		}
  		else if(ColorPin4Value < ColorComparison_Buf4)  //右边触发黑线   右加速
  		{
  				LeftMotorSpeed(MaxSpeed);
  				RightMotorSpeed(0);
  		}
			else if(ColorPin1Value < ColorComparison_Buf1)   //最左边触发黑线   
  		{	
  				LeftMotorSpeed(MaxSpeed);
  				RightMotorSpeed(MaxSpeed);
  		}
  		else if(ColorPin5Value < ColorComparison_Buf5)  //最右边触发黑线 
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
			s = 0-s;  //转为正
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
			s = 0-s;  //转为正
			analogWrite(6,s);
    	analogWrite(11,0);
		}
}

//***************************************************


//*******************传感器模块**********************
//读取温度值
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

//读取超声波值
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
// 检测脉冲宽度，并计算出距离
    distance = pulseIn(EchoPin, HIGH) / 58.00;
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
  OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
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

  OLED_Fill(0x00); //初始清屏
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
功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7   x: 0~127
f:是否取反显示
注意 需要使用的话 需要定义数组 F8x16
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
字符串打印函数
x:横坐标  范围0-127
y:纵坐标  范围0-6
该函数打印ascll码 范围如下:

!"#$%&'()*+,-./0123456789:;<=>
?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]
^_`abcdefghijklmnopqrstuvwxyz{|}~

以上图标都可以打印显示,函数使用例子:
oled_puts(0,0,"123abcdfghijklmn6789:;<=>?@ABC'()*Z[\]^_`<=>#$%&");
**********************/
void CoolGuyModule_OLED::OLED_DrawString(unsigned char y,unsigned char x,String str)
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
               x1 = 0;      //未超出则纵坐标下移，横坐标清零
               y1 +=2;
            }
        }
        if(!(c<0x20||c>0x7e))
        {
            OLED_P8x16Ch(x1,y1,c-0x20);    //ascll码最小为空格"0x20" 所有减到0x20就是字库所对应的序号
        }
        x1 += 8;  //横坐标加8，因为每个字符横向占用8位显存
    }
}

void CoolGuyModule_OLED::OLED_DrawValue(unsigned char y,unsigned char x,float f)
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
		OLED_DrawString(y,x,str);
  
}



//***************************************************


//************************字符串比较***************************
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
