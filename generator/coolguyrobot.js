'use strict';

goog.provide('Blockly.Arduino.coolguyrobot');

goog.require('Blockly.Arduino');



/////////////////////////////传感器模块/////////////////////////////////////////////////
/////////////////////////////传感器模块/////////////////////////////////////////////////
/////////////////////////////传感器模块/////////////////////////////////////////////////
/////////////////////////////传感器模块/////////////////////////////////////////////////
/////温度传感器模块////////读温度值在引脚COOLGUY_ANALOG_INPUT/////coolguy_temp_setup
Blockly.Arduino.coolguy_temp_setup = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_Sensor::Read_Temperature('+dropdown_pin+')';
   return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/////空气质量模块////////读空气质量在引脚COOLGUY_ANALOG_INPUT/////coolguy_airquality
Blockly.Arduino.coolguy_airquality = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_Sensor::Read_PM2_5('+dropdown_pin+')';
   return [code, Blockly.Arduino.ORDER_ATOMIC];
};

////声音传感器
Blockly.Arduino.coolguy_sensor_sound = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

///////红外测距传感器
Blockly.Arduino.coolguy_sensor_irranging = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

//光敏传感器
Blockly.Arduino.coolguy_sensor_photo = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


//按键传感器
Blockly.Arduino.coolguy_sensor_switch = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

//火焰传感器
Blockly.Arduino.coolguy_sensor_fire = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

//震动传感器
Blockly.Arduino.coolguy_sensor_shock = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

//触摸开关
Blockly.Arduino.coolguy_sensor_touch = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/////////////////////////////////循线模块/////////////////////////////////////////////////
/////////////////////////////////循线模块/////////////////////////////////////////////////
/////////////////////////////////循线模块/////////////////////////////////////////////////
/////////////////////////////////循线模块/////////////////////////////////////////////////
/////////////////////////////////循线模块/////////////////////////////////////////////////
/////////////////////////////////循线模块/////////////////////////////////////////////////
///////设置五灰度比较/////
Blockly.Arduino.coolguy_line_set = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1', Blockly.Arduino.ORDER_ATOMIC);//Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_NONE) || '0';
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   var num3 = Blockly.Arduino.valueToCode(this, 'num3',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   var num4 = Blockly.Arduino.valueToCode(this, 'num4',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   var num5 = Blockly.Arduino.valueToCode(this, 'num5',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::SetComparisonValue('+num1+','+num2+','+num3+','+num4+','+num5+');\n';
    return code;
};
///////设置五灰度端口/////
Blockly.Arduino.coolguy_line_port = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::WalkLine_Init('+dropdown_pin+');\n';
   return code;
};
//////转速？寻？路口后冲？秒///////coolguy_line1
Blockly.Arduino.coolguy_line1 = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//转速
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//路口数
   var num3 = Blockly.Arduino.valueToCode(this, 'num3',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//秒
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::RunWalkLine('+num2+','+num1+','+num3+');\n';
  return code;
};

//////转速？循线？秒后停止coolguy_line2
Blockly.Arduino.coolguy_line2 = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//转速
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//路口数
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::RunWalkLine_Timer('+num1+','+num2+');\n';
  return code;
};
//////转速？左转弯？线coolguy_line3    CoolGuyModule_WalkLine::RunWalkLine_Turn(int Direction,int MaxSpeed,int LineNum)
Blockly.Arduino.coolguy_line3 = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//转速
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//几线
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::RunWalkLine_Turn(0,'+num1+','+num2+');\n';
   return code;
};
//////转速？右转弯？线coolguy_line4
Blockly.Arduino.coolguy_line4 = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//转速
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//几线
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::RunWalkLine_Turn(1,'+num1+','+num2+');\n';
   return code;
};
//////读五灰度传感器？coolguy_line5
Blockly.Arduino.coolguy_line5 = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::GrayValue_ReadOne('+dropdown_pin+')';
   return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/////////////////////LED与OLED模块///////////////////////////////////////////////////////////////////
/////////////////////LED与OLED模块///////////////////////////////////////////////////////////////////
/////////////////////LED与OLED模块///////////////////////////////////////////////////////////////////
/////////////////////LED与OLED模块///////////////////////////////////////////////////////////////////
/////////////////////LED与OLED模块///////////////////////////////////////////////////////////////////
/////////////////////LED与OLED模块///////////////////////////////////////////////////////////////////
/////////////////////LED与OLED模块///////////////////////////////////////////////////////////////////
/////////////////////LED与OLED模块///////////////////////////////////////////////////////////////////
/////LED灯
Blockly.Arduino.coolguy_led = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  var dropdown_pin2 = this.getTitleValue('PIN2');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_coolguy_ledmo'+dropdown_pin2]='pinMode('+dropdown_pin2+',OUTPUT);';
  var code = 'digitalWrite('+dropdown_pin2+','+dropdown_pin1+');\n';
  return code;
};

