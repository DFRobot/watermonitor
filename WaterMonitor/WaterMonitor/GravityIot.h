/*********************************************************************
* DFIot.h
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:  This library file is mainly used to operate OBLOQ 
* Internet of Things
*
* author  :  Jason
* version :  V1.0
* date    :  2017-04-07
**********************************************************************/

#pragma once
#include "Iot.h"
typedef void* (*eventCallback)(uint8_t type, const char *data, uint16_t len);

class GravityIot :public Iot
{
public:
	GravityIot(eventCallback cb = NULL);
	~GravityIot();

public:
	//**********************************************************************************************************     
	// 函数名称： sendMessage      
	// 函数说明： 向指定设备循环发送消息
	// 参    数： topic 物联网设备名
	// 参    数： data  发送的消息
	// 参    数： frequency 发送消息的时间间隔
	// 返 回 值： 无
	//**********************************************************************************************************
	void sendMessage(const char* topic, const char *data, unsigned long  frequency);
	void receiveMessage(const char* topic, IotCb _cb);
};

