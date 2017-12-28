'use strict';

goog.provide('Blockly.Arduino.coolguyrobot');

goog.require('Blockly.Arduino');


/*                     其他串口模块                      */
/*设定比较内容*/
Blockly.Arduino.coolguy_serial_content_set = function() {
  var str3 = Blockly.Arduino.valueToCode(this, 'TEXT3', Blockly.Arduino.ORDER_ATOMIC) || 'String(\"\")'
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  var code = 'CoolGuyModule_StringCmp::SetString('+str3+');\n';
  return code;
};

/*比较内容完全相同*/
Blockly.Arduino.coolguy_serial_content_compare_allsame = function() {
  var str3 = Blockly.Arduino.valueToCode(this, 'TEXT3', Blockly.Arduino.ORDER_ATOMIC) || 'String(\"\")'
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.setups_['setup_coolguy_serial2'] = 'Serial.setTimeout(100);\n';
  var code = 'CoolGuyModule_StringCmp:: Compare_StringEqual('+str3+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*比较内容包含*/
Blockly.Arduino.coolguy_serial_content_compare_include = function() {
  var str3 = Blockly.Arduino.valueToCode(this, 'TEXT3', Blockly.Arduino.ORDER_ATOMIC) || 'String(\"\")'
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.setups_['setup_coolguy_serial2'] = 'Serial.setTimeout(100);\n';
  var code = 'CoolGuyModule_StringCmp:: Compare_IncludeString ('+str3+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};/*                     其他串口模块结束                   */

/*                       循线模块                          */
/*设置五灰度比较值*/
Blockly.Arduino.coolguy_line_cmp_valueset = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1', Blockly.Arduino.ORDER_ATOMIC);//Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_NONE) || '0';
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   var num3 = Blockly.Arduino.valueToCode(this, 'num3',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   var num4 = Blockly.Arduino.valueToCode(this, 'num4',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   var num5 = Blockly.Arduino.valueToCode(this, 'num5',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::SetComparisonValue('+num1+','+num2+','+num3+','+num4+','+num5+');\n';
    return code;
};

/*设置五灰度端口*/
Blockly.Arduino.coolguy_line_portset = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::WalkLine_Init('+dropdown_pin+');\n';
   return code;
};

/*路口过冲设定*/
Blockly.Arduino.coolguy_line_crossroad = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//转速
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//路口数
   var num3 = Blockly.Arduino.valueToCode(this, 'num3',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//秒
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::RunWalkLine('+num2+','+num1+','+num3+');\n';
  return code;
};

/*巡线时间设定*/
Blockly.Arduino.coolguy_line_time = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//转速
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//路口数
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::RunWalkLine_Timer('+num1+','+num2+');\n';
  return code;
};

/*左转弯设定*/
Blockly.Arduino.coolguy_line_turnleft = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//转速
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//几线
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::RunWalkLine_Turn(0,'+num1+','+num2+');\n';
   return code;
};

/*右转弯设定*/
Blockly.Arduino.coolguy_line_turnright  = function() {
   var num1 = Blockly.Arduino.valueToCode(this, 'num1',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//转速
   var num2 = Blockly.Arduino.valueToCode(this, 'num2',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';//几线
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::RunWalkLine_Turn(1,'+num1+','+num2+');\n';
   return code;
};

/*选择五灰度传感器*/
Blockly.Arduino.coolguy_line_sensorchoose = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine::GrayValue_ReadOne('+dropdown_pin+')';
   return [code, Blockly.Arduino.ORDER_ATOMIC];
};/*                       循线模块结束                          */

/*                      超声波模块                             */
/*一体超声波 置于五灰度传感器上 无需设置端口*/
Blockly.Arduino.coolguy_ultrasonic_already = function() {
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  var code = 'CoolGuyModule_WalkLine::GetUltrasonicVal()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*读扩展超声波距离*/
Blockly.Arduino.coolguy_ultrasonic_setup = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  var code = 'CoolGuyModule_Sensor:: Read_UltrasonicVal ('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};/*                      超声波模块结束                          */

/*                      红外遥控器模块                          */
/*红外遥控器 遥控通道(1~8）  （无、上、下、左、右、上+B、下+B、左+B、右+B）键按下 引脚（IO2、IO3）*/
Blockly.Arduino.coolguy_remotecontrol = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  var dropdown_pin2 = this.getTitleValue('PIN2');
  var dropdown_pin3 = this.getTitleValue('PIN3');
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.setups_['setup_coolguy_remotecontrol_'+dropdown_pin3]='CoolGuyModule_IR:: IR_Init('+dropdown_pin3+');';
  var code = 'CoolGuyModule_IR::IR_KeyValueCmp('+dropdown_pin2+','+dropdown_pin1+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};/*                      红外遥控器模块结束                          */

/*                    其他传感器模块                     */
/*设置录音模块端口模块*/
Blockly.Arduino.coolguy_record_portsetup = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"record'] = '#include <wtr050.h>';
   Blockly.Arduino.definitions_['define_"record_setup'+dropdown_pin] = 'wtr050 wtr050_1('+dropdown_pin+');';
   var code = '';
   return code;
};

/*开始录音*/
Blockly.Arduino.coolguy_record_start = function() {
  Blockly.Arduino.definitions_['define_"record'] = '#include <wtr050.h>';
  var code = 'wtr050_1.record_start();\n';
  return code;
};

/*停止录音*/
Blockly.Arduino.coolguy_record_stop = function() {
  Blockly.Arduino.definitions_['define_"record'] = '#include <wtr050.h>';
  var code = 'wtr050_1.record_stop();\n';
  return code;
};

/*播放录音*/
Blockly.Arduino.coolguy_record_play = function() {
  Blockly.Arduino.definitions_['define_"record'] = '#include <wtr050.h>';
  var code = 'wtr050_1.play();\n';
  return code;
};

/*温度传感器模块*/
Blockly.Arduino.coolguy_temp_get = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   // Blockly.Arduino.definitions_['define_"Wire.h'] = '#include <Wire.h>';
   // Blockly.Arduino.definitions_['define_"OneWire.h'] = '#include <OneWire.h>';
   Blockly.Arduino.definitions_['define_"CoolGuyModule_Temperature_Read ds' + dropdown_pin] = 'CoolGuyModule_Temperature_Read ds(' + dropdown_pin +');';
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   //Blockly.Arduino.definitions_['float readT()'] = 'float readT(int pin){ OneWire ds(pin); byte data[12];  byte addr[8];   if ( !ds.search(addr)) {    ds.reset_search();    return -300;   }   ds.reset();  ds.select(addr);  ds.write(0x44,1);  ds.reset();  ds.select(addr);  ds.write(0xBE);    for (int i = 0; i < 9; i++) {     data[i] = ds.read();  }   ds.reset_search();   byte MSB = data[1];  byte LSB = data[0];   float raw = ((MSB << 8) | LSB);   float realTempC = raw / 16;   return realTempC;}';
   var code = 'ds.readT()';
   return [code, Blockly.Arduino.ORDER_ATOMIC];
};




/*空气质量检测模块*/
Blockly.Arduino.coolguy_airquality = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_Sensor::Read_PM2_5('+dropdown_pin+')';
   return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*声音传感器*/
Blockly.Arduino.coolguy_sensor_sound = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*红外测距传感器*/
Blockly.Arduino.coolguy_sensor_irranging = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*光敏传感器*/
Blockly.Arduino.coolguy_sensor_photo = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


