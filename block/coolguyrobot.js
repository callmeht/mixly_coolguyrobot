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




/////////////////////////////传感器模块/////////////////////////////////////////////////
/////////////////////////////传感器模块/////////////////////////////////////////////////
/////////////////////////////传感器模块/////////////////////////////////////////////////
/////////////////////////////传感器模块/////////////////////////////////////////////////
////声音传感器
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
//    this.setTooltip(Blockly.MIXLY_COOLGUY_TEMP1_TOOLTIP);//说明文字
  //this.setPreviousStatement(true, null);//设置为上可接
 // this.setNextStatement(true, null);//设置为下可接
  }
};

///////红外测距传感器
Blockly.Blocks.coolguy_sensor_irranging = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
      .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
         this.appendDummyInput("")
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
               .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_IRRANGING);
      this.setInputsInline(true);//设置为同一行，false为换行
    this.setOutput(true, Number);//左端接口伸出，false为不伸出
//    this.setTooltip(Blockly.MIXLY_COOLGUY_TEMP1_TOOLTIP);//说明文字
  //this.setPreviousStatement(true, null);//设置为上可接
 // this.setNextStatement(true, null);//设置为下可接
  }
};

//光敏传感器
Blockly.Blocks.coolguy_sensor_photo = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
      .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
         this.appendDummyInput("")
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
               .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_PHOTO);
      this.setInputsInline(true);//设置为同一行，false为换行
    this.setOutput(true, Number);//左端接口伸出，false为不伸出
//    this.setTooltip(Blockly.MIXLY_COOLGUY_TEMP1_TOOLTIP);//说明文字
  //this.setPreviousStatement(true, null);//设置为上可接
 // this.setNextStatement(true, null);//设置为下可接
  }
};

//按键传感器
Blockly.Blocks.coolguy_sensor_switch = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
      .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
         this.appendDummyInput("")
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
               .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_SWITCH);
      this.setInputsInline(true);//设置为同一行，false为换行
    this.setOutput(true, Number);//左端接口伸出，false为不伸出
//    this.setTooltip(Blockly.MIXLY_COOLGUY_TEMP1_TOOLTIP);//说明文字
  //this.setPreviousStatement(true, null);//设置为上可接
 // this.setNextStatement(true, null);//设置为下可接
  }
};

//火焰传感器
Blockly.Blocks.coolguy_sensor_fire = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
      .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
         this.appendDummyInput("")
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
               .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_FIRE);
      this.setInputsInline(true);//设置为同一行，false为换行
    this.setOutput(true, Number);//左端接口伸出，false为不伸出
//    this.setTooltip(Blockly.MIXLY_COOLGUY_TEMP1_TOOLTIP);//说明文字
  //this.setPreviousStatement(true, null);//设置为上可接
 // this.setNextStatement(true, null);//设置为下可接
  }
};

//震动传感器
Blockly.Blocks.coolguy_sensor_shock = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
      .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
         this.appendDummyInput("")
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
               .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_SHOCK);
      this.setInputsInline(true);//设置为同一行，false为换行
    this.setOutput(true, Number);//左端接口伸出，false为不伸出
//    this.setTooltip(Blockly.MIXLY_COOLGUY_TEMP1_TOOLTIP);//说明文字
  //this.setPreviousStatement(true, null);//设置为上可接
 // this.setNextStatement(true, null);//设置为下可接
  }
};

//触摸开关
Blockly.Blocks.coolguy_sensor_touch = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
      .appendTitle(Blockly.MIXLY_COOLGUY_PIN);
         this.appendDummyInput("")
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN")
               .appendTitle(Blockly.MIXLY_COOLGUY_SENSOR_TOUCH);
      this.setInputsInline(true);//设置为同一行，false为换行
    this.setOutput(true, Number);//左端接口伸出，false为不伸出
