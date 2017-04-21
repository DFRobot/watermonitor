/*********************************************************************
* GravityLcd.h
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
* date    :  2017-04-18
**********************************************************************/

#pragma once
class GravityLcd
{
public:
	GravityLcd();
	~GravityLcd();

public:
	//初始化
	void setup();

	//刷新LCD
	void update();

private:
	unsigned long displayUpdateTime;

	// 绘制显示屏的一帧图像
	void draw();

	//日期
	char year[5] ;
	char month[3];
	char day[3] ;
	char hour[3];
	char minute[3];
	char second[3];

	//存放各传感器数据
	char ph[10];
	char temp[4];
	char Do[10];
	char ec[10];
	char orp[10];
};