Blockly.Arduino.coolguy_oled_English = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  var dropdown_pin2 = this.getTitleValue('PIN2');
  var str3 = Blockly.Arduino.valueToCode(this, 'TEXT3', Blockly.Arduino.ORDER_ATOMIC) || 'String(\"\")'
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.definitions_['define_coolguy_oled1'] = 'CoolGuyModule_OLED OLED;';
  var code = 'OLED.OLED_DrawString('+dropdown_pin1+','+dropdown_pin2+', '+str3+');\n';
  return code;
};

Blockly.Arduino.coolguy_oled_number = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  var dropdown_pin2 = this.getTitleValue('PIN2');
  var num = Blockly.Arduino.valueToCode(this, 'num',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.definitions_['define_coolguy_oled1'] = 'CoolGuyModule_OLED OLED;';
  var code = 'OLED.OLED_DrawValue('+dropdown_pin1+','+dropdown_pin2+', '+num+');\n';
  return code;
};

Blockly.Arduino.coolguy_oled3 = function() {
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.definitions_['define_coolguy_oled1'] = 'CoolGuyModule_OLED OLED;';
  var code = 'OLED.OLED_CLS();\n';
  return code;
};
Blockly.Arduino.coolguy_Nixietube = function() {
   var num = Blockly.Arduino.valueToCode(this, 'num',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuy'] = '#include <CoolGuy.h>';
   var code = 'CoolGuy_Digital::Set_Digital('+dropdown_pin+', '+num+');\n';
   return code;
};


/////////////////////////////////超声波模块//////////////////////////////////////////////////////////
/////////////////////////////////超声波模块//////////////////////////////////////////////////////////
/////////////////////////////////超声波模块//////////////////////////////////////////////////////////
/////////////////////////////////超声波模块//////////////////////////////////////////////////////////
/////////////////////////////////超声波模块//////////////////////////////////////////////////////////
//////超声波模块 
/////读一体超声波距离（注：在五灰度已设置端口）
Blockly.Arduino.coolguy_ultrasonic_already = function() {
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  var code = 'CoolGuyModule_WalkLine::GetUltrasonicVal()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};
///////读扩展超声波距离在引脚COOLGUY_ANALOG_INPUT
Blockly.Arduino.coolguy_ultrasonic_setup = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  var code = 'CoolGuyModule_Sensor:: Read_UltrasonicVal ('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

////////////////////////////////红外遥控模块//////////////////////////////////////////////////////////////////////
////////////////////////////////红外遥控模块//////////////////////////////////////////////////////////////////////
////////////////////////////////红外遥控模块//////////////////////////////////////////////////////////////////////
////////////////////////////////红外遥控模块//////////////////////////////////////////////////////////////////////
////////////////////////////////红外遥控模块//////////////////////////////////////////////////////////////////////
////////////////////////////////红外遥控模块//////////////////////////////////////////////////////////////////////
////////////////////////////////红外遥控模块//////////////////////////////////////////////////////////////////////
////红外遥控器 遥控通道1~8  ？键按下（上、下、左、右、上+B、下+B、左+B、右+B）引脚IO2IO3选择。
Blockly.Arduino.coolguy_remotecontrol = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  var dropdown_pin2 = this.getTitleValue('PIN2');
  var dropdown_pin3 = this.getTitleValue('PIN3');
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.setups_['setup_coolguy_remotecontrol_'+dropdown_pin3]='CoolGuyModule_IR:: IR_Init('+dropdown_pin3+');';
  var code = 'CoolGuyModule_IR::IR_KeyValueCmp('+dropdown_pin2+','+dropdown_pin1+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};





////////////////////////////////电机模块////////////////////////////////////////////////////////////////////
////////////////////////////////电机模块////////////////////////////////////////////////////////////////////
////////////////////////////////电机模块////////////////////////////////////////////////////////////////////
////////////////////////////////电机模块////////////////////////////////////////////////////////////////////
////////////////////////////////电机模块////////////////////////////////////////////////////////////////////
////////////////////////////////电机模块////////////////////////////////////////////////////////////////////
////////////////////////////////电机模块////////////////////////////////////////////////////////////////////
/////左电机数字为int类型，若超过-256~255，只取低十六位////
Blockly.Arduino.coolguy_motor_left = function() {
   var num = Blockly.Arduino.valueToCode(this, 'num',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   if(num>255)num=255;
   else if(num<-255)num=-255;
   else;
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   //Blockly.Arduino.setups_['setup_coolguy_motor_left']='CoolGuyModule_WalkLine:: RightMotorSpeed ('+num+');';
    var code = 'CoolGuyModule_WalkLine:: LeftMotorSpeed ('+num+');\n';
    return code;
};
/////右电机数字为int类型，若超过-256~255，只取低十六位////
Blockly.Arduino.coolguy_motor_right = function() {
   var num = Blockly.Arduino.valueToCode(this, 'num',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   if(num>255)num=255;
   else if(num<-255)num=-255;
   else;
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine:: RightMotorSpeed ('+num+');\n';
   return code;
};

////////////////////////////////////////////////系统自带模块///////////////////////////////
////////////////////////////////////////////////系统自带模块///////////////////////////////
////////////////////////////////////////////////系统自带模块///////////////////////////////
////////////////////////////////////////////////系统自带模块///////////////////////////////
////////////////////////////////////////////////系统自带模块///////////////////////////////
////////////////////////////////////////////////系统自带模块///////////////////////////////
////////////////////////////////////////////////系统自带模块///////////////////////////////
////////////////////////////////////////////////系统自带模块///////////////////////////////
////////////////////////////////////////////////系统自带模块///////////////////////////////
////////////////////////////////////////////////系统自带模块///////////////////////////////
///////////////////读系统模拟接口//////////////////////////
Blockly.Arduino.coolguy_analog_reading = function() {
   var dropdown_pin = this.getTitleValue('PIN');
  var code = 'analogRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};
///////////////////读系统数字接口//////////////////////////
Blockly.Arduino.coolguy_digital_reading = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
    Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
   var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

///////////////////PWM//////////////////////
Blockly.Arduino.coolguy_pwm = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   var pwm_num = this.getTitleValue('PWM_NUM');
    Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
   var code = 'analogWrite('+dropdown_pin+','+pwm_num+');\n';
    return code;
};
///////////////SERVO///////////////////////////servo_9.write(90)
Blockly.Arduino.coolguy_servo = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   var servo_num = this.getTitleValue('SERVO_NUM');
    Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
    Blockly.Arduino.definitions_['define_"servo']='#include <Servo.h>';
    Blockly.Arduino.setups_['setup_coolguy_servo'+dropdown_pin]='servo_'+dropdown_pin+'.attach('+dropdown_pin+');';
   var code = 'servo_'+dropdown_pin+'.write('+servo_num+');\n';
    return code;
};
// /////////////TIMER//////////////////////////millis()/1000.0
Blockly.Arduino.coolguy_timer = function() {
    Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  var code = 'millis()/1000.0';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.coolguy_serial1 = function() {
  var str3 = Blockly.Arduino.valueToCode(this, 'TEXT3', Blockly.Arduino.ORDER_ATOMIC) || 'String(\"\")'
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  var code = 'CoolGuyModule_StringCmp::SetString('+str3+');\n';
  return code;
};
Blockly.Arduino.coolguy_serial2 = function() {
  var str3 = Blockly.Arduino.valueToCode(this, 'TEXT3', Blockly.Arduino.ORDER_ATOMIC) || 'String(\"\")'
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.setups_['setup_coolguy_serial2'] = 'Serial.setTimeout(100);\n';
  var code = 'CoolGuyModule_StringCmp:: Compare_StringEqual('+str3+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};
Blockly.Arduino.coolguy_serial3 = function() {
  var str3 = Blockly.Arduino.valueToCode(this, 'TEXT3', Blockly.Arduino.ORDER_ATOMIC) || 'String(\"\")'
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.setups_['setup_coolguy_serial2'] = 'Serial.setTimeout(100);\n';
  var code = 'CoolGuyModule_StringCmp:: Compare_IncludeString ('+str3+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.coolguy_record_setup = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"record'] = '#include <wtr050.h>';
   Blockly.Arduino.definitions_['define_"record_setup'+dropdown_pin] = 'wtr050 wtr050_1('+dropdown_pin+');';
   var code = '';
   return code;
};
Blockly.Arduino.coolguy_record1 = function() {
  Blockly.Arduino.definitions_['define_"record'] = '#include <wtr050.h>';
  var code = 'wtr050_1.record_start();\n';
  return code;
};
Blockly.Arduino.coolguy_record2 = function() {
  Blockly.Arduino.definitions_['define_"record'] = '#include <wtr050.h>';
  var code = 'wtr050_1.record_stop();\n';
  return code;
};
Blockly.Arduino.coolguy_record3 = function() {
  Blockly.Arduino.definitions_['define_"record'] = '#include <wtr050.h>';
  var code = 'wtr050_1.play();\n';
  return code;
};
Blockly.Arduino.coolguy_allportinitial = function() {
  Blockly.Arduino.setups_['setup_input_initial port2'] = 'pinMode(2, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port3'] = 'pinMode(3, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port4'] = 'pinMode(4, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port12'] = 'pinMode(12, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port13'] = 'pinMode(13, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port9'] = 'pinMode(9, OUTPUT);';
  var code = '';
  return code;
};