//    this.setTooltip(Blockly.MIXLY_COOLGUY_TEMP1_TOOLTIP);//说明文字
  //this.setPreviousStatement(true, null);//设置为上可接
 // this.setNextStatement(true, null);//设置为下可接
  }
};

Blockly.Blocks.coolguy_oled1 = {
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
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};


////////////显示数字//////////////////////////
Blockly.Blocks.coolguy_oled2 = {
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
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};
Blockly.Blocks.coolguy_oled3 = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_OLED3);
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};
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
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

Blockly.Blocks.coolguy_ultrasonic = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
      .appendTitle(Blockly.MIXLY_COOLGUY_ULTRASONIC);
         this.appendDummyInput("")
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_ANALOG_INPUT), "PIN");

      this.setInputsInline(true);//设置为同一行，false为换行
    this.setOutput(true, Number);//左端接口伸出，false为不伸出
//    this.setTooltip(Blockly.MIXLY_COOLGUY_TEMP1_TOOLTIP);//说明文字
  //this.setPreviousStatement(true, null);//设置为上可接
 // this.setNextStatement(true, null);//设置为下可接
  }
};


////红外遥控器 遥控通道1~8  ？键按下（上、下、左、右、上+B、下+B、左+B、右+B）引脚IO2IO3选择。
var COOLGUY_REMOTECONTROL_CHANNAL=[["1", "1"],["2", "2"],["3", "3"],["4", "4"],["5", "5"],["6", "6"],["7", "7"],["8", "8"]];
var COOLGUY_REMOTECONTROL_KEY=[["无", "0"],["上", "1"],["下", "2"],["左", "3"],["右", "4"],["上+B", "5"],["下+B", "6"],["左+B", "7"],["右+B", "8"]];
var COOLGUY_REMOTECONTROL_INPUT=[["IO2", "2"],["IO3", "3"]];
Blockly.Blocks.coolguy_remotecontrol = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_REMOTECONTROL_CHANNAL)
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_REMOTECONTROL_CHANNAL), "PIN1");
    this.appendDummyInput("")
      .appendTitle(Blockly.MIXLY_COOLGUY_KONGGE)
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_REMOTECONTROL_KEY), "PIN2")
                  .appendTitle(Blockly.MIXLY_COOLGUY_REMOTECONTROL_KEY);
    this.appendDummyInput("")
                  .appendTitle(Blockly.MIXLY_COOLGUY_PIN)
                    .appendTitle(new Blockly.FieldDropdown(COOLGUY_REMOTECONTROL_INPUT), "PIN3");
    this.setInputsInline(true);//设置为同一行，false为换行
        this.setOutput(true, Number);//左端接口伸出，false为不伸出
  //  this.setPreviousStatement(true, null);
   // this.setNextStatement(true, null);
  }
};

/////LED灯  ON/OFF LED灯在引脚var COOLGUY_ANALOG_INPUT=[["A0", "A0"],["A2", "A2"],["A4", "A4"]];
var COOLGUY_LED_STATUS=[["开启", "0"],["关闭", "1"]];
Blockly.Blocks.coolguy_ledmo = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_LED_STATUS), "PIN1");
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_LEDMO)
         .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN2");
    this.setInputsInline(true);//设置为同一行，false为换行
      //  this.setOutput(true, Number);//左端接口伸出，false为不伸出
    this.setPreviousStatement(true, null);//设置为上可接
   this.setNextStatement(true, null);//设置为下可接
  }
};

//////超声波模块 
//var COLOR_ULTRASONIC=60;
/////读一体超声波距离（注：在五灰度已设置端口）coolguy_ultrasonic_already
Blockly.Blocks.coolguy_ultrasonic_already = {
  init: function() {
    //this.setColour(COLOR_ULTRASONIC);
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_ULTRASONIC_ALREAGY);
    this.setInputsInline(true);//设置为同一行，false为换行
      this.setOutput(true, Number);//左端接口伸出，false为不伸出
   //  this.setPreviousStatement(true, null);//设置为上可接
   // this.setNextStatement(true, null);//设置为下可接
  }
};
///////读扩展超声波距离在引脚COOLGUY_ANALOG_INPUT
Blockly.Blocks.coolguy_ultrasonic_setup = {
  init: function() {
    //this.setColour(COLOR_ULTRASONIC);
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_ULTRASONIC_SETUP)
       .appendTitle(new Blockly.FieldDropdown(COOLGUY_ANALOG_INPUT), "PIN");
    this.setInputsInline(true);//设置为同一行，false为换行
      this.setOutput(true, Number);//左端接口伸出，false为不伸出
   //  this.setPreviousStatement(true, null);//设置为上可接
   // this.setNextStatement(true, null);//设置为下可接
  }
};

//var COLOR_TEMP=80;
/////温度传感器模块////////读温度值在引脚COOLGUY_ANALOG_INPUT/////coolguy_temp_setup
Blockly.Blocks.coolguy_temp_setup = {
  init: function() {
    //this.setColour(COLOR_TEMP);
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_TEMP_SETUP)
       .appendTitle(new Blockly.FieldDropdown(COOLGUY_ANALOG_INPUT), "PIN");
    this.setInputsInline(true);//设置为同一行，false为换行
      this.setOutput(true, Number);//左端接口伸出，false为不伸出
   //  this.setPreviousStatement(true, null);//设置为上可接
   // this.setNextStatement(true, null);//设置为下可接
  }
};

//var COLOR_AIR=80;
/////空气质量模块////////读空气质量在引脚COOLGUY_ANALOG_INPUT/////coolguy_airquality
Blockly.Blocks.coolguy_airquality = {
  init: function() {
    //this.setColour(COLOR_AIR);
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_AIRQUALITY)
       .appendTitle(new Blockly.FieldDropdown(COOLGUY_ANALOG_INPUT), "PIN");
    this.setInputsInline(true);//设置为同一行，false为换行
      this.setOutput(true, Number);//左端接口伸出，false为不伸出
   //  this.setPreviousStatement(true, null);//设置为上可接
   // this.setNextStatement(true, null);//设置为下可接
  }
};

////电机模块//////
/////左电机数字为int类型，若超过-256~255，只取低十六位////
Blockly.Blocks.coolguy_motor_left =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_MOTOR_LEFT);
        this.appendValueInput('num')
         .setCheck(Number);
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};
/////右电机数字为int类型，若超过-256~255，只取低十六位////
Blockly.Blocks.coolguy_motor_right =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_MOTOR_RIGHT);
        this.appendValueInput('num')
         .setCheck(Number);
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};



///////////循线模块/////////
///////设置五灰度比较从左到右/////
Blockly.Blocks.coolguy_line_set =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE_SET);
    // this.appendDummyInput()
    //     .appendField(new Blockly.FieldTextInput('0', Blockly.FieldTextInput.math_number_validator), 'NUM');
        // this.setOutput(true, Number);
          this.appendValueInput("num1", Number)
        // .appendTitle(Blockly.LUXE_SPEED) // 这个显示在STAT表示的数值后面
        .setCheck(Number);
        // this.appendValueInput('num1')
        //  .setCheck(Number);
        this.appendValueInput('num2')
         .setCheck(Number);
        this.appendValueInput('num3')
         .setCheck(Number);
        this.appendValueInput('num4')
         .setCheck(Number);
        this.appendValueInput('num5')
         .setCheck(Number);
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

    // this.appendDummyInput()
    //     .appendField(new Blockly.FieldTextInput('0',
    //     Blockly.FieldTextInput.math_number_validator), 'NUM');
    // this.setOutput(true, Number);
//////设置五灰度端口
Blockly.Blocks.coolguy_line_port =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_LINE_PORT)
               .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN");
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

//////转速？寻？路口后冲？秒///////coolguy_line1
Blockly.Blocks.coolguy_line1 =  {
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
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

//////转速？循线？秒后停止coolguy_line2
Blockly.Blocks.coolguy_line2 =  {
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
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};
//////转速？左转弯？线coolguy_line3
Blockly.Blocks.coolguy_line3 =  {
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
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};
//////转速？右转弯？线coolguy_line4
Blockly.Blocks.coolguy_line4 =  {
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
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

var COOLGUY_LINE_5=[["1","1"],["2","2"],["3","3"],["4","4"],["5","5"]];
Blockly.Blocks.coolguy_line5 =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_LINE5)
              .appendTitle(new Blockly.FieldDropdown(COOLGUY_LINE_5), "PIN");
    this.setInputsInline(true);//设置为同一行，false为换行
      this.setOutput(true, Number);//左端接口伸出，false为不伸出
  }
};



///////系统接口//////
Blockly.Blocks.coolguy_analog_reading =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_ANALOG_READING)
              .appendTitle(new Blockly.FieldDropdown(COOLGUY_ANALOG_INPUT), "PIN");
    this.setInputsInline(true);//设置为同一行，false为换行
      this.setOutput(true, Number);//左端接口伸出，false为不伸出
  }
};
Blockly.Blocks.coolguy_digital_reading =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_DIGITAL_READING)
              .appendTitle(new Blockly.FieldDropdown(COOLGUY_DIGITAL_INPUT), "PIN");
    this.setInputsInline(true);//设置为同一行，false为换行
      this.setOutput(true, Number);//左端接口伸出，false为不伸出
  }
};
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
    this.setInputsInline(true);//设置为同一行，false为换行
         // this.setOutput(true, Number);//左端接口伸出，false为不伸出
           this.setPreviousStatement(true, null);//设置为上可接
           this.setNextStatement(true, null);//设置为下可接
  }
};

// /////////////TIMER//////////////////////////millis()/1000.0
Blockly.Blocks.coolguy_timer =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
       .appendTitle(Blockly.MIXLY_COOLGUY_TIMER);
    this.setInputsInline(true);//设置为同一行，false为换行
         this.setOutput(true, Number);//左端接口伸出，false为不伸出
           // this.setPreviousStatement(true, null);//设置为上可接
           // this.setNextStatement(true, null);//设置为下可接
  }
}; 

Blockly.Blocks.coolguy_serial1 = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_SIRIEL1);
         this.appendDummyInput("")
          this.appendValueInput('TEXT3')
          .setCheck(String);
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};
Blockly.Blocks.coolguy_serial2 = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_SIRIEL2);
         this.appendDummyInput("")
          this.appendValueInput('TEXT3')
          .setCheck(String);
    this.setInputsInline(true);//设置为同一行，false为换行
      this.setOutput(true, Number);//左端接口伸出，false为不伸出
           // this.setPreviousStatement(true, null);//设置为上可接
           // this.setNextStatement(true, null);//设置为下可接
  }
};
Blockly.Blocks.coolguy_serial3 = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_COOLGUY_SIRIEL3);
         this.appendDummyInput("")
          this.appendValueInput('TEXT3')
          .setCheck(String);
    this.setInputsInline(true);//设置为同一行，false为换行
      this.setOutput(true, Number);//左端接口伸出，false为不伸出
           // this.setPreviousStatement(true, null);//设置为上可接
           // this.setNextStatement(true, null);//设置为下可接
  }
};

Blockly.Blocks.coolguy_record_setup =  {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_record_setup)
               .appendTitle(new Blockly.FieldDropdown(COOLGUY_ALL_INPUT), "PIN");
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};
Blockly.Blocks.coolguy_record1 = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_record1);
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};
Blockly.Blocks.coolguy_record2 = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_record2);
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};
Blockly.Blocks.coolguy_record3 = {
  init: function() {
    this.setColour(Blockly.Blocks.coolguyrobot.HUE);
    this.appendDummyInput("")
        .appendTitle(Blockly.MIXLY_record3);
    this.setInputsInline(true);//设置为同一行，false为换行
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};