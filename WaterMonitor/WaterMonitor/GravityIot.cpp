/*********************************************************************
* GravityIot.cpp
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:  This library file mainly completes the accelerometer
* and gyroscope attitude detection
*
* author  :  Jason
* version :  V1.0
* date    :  2017-04-01
**********************************************************************/

#include "GravityIot.h"
#include <Arduino.h>

GravityIot::GravityIot(eventCallback cb = NULL):Iot(cb)
{
}


GravityIot::~GravityIot()
{
}

//**********************************************************************************************************     
// 函数名称： sendMessage      
// 函数说明： 向指定设备循环发送消息
// 参    数： topic 物联网设备名
// 参    数： data  发送的消息
// 参    数： frequency 发送消息的时间间隔
// 返 回 值： 无
//**********************************************************************************************************
void GravityIot::sendMessage(const char * topic, const char * data, unsigned long  frequency)
{
	static unsigned long sendTime = 0;
	if (millis() - sendTime >= frequency) {
		sendTime = millis();
		publish(topic, data);      
	}
}

void GravityIot::receiveMessage(const char * topic, IotCb _cb)
{
}