/*按键传感器*/
Blockly.Arduino.coolguy_sensor_switch = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*火焰传感器*/
Blockly.Arduino.coolguy_sensor_fire = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*震动传感器*/
Blockly.Arduino.coolguy_sensor_shock = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*触摸开关*/
Blockly.Arduino.coolguy_sensor_touch = function() {
  var dropdown_pin = this.getTitleValue('PIN');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
  var code = '!digitalRead('+dropdown_pin+')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};/*                    其他传感器模块结束                     */

/*                       电机模块                             */
/*左电机*/
Blockly.Arduino.coolguy_motor_left = function() {
   var num = Blockly.Arduino.valueToCode(this, 'num',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   if (num > 255)
    {
      num=255;
    }
   else if (num < -255)
    {
      num = -255;
    }
   else;
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
    var code = 'CoolGuyModule_WalkLine:: LeftMotorSpeed ('+num+');\n';
    return code;
};

/*右电机*/
Blockly.Arduino.coolguy_motor_right = function() {
   var num = Blockly.Arduino.valueToCode(this, 'num',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   if (num > 255)
    {
      num = 255;
    }
   else if (num < -255)
    {
      num = -255;
    } 
   else;
   Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
   var code = 'CoolGuyModule_WalkLine:: RightMotorSpeed (' + num + ');\n';
   return code;
};/*                       电机模块结束                             */

/*                      LED/OLED模块                        */
/*oled显示英文字符串*/
Blockly.Arduino.coolguy_oled_English = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  var dropdown_pin2 = this.getTitleValue('PIN2');
  var str3 = Blockly.Arduino.valueToCode(this, 'TEXT3', Blockly.Arduino.ORDER_ATOMIC) || 'String(\"\")'
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.definitions_['define_coolguy_oled1'] = 'CoolGuyModule_OLED OLED;';
  var code = 'OLED.OLED_DrawString('+dropdown_pin1+','+dropdown_pin2+', '+str3+');\n';
  return code;
};

/*oled显示数字*/
Blockly.Arduino.coolguy_oled_number = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  var dropdown_pin2 = this.getTitleValue('PIN2');
  var num = Blockly.Arduino.valueToCode(this, 'num',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.definitions_['define_coolguy_oled1'] = 'CoolGuyModule_OLED OLED;';
  var code = 'OLED.OLED_DrawValue('+dropdown_pin1+','+dropdown_pin2+', '+num+');\n';
  return code;
};

/*oled清屏*/
Blockly.Arduino.coolguy_oled_clear = function() {
  Blockly.Arduino.definitions_['define_"CoolGuyRobot'] = '#include "CoolGuyRobot.h"';
  Blockly.Arduino.definitions_['define_coolguy_oled1'] = 'CoolGuyModule_OLED OLED;';
  var code = 'OLED.OLED_CLS();\n';
  return code;
};

/*数码管显示数字*/
Blockly.Arduino.coolguy_Nixietube = function() {
   var num = Blockly.Arduino.valueToCode(this, 'num',Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
   var dropdown_pin = this.getTitleValue('PIN');
   Blockly.Arduino.definitions_['define_"CoolGuy'] = '#include <CoolGuy.h>';
   var code = 'CoolGuy_Digital::Set_Digital('+dropdown_pin+', '+num+');\n';
   return code;
};

/*LED灯*/
Blockly.Arduino.coolguy_led = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  var dropdown_pin2 = this.getTitleValue('PIN2');
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  Blockly.Arduino.setups_['setup_input_'+dropdown_pin2]='pinMode('+dropdown_pin2+',OUTPUT);';
  Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin2] = 'digitalWrite('+dropdown_pin2+',HIGH);';
  var code = 'digitalWrite('+dropdown_pin2+','+dropdown_pin1+');\n';
  return code;
};/*                      LED/OLED模块结束                        */

/*                      系统模块                             */
/*读模拟引脚*/
Blockly.Arduino.coolguy_analog_reading = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   var code = 'analogRead('+dropdown_pin+')';
   return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*读数字引脚*/
Blockly.Arduino.coolguy_digital_reading = function() {
    var dropdown_pin = this.getTitleValue('PIN');
    Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
    Blockly.Arduino.setups_['setup_input_'+dropdown_pin] = 'pinMode('+dropdown_pin+', INPUT);';
    Blockly.Arduino.setups_['setup_input_pull_up'+dropdown_pin] = 'digitalWrite('+dropdown_pin+',HIGH);';
    var code = '!digitalRead('+dropdown_pin+')';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*设置PWM端口和输出*/
Blockly.Arduino.coolguy_pwm = function() {
   var dropdown_pin = this.getTitleValue('PIN');
   var pwm_num = this.getTitleValue('PWM_NUM');
   Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
   var code = 'analogWrite('+dropdown_pin+','+pwm_num+');\n';
   return code;
};

/*计时器（毫秒为单位）*/
Blockly.Arduino.coolguy_timer = function() {
  Blockly.Arduino.definitions_['define_"Arduino']='#include <Arduino.h>';
  var code = 'millis()/1000.0';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/*部分数字端口设为输出*/
Blockly.Arduino.coolguy_allportinitial = function() {
  Blockly.Arduino.setups_['setup_input_initial port2'] = 'pinMode(2, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port3'] = 'pinMode(3, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port4'] = 'pinMode(4, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port12'] = 'pinMode(12, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port13'] = 'pinMode(13, OUTPUT);';
  Blockly.Arduino.setups_['setup_input_initial port9'] = 'pinMode(9, OUTPUT);';
  var code = '';
  return code;
};/*                      系统模块结束                             */

