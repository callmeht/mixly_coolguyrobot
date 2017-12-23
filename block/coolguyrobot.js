'use strict';

goog.provide('Blockly.Blocks.coolguyrobot');

goog.require('Blockly.Blocks');


Blockly.Blocks.coolguyrobot.HUE = 20;

var COOLGUY_MS=[["M1", "1"],["M2", "2"]];
var COOLGUY_OLEDROW=[["1","1"],["2","2"],["3","3"],["4","4"]];
var COOLGUY_OLEDLINE=[["1","1"],["2","2"],["3","3"],["4","4"],["5","5"],["6","6"],["7","7"],["8","8"],["9","9"],["10","10"],["11","11"],["12","12"],["13","13"],["14","14"],["15","15"],["16","16"]];
var COOLGUY_ALL_INPUT=[["IO2", "2"],["IO3", "3"],["IO4", "4"],["IO7", "7"],["IO8", "8"],["IO9", "9"],["IO12", "12"],["IO13", "13"],["A0", "A0"],["A2", "A2"],["A4", "A4"]];
var COOLGUY_ANALOG_INPUT=[["A0", "A0"],["A2", "A2"],["A4", "A4"]];
var COOLGUY_DIGITAL_INPUT=[["IO2", "2"],["IO3", "3"],["IO4", "4"],["IO7", "7"],["IO8", "8"],["IO9", "9"],["IO12", "12"],["IO13", "13"]];



/*                     其他串口模块                      */
/*设定比较内容*/
Blockly.Blocks.coolguy_serial_content_set = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_SIRIEL1);
    this.appendDummyInput("")
    this.appendValueInput('TEXT3')
        .setCheck(String);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*比较内容完全相同*/
Blockly.Blocks.coolguy_serial_content_compare_allsame= {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_SIRIEL2);
    this.appendDummyInput("")
    this.appendValueInput('TEXT3')
        .setCheck(String);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*比较内容包含*/
Blockly.Blocks.coolguy_serial_content_compare_include = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_SIRIEL3);
    this.appendDummyInput("")
    this.appendValueInput('TEXT3')
        .setCheck(String);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};/*                     其他串口模块结束                   */

/*                       循线模块                          */
/*设置五灰度比较值*/
Blockly.Blocks.coolguy_line_cmp_valueset =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE_SET);
    this.appendValueInput("num1", Number)
        .setCheck(Number);
    this.appendValueInput('num2')
        .setCheck(Number);
    this.appendValueInput('num3')
        .setCheck(Number);
    this.appendValueInput('num4')
        .setCheck(Number);
    this.appendValueInput('num5')
        .setCheck(Number);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};


/*设置五灰度端口*/
Blockly.Blocks.coolguy_line_portset =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE_PORT)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*路口过冲设定*/
Blockly.Blocks.coolguy_line_crossroad =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE1_1);
    this.appendValueInput('num1')
        .setCheck(Number);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE1_2);
    this.appendValueInput('num2')
        .setCheck(Number);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE1_3);
    this.appendValueInput('num3')
        .setCheck(Number);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE1_4);           
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*巡线时间设定*/
Blockly.Blocks.coolguy_line_time =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE1_1);
    this.appendValueInput('num1')
        .setCheck(Number);
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_LINE2_2);
    this.appendValueInput('num2')
        .setCheck(Number);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE2_3);      
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*左转弯设定*/
Blockly.Blocks.coolguy_line_turnleft =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE1_1);
    this.appendValueInput('num1')
        .setCheck(Number);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE3_2);
    this.appendValueInput('num2')
        .setCheck(Number);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE3_3);      
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*右转弯设定*/
Blockly.Blocks.coolguy_line_turnright =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE1_1);
    this.appendValueInput('num1')
        .setCheck(Number);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE4_2);
    this.appendValueInput('num2')
        .setCheck(Number);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE3_3);      
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*选择五灰度传感器*/
var COOLGUY_LINE_SENSOR=[["1","1"],["2","2"],["3","3"],["4","4"],["5","5"]];
Blockly.Blocks.coolguy_line_sensorchoose =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE5)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_LINE_SENSOR), "PIN");
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};/*                       循线模块结束                          */

/*                      超声波模块                             */
/*一体超声波 置于五灰度传感器上 无需设置端口*/
Blockly.Blocks.coolguy_ultrasonic_already = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_ULTRASONIC_ALREAGY);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*读扩展超声波距离*/
Blockly.Blocks.coolguy_ultrasonic_setup = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_ULTRASONIC_SETUP)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ANALOG_INPUT), "PIN");
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};/*                      超声波模块结束                          */

/*                      红外遥控器模块                          */
/*红外遥控器 遥控通道(1~8）  （无、上、下、左、右、上+B、下+B、左+B、右+B）键按下 引脚（IO2、IO3）*/
var COOLGUY_REMOTECONTROL_CHANNAL=[["1", "1"],["2", "2"],["3", "3"],["4", "4"],["5", "5"],["6", "6"],["7", "7"],["8", "8"]];
var COOLGUY_REMOTECONTROL_KEY=[["无", "0"],["上", "1"],["下", "2"],["左", "3"],["右", "4"],["上+B", "5"],["下+B", "6"],["左+B", "7"],["右+B", "8"]];
var COOLGUY_REMOTECONTROL_PORT=[["IO2", "2"],["IO3", "3"]];
Blockly.Blocks.coolguy_remotecontrol = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_REMOTECONTROL_CHANNAL)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_REMOTECONTROL_CHANNAL), "PIN1");
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_BLANK)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_REMOTECONTROL_KEY), "PIN2")
        .appendTitle(Blockly.MIXLY_COOLGUY_REMOTECONTROL_KEY);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PIN)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_REMOTECONTROL_PORT), "PIN3");
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};/*                      红外遥控器模块结束                          */

/*                    其他传感器模块                     */
/*设置录音模块端口模块*/
Blockly.Blocks.coolguy_record_portsetup =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_record_setup)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*开始录音*/
Blockly.Blocks.coolguy_record_start = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_record1);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*停止录音*/
Blockly.Blocks.coolguy_record_stop = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_record2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*播放录音*/
Blockly.Blocks.coolguy_record_play = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_record3);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*温度传感器模块*/
Blockly.Blocks.coolguy_temp_get = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_TEMP_SETUP)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN");
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};


/*空气质量检测模块*/
Blockly.Blocks.coolguy_airquality = {
  init: function() {
    //this.setColour(COLOR_AIR);
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_AIRQUALITY)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ANALOG_INPUT), "PIN");
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*声音传感器*/
Blockly.Blocks.coolguy_sensor_sound = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
    this.appendDummyInput("")
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
        .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_SOUND);
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setOutput(true, Number);//左端接口伸出，false为不伸出
   /* this.setTooltip(Blockly.MIXLY_COOLGUY_TEMP1_TOOLTIP);//说明文字
    this.setPreviousStatement(true, null);//设置为上可接
    this.setNextStatement(true, null);//设置为下可接*/
  }
};

/*红外测距传感器*/
Blockly.Blocks.coolguy_sensor_irranging = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
    this.appendDummyInput("")
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
        .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_IRRANGING);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*光敏传感器*/
Blockly.Blocks.coolguy_sensor_photo = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
    this.appendDummyInput("")
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
        .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_PHOTO);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*按键传感器*/
Blockly.Blocks.coolguy_sensor_switch = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
    this.appendDummyInput("")
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
        .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_SWITCH);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*火焰传感器*/
Blockly.Blocks.coolguy_sensor_fire = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
    this.appendDummyInput("")
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
        .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_FIRE);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*震动传感器*/
Blockly.Blocks.coolguy_sensor_shock = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
    this.appendDummyInput("")
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
        .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_SHOCK);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*触摸开关*/
Blockly.Blocks.coolguy_sensor_touch = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
    this.appendDummyInput("")
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
        .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_TOUCH);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};/*                    其他传感器模块结束                     */

/*                       电机模块                             */
/*左电机*/
Blockly.Blocks.coolguy_motor_left =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_MOTOR_LEFT);
    this.appendValueInput('num')
        .setCheck(Number);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*右电机*/
Blockly.Blocks.coolguy_motor_right =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_MOTOR_RIGHT);
    this.appendValueInput('num')
        .setCheck(Number);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};/*                       电机模块结束                             */

/*                      LED/OLED模块                        */
/*oled显示英文字符串*/
Blockly.Blocks.coolguy_oled_English = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_OLED);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_ROW)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_OLEDROW), "PIN1");
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_LINE)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_OLEDLINE), "PIN2");
    this.appendDummyInput("")
        .appendField(Blockly.MIXLY_OLEDSHOW); 
    this.appendValueInput('TEXT3')
        .setCheck(String);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*oled显示数字*/
Blockly.Blocks.coolguy_oled_number = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_OLED);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_ROW)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_OLEDROW), "PIN1");
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_LINE)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_OLEDLINE), "PIN2");
    this.appendValueInput('num')
        .setCheck(Number)
        .appendTitle(Blockly.MIXLY_OLEDSHOWNUM);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*oled清屏*/
Blockly.Blocks.coolguy_oled_clear = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_OLED3);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*数码管显示数字*/
Blockly.Blocks.coolguy_Nixietube = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_Nixietube);
    this.appendValueInput('num')
        .setCheck(Number);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_PORT)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ANALOG_INPUT), "PIN");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*LED灯*/
var COOLGUY_LED_STATUS=[["开启", "0"],["关闭", "1"]];
Blockly.Blocks.coolguy_led= {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_LED_STATUS), "PIN1");
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LEDMO)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN2");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};/*                      LED/OLED模块结束                        */

/*                      系统模块                             */
/*读模拟引脚*/
Blockly.Blocks.coolguy_analog_reading =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_ANALOG_READING)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_ANALOG_INPUT), "PIN");
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*读数字引脚*/
Blockly.Blocks.coolguy_digital_reading =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_DIGITAL_READING)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_DIGITAL_INPUT), "PIN");
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
};

/*设置PWM端口和输出*/
var COOLGUY_PWM_OUTPUT=[["IO5", "5"],["IO6", "6"],["IO10", "10"],["IO11", "11"]];
var COOLGUY_PWM_CHOOSE=[["0", "0"],["50", "50"],["100", "100"],["150", "150"],["200", "200"],["255", "255"]];
Blockly.Blocks.coolguy_pwm =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PWM_01)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_PWM_OUTPUT), "PIN");
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_PWM_02)
        .appendTitle(new Blockly.FieldDropdown(COOLGUY_PWM_CHOOSE), "PWM_NUM");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

/*计时器（毫秒为单位）*/
Blockly.Blocks.coolguy_timer =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_TIMER);
    this.setInputsInline(true);
    this.setOutput(true, Number);
  }
}; 

/*部分数字端口设为输出*/
Blockly.Blocks.coolguy_allportinitial = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_ALLPORTINITIAL);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};/*                      系统模块结束                             */