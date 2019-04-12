'use strict';

goog.provide('Blockly.Arduino.MotorDriverBoard');

goog.require('Blockly.Arduino');

//将第0个图形块转化为C语言 Hummerbot初始化
Blockly.Arduino.md_setup = function() {
 //Blockly.Arduino.definitions_['define_Arduino'] = '#include<Arduino.h>'; 
 //Blockly.Arduino.definitions_['define_wire'] = '#include<wire.h>'; 
 //Blockly.Arduino.definitions_['define_SoftwareSerial'] = '#include<SoftwareSerial.h>'; 
 //Blockly.Arduino.definitions_['define_ProtocolParser'] = '#include<ProtocolParser.h>'; 
 //Blockly.Arduino.definitions_['define_BluetoothHandle'] = '#include<BluetoothHandle.h>'; 
 //Blockly.Arduino.definitions_['define_KeyMap'] = '#include<KeyMap.h>'; 
// Blockly.Arduino.definitions_['define_debug'] = '#include<debug.h>'; 
 Blockly.Arduino.definitions_['define_Emakefun_MotorDriver'] = '#include<Emakefun_MotorDriver.h>';
 Blockly.Arduino.definitions_['object0'] = 'Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();\n'
 Blockly.Arduino.setups_['setup_md_setup1'] ='\t'+'Serial.begin(9600);\n'
                                        
 var code = '';
 return code;
};
//将第一个图形块转化为C语言 直流电机下拉（下拉没有value），正反转（下拉），速度（输入,有value）
Blockly.Arduino.md_dcmotor = function() {
 var dropdown_DCPorts = this.getFieldValue('DCPorts');
 var dropdown_DCDirections = this.getFieldValue('DCDirections');
   var value_Speed = Blockly.Arduino.valueToCode(this,'Speed',Blockly.Arduino.ORDER_ATOMIC);
 Blockly.Arduino.definitions_['object'+dropdown_DCPorts+''] = 'Emakefun_DCMotor *DCmotor_'+dropdown_DCPorts+' = mMotorDriver.getMotor('+dropdown_DCPorts+');\n'
 Blockly.Arduino.setups_['setup_md_setup2'] ='\t'+'mMotorDriver.begin(50);\n'

 var code = ' DCmotor_'+dropdown_DCPorts+'->setSpeed('+value_Speed+');\n'
 			+'DCmotor_'+dropdown_DCPorts+'->run('+dropdown_DCDirections+');\n';
return code;
};
//将第二个图形块转化为C语言 停止直流电机 下拉（下拉没有value）
Blockly.Arduino.md_stopDCmotor = function(){
 var dropdown_DCPorts = this.getFieldValue('DCPorts');
 var code = 'DCmotor_'+dropdown_DCPorts+'->run(RELEASE);\n'
 return code;
};
//将第三个图形块转化为C语言 编码电机下拉（下拉没有value），正反转（下拉），速度（输入,有value）
 Blockly.Arduino.md_enmotor = function() {
 var dropdown_ENPorts = this.getFieldValue('ENPorts');
 var dropdown_ENDirections = this.getFieldValue('ENDirections');
   var value_Speed = Blockly.Arduino.valueToCode(this,'Speed',Blockly.Arduino.ORDER_ATOMIC);
 Blockly.Arduino.definitions_['object'+dropdown_ENPorts+''] = 'Emakefun_EncoderMotor *encodermotor_'+dropdown_ENPorts+' = mMotorDriver.getEncoderMotor('+dropdown_ENPorts+');\n'
 Blockly.Arduino.setups_['setup_md_setup3'] ='\t'+'mMotorDriver.begin(50);\n'

 var code = ' encodermotor_'+dropdown_ENPorts+'->setSpeed('+value_Speed+');\n'
 			+'encodermotor_'+dropdown_ENPorts+'->run('+dropdown_ENDirections+');\n';
return code;
};
//将第四个图形块转化为C语言 停止编码电机 下拉（下拉没有value）
Blockly.Arduino.md_stopENmotor = function(){
 var dropdown_ENPorts = this.getFieldValue('ENPorts');
 var code = 'encodermotor_'+dropdown_ENPorts+'->run(RELEASE);\n'
 return code;
};
//将第五个图形块转化为C语言 步进电机下拉，步数value，方向下拉，方式下拉
Blockly.Arduino.md_stmotor = function(){
 var dropdown_STPorts = this.getFieldValue('STPorts');
 var dropdown_STDirections = this.getFieldValue('STDirections');
  var dropdown_STStyles = this.getFieldValue('STStyles');
 var value_Steps = Blockly.Arduino.valueToCode(this,'Steps',Blockly.Arduino.ORDER_ATOMIC);
  Blockly.Arduino.setups_['setup_md_setup7'] ='\t'+'mMotorDriver.begin(50);\n'
  Blockly.Arduino.definitions_['object'+dropdown_STPorts+''] = 'Emakefun_StepperMotor *steppermotor_'+dropdown_STPorts+' = mMotorDriver.getStepper('+value_Steps+','+dropdown_STPorts+');\n'
 var code = ' steppermotor_'+dropdown_STPorts+'->step('+value_Steps+','+dropdown_STDirections+','+dropdown_STStyles+');\n';
 return code;
};
//将第六个图形块转化为C语言 设置RGB灯颜色（下拉，红，绿，蓝，黄，紫，白，黑）
Blockly.Arduino.md_RGB = function(){
	var dropdown_RGB = this.getFieldValue('RGB');
	var dropdown_RGBCOLOR = this.getFieldValue('RGBCOLOR');
	 Blockly.Arduino.definitions_['object5'] = 'Emakefun_Sensor *rgb = mMotorDriver.getSensor(E_RGB);\n'
 var code = 'rgb->SetRgbColor((E_RGB_INDEX)'+dropdown_RGB+', '+dropdown_RGBCOLOR+');\n';
 return code;
};
//将第七个图形块转化为C语言 播放声音 下拉
Blockly.Arduino.md_playSounds = function(){
	var dropdown_Sounds = this.getFieldValue('Sounds');
	Blockly.Arduino.definitions_['object6'] = 'Emakefun_Sensor *buzzer = mMotorDriver.getSensor(E_BUZZER);\n'
 var code = 'buzzer->Sing('+dropdown_Sounds+');\n';
 return code;
};
//将第八个图形块转化为C语言 超声波初始化
Blockly.Arduino.md_initultrasonic = function(){
 Blockly.Arduino.definitions_['object7'] = 'Emakefun_Sensor *ultrasonic = mMotorDriver.getSensor(E_ULTRASONIC);\n'
 var code = '';
 return code;
};
//将第九个图形块转化为C语言 读取超声波距离
Blockly.Arduino.md_readUltrasonicDistance = function(){
 
 var code = 'ultrasonic->GetUltrasonicDistance()';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; //当code为表达式时用此返回方式
};
//将第十个图形块转化为C语言 红外接收初始化
Blockly.Arduino.md_initirremote = function(){
	Blockly.Arduino.definitions_['define_KeyMap'] = '#include<KeyMap.h>'; 
	Blockly.Arduino.definitions_['object8'] = 'Emakefun_Sensor *ir = mMotorDriver.getSensor(E_IR);\n'
  var code = '';
 return code;
};
//将第十一个图形块转化为C语言 红外遥控按键（下拉，返回boolean）
Blockly.Arduino.md_irKeyPress = function(){
	var dropdown_Irkeys = this.getFieldValue('Irkeys');
Blockly.Arduino.definitions_['object9'] = 'byte irKeyCode;\n'
 var code = '(E_IR_KEYCODE)ir->mIrRecv->getIrKey(ir->mIrRecv->getCode()) == '+dropdown_Irkeys+'';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};

//将第十二个图形块转化为C语言 NRF24L01初始化    field的name不确定使NUM待检测
Blockly.Arduino.md_initnrf24l01 = function(){
	Blockly.Arduino.definitions_['object10'] = 'Emakefun_Sensor *nrf24l01= mMotorDriver.getSensor(E_NRF24L01);\n'
  var code = '';
 return code;
};
//将第十三个图形块转化为C语言 NRF24L01发送数据地址value 数据value
Blockly.Arduino.md_nrf24l01send = function(){
 var value_address = Blockly.Arduino.valueToCode(this,'address',Blockly.Arduino.ORDER_ATOMIC);
var value_data = Blockly.Arduino.valueToCode(this,'data',Blockly.Arduino.ORDER_ATOMIC);
 
 var code = 'nrf24l01->sendNrf24l01((char *)\"'+value_address+'\",'+value_data+');\n';
 return code;
};
//将第十四个图形块转化为C语言 NRF24L01接收数据地址value
Blockly.Arduino.md_nrf24l01receive = function(){
  var value_address = Blockly.Arduino.valueToCode(this,'address',Blockly.Arduino.ORDER_ATOMIC);
 var code = 'int NrfData;\nNrfData = nrf24l01->GetNrf24L01((char *)\"'+value_address+'");\n';
  return code; //当code为表达式时用此返回方式
};
//将第十五个图形块转化为C语言 NRF24L01数据不为空
Blockly.Arduino.md_NRF24L01isnotnull = function(){
 var code = 'NrfData != NULL';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第十六个图形块转化为C语言 获取NRF24L01数据
Blockly.Arduino.md_getNRF24L01 = function(){																											
 var code = 'NrfData';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第十七个图形块转化为C语言 PS2手柄初始化
Blockly.Arduino.md_PS2init = function(){
	Blockly.Arduino.definitions_['object10'] = 'Emakefun_Sensor *ps2x = mMotorDriver.getSensor(E_PS2X);\n'
 var code = 'static int vibrate = 0;\nbyte PSS_X = 0,PSS_Y = 0;\nps2x->mPs2x->read_gamepad(false, vibrate);\n';
 return code;
};
//将第十八个图形块转化为C语言 PS2键被按下（下拉）
Blockly.Arduino.md_WhichPS2KeyPressed = function(){
 var code = 'ps2x->mPs2x->ButtonDataByte()';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第十九个图形块转化为C语言 设置PS2摇杆震动值
Blockly.Arduino.md_setps2vibrate = function(){
var code = ' vibrate = ps2x->mPs2x->Analog(PSAB_CROSS);\n';
return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第二十个图形块转化为C语言 ps2手柄按下 下拉无value
Blockly.Arduino.md_ps2keypress = function(){
 var dropdown_PS2keys = this.getFieldValue('PS2keys');
 var code = 'ps2x->mPs2x->Button('+dropdown_PS2keys+')';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第二十一个图形块转化为C语言 ps2手柄松开 下拉无value
Blockly.Arduino.md_ps2keyunpress = function(){
	 var dropdown_PS2keys = this.getFieldValue('PS2keys');
	  var code = 'ps2x->mPs2x->ButtonReleased('+dropdown_PS2keys+')';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};
//将第二十二个图形块转化为C语言 获取摇杆值（下拉）
Blockly.Arduino.md_ps2getvibrate = function(){
 var dropdown_Vibrate = this.getFieldValue('Vibrate');
 var code = 'ps2x->Analog('+dropdown_Vibrate+')';
 return [code, Blockly.Arduino.ORDER_ATOMIC]; 
};

//将第二十三个图形块转化为C语言 读取ps2状态
Blockly.Arduino.md_ps2status = function(){
 var code = 'ps2x.read_gamepad(false, 0);\n';
 return code;
};
//将第二十四个图形块转化为C语言 舵机 接口下拉  角度value
Blockly.Arduino.md_servo = function(){
	var dropdown_Servoports = this.getFieldValue('Servoports');
	var value_angle = Blockly.Arduino.valueToCode(this,'angle',Blockly.Arduino.ORDER_ATOMIC);
	Blockly.Arduino.setups_['setup_md_setup5'] ='\t'+'mMotorDriver.begin(50);\n'
	Blockly.Arduino.definitions_['object11'] = 'Emakefun_Servo *servo'+dropdown_Servoports+' = mMotorDriver.getServo('+dropdown_Servoports+');\n'
 var code = ' servo'+dropdown_Servoports+'->writeServo('+value_angle+');\n';
 return code;
};