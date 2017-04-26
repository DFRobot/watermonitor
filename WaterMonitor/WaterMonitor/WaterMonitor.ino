/*********************************************************************
* WaterMonitor.ino
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:
* This sample code is mainly used to monitor water quality
* including ph, temperature, dissolved oxygen, ec and orp,etc.
* 
* Software Environment: Arduino IDE 1.8.2 
* Software download link: https://www.arduino.cc/en/Main/Software
*
* Hardware platform   : Arduino M0, Arduino Mega2560
*
* author  :  Jason
* version :  V1.0
* date    :  2017-04-06
**********************************************************************/

#include <Arduino.h>
#include "GravitySensorHub.h"
#include <stdlib.h>
#include "GravityRtc.h"
#include "OneWire.h"



//温度传感器引脚定义和初始化
OneWire temperature(5);  

//时钟模块
GravityRtc rtc;

//传感器监视器
GravitySensorHub monitor;


void setup() {
	Serial.begin(9600);
	rtc.setup();
	monitor.setup();

}


//********************************************************************************************
// 函数名称: monitor.getValueBySensorNumber(0)
// 函数说明：获取传感器的数值，不同的参数代表获取不同的传感器数据     
// 参    数: 0  ph值  
// 参    数: 1  温度值    
// 参    数: 2  溶解氧
// 参    数: 3  电导率
// 参    数: 4  氧化还原电位
// 返 回 值: 返回一个double类型的数据 
//********************************************************************************************


void loop() {
	rtc.update();
	monitor.update();

	//*************************串口调试******************
	//Serial.print("ph= ");
	//Serial.print(monitor.getValueBySensorNumber(0));
	//Serial.print("  Temp= ");
	//Serial.print(monitor.getValueBySensorNumber(1));
	//Serial.print("  Orp= ");
	//Serial.println(monitor.getValueBySensorNumber(4));
	//Serial.print("  EC= ");
	//Serial.println(monitor.getValueBySensorNumber(3));
}



/******************************相关调试信息的打印***************************/
//注意:Arduino M0打印调试信息的时候需要将Serial替换成SerialUSB

//*************************串口调试******************
//Serial.print("ph= ");
//Serial.print(monitor.getValueBySensorNumber(0));
//Serial.print("  Temp= ");
//Serial.print(monitor.getValueBySensorNumber(1));
//Serial.print("  Orp= ");
//Serial.println(monitor.getValueBySensorNumber(4));
//Serial.print("  EC= ");
//Serial.println(monitor.getValueBySensorNumber(3));


//*************************时间********************************
//Serial.print("   Year = ");//year
//Serial.print(rtc.year);
//Serial.print("   Month = ");//month
//Serial.print(rtc.month);
//Serial.print("   Day = ");//day
//Serial.print(rtc.day);
//Serial.print("   Week = ");//week
//Serial.print(rtc.week);
//Serial.print("   Hour = ");//hour
//Serial.print(rtc.hour);
//Serial.print("   Minute = ");//minute
//Serial.print(rtc.minute);
//Serial.print("   Second = ");//second
//Serial.println(rtc.second);