//********************人工智能***********************
//************* MU摄像头模块***************
var dealy_time = 5000;
Blockly.Arduino.coolguy_mu_setup_start = function() {
    Blockly.Arduino.definitions_['define_VisionSensor'] = '#include "VisionSensor.h"';
    Blockly.Arduino.definitions_['define_VisionSensor_class'] = 'VisionSensor MU(Serial, 115200);';
    Blockly.Arduino.setups_['mu_setup_start_serial'] = 'Serial.begin(115200);';
    Blockly.Arduino.setups_['mu_setup_start'] = 'Serial.println("CMD+SENSOR_SETUP");';
    Blockly.Arduino.setups_['mu_setup_start_delay'] = 'delay(' + dealy_time + ');';
    var code = '';
    return code;
};

Blockly.Arduino.coolguy_mu_setup_stop = function() {
    Blockly.Arduino.setups_['mu_setup_stop_save'] = 'Serial.println("CMD+SENSOR_SAVE");';
    Blockly.Arduino.setups_['mu_setup_stop_delay1'] = 'delay(' + dealy_time + ');';
    Blockly.Arduino.setups_['mu_setup_stop_exit'] = 'Serial.println("CMD+SENSOR_EXIT");';
    Blockly.Arduino.setups_['mu_setup_stop_delay2'] = 'delay(' + dealy_time + ');';
    var code = '';
    return code;
};

Blockly.Arduino.coolguy_mu_setup_type = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  Blockly.Arduino.setups_['mu_setup_type']='Serial.println("CMD+VISION_TYPE='+dropdown_pin1+'");';
  Blockly.Arduino.setups_['mu_setup_type_delay']='delay(' + dealy_time + ');';
  var code = '';
  return code;
};

Blockly.Arduino.coolguy_mu_setup_level = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  Blockly.Arduino.setups_['mu_setup_level']='Serial.println("CMD+VISION_LEVEL='+dropdown_pin1+'");';
  Blockly.Arduino.setups_['mu_setup_level_delay']='delay(' + dealy_time + ');';
  var code = '';
  return code;
};

Blockly.Arduino.coolguy_mu_setup_zoom = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  Blockly.Arduino.setups_['mu_setup_zoom']='Serial.println("CMD+VISION_ZOOM='+dropdown_pin1+'");';
  Blockly.Arduino.setups_['mu_setup_zoom_delay']='delay(' + dealy_time + ');';
  var code = '';
  return code;
};

var mode_output = 0;//0表示CALLBACK，1表示DATAFLOW
Blockly.Arduino.coolguy_mu_setup_output = function() {
  var dropdown_pin1 = this.getTitleValue('PIN1');
  if(dropdown_pin1 == "DATAFLOW"){
    mode_output = 1;
  }else if(dropdown_pin1 == "CALLBACK"){
    mode_output = 0;
  }
  Blockly.Arduino.setups_['mu_setup_output_uart1']='Serial.println("CMD+UART_STATUS=1");';
  Blockly.Arduino.setups_['mu_setup_output_delay1']='delay(' + dealy_time + ');';
  Blockly.Arduino.setups_['mu_setup_output_uart']='Serial.println("CMD+UART_OUTPUT='+dropdown_pin1+'");';
  Blockly.Arduino.setups_['mu_setup_output_delay2']='delay(' + dealy_time + ');';
  Blockly.Arduino.setups_['mu_setup_output_usb1']='Serial.println("CMD+USB_STATUS=1");';
  Blockly.Arduino.setups_['mu_setup_output_delay3']='delay(' + dealy_time + ');';
  Blockly.Arduino.setups_['mu_setup_output_usb']='Serial.println("CMD+USB_OUTPUT='+dropdown_pin1+'");';
  Blockly.Arduino.setups_['mu_setup_output_delay4']='delay(' + dealy_time + ');';
  var code = '';
  return code;
};

Blockly.Arduino.coolguy_mu_data_read = function() {
  Blockly.Arduino.setups_['mu_setup_initialize'] = 'MU.begin();';  
  var code = '';
  if(mode_output == 0){//0表示CALLBACK，1表示DATAFLOW
    code = 'Serial.println("CMD+VISION_DETECT=X");\n';
  }
  code += 'MU.search();\n';
  return code;
};

Blockly.Arduino.coolguy_mu_datavalid = function() {
    Blockly.Arduino.definitions_['define_VisionSensor'] = '#include "VisionSensor.h"';
    Blockly.Arduino.definitions_['define_VisionSensor_class'] = 'VisionSensor MU(Serial, 115200);';
    Blockly.Arduino.setups_['mu_setup_initialize'] = 'MU.begin();';  
    var code = 'MU.valid()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.coolguy_mu_detected = function() {
    Blockly.Arduino.definitions_['define_VisionSensor'] = '#include "VisionSensor.h"';
    Blockly.Arduino.definitions_['define_VisionSensor_class'] = 'VisionSensor MU(Serial, 115200);';
    var code = 'MU.detected()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.coolguy_mu_getx = function() {
    Blockly.Arduino.definitions_['define_VisionSensor'] = '#include "VisionSensor.h"';
    Blockly.Arduino.definitions_['define_VisionSensor_class'] = 'VisionSensor MU(Serial, 115200);';
    var code = 'MU.getX()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.coolguy_mu_gety = function() {
    Blockly.Arduino.definitions_['define_VisionSensor'] = '#include "VisionSensor.h"';
    Blockly.Arduino.definitions_['define_VisionSensor_class'] = 'VisionSensor MU(Serial, 115200);';
    var code = 'MU.getY()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.coolguy_mu_getwidth = function() {
    Blockly.Arduino.definitions_['define_VisionSensor'] = '#include "VisionSensor.h"';
    Blockly.Arduino.definitions_['define_VisionSensor_class'] = 'VisionSensor MU(Serial, 115200);';
    var code = 'MU.getWidth()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.coolguy_mu_getheight = function() {
    Blockly.Arduino.definitions_['define_VisionSensor'] = '#include "VisionSensor.h"';
    Blockly.Arduino.definitions_['define_VisionSensor_class'] = 'VisionSensor MU(Serial, 115200);';
    var code = 'MU.getHeight()';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};