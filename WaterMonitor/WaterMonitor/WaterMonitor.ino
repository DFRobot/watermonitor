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
#include <MemoryFree.h>

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
	/*Serial.print("freeMemory()=");
	Serial.println(freeMemory());*/

	//Serial.print("ph= ");
	//Serial.print(monitor.getValueBySensorNumber(0));
	//Serial.print("  Temp= ");
	//Serial.print(monitor.getValueBySensorNumber(1));
	//Serial.print("  EC= ");
	//Serial.print(monitor.getValueBySensorNumber(3));
	//Serial.print("  Orp= ");
	//Serial.println(monitor.getValueBySensorNumber(4));
	

}


/******************************相关调试信息的打印***************************/
//*************************带框架测试程序******************
//Serial.print("ph= ");
//Serial.print(monitor.getValueBySensorNumber(0));
//Serial.print("  Temp= ");
//Serial.print(monitor.getValueBySensorNumber(1));
//Serial.print("  Orp= ");
//Serial.println(monitor.getValueBySensorNumber(4));
//Serial.print("  EC= ");
//Serial.println(monitor.getValueBySensorNumber(3));


//***********************不带框架的测试程序******************
//Serial.print("ph= ");
//Serial.print(ph.getValue());
//Serial.print("  orp= ");
//Serial.print(orp.getValue());
//Serial.print("  temp= ");
//Serial.print(temp.getValue());
//Serial.print("  ec= ");
//Serial.print(ec.getValue());

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



//*************************物联网代码****************************
//dtostrf(monitor.getValueBySensorNumber(0), 6, 2, buffer);
//dfiot.sendMessage("ph", buffer, 5000);
//dtostrf(monitor.getValueBySensorNumber(2), 6, 2, buffer);
//dfiot.sendMessage("temp", buffer, 5000);
//dfiot.loop();
