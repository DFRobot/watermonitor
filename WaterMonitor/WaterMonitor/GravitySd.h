/*********************************************************************
* GravitySd.h
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
* date    :  2017-04-19
**********************************************************************/

#pragma once

#include "WaterSensor.h"
#include <SD.h>
#include "string.h"

class GravitySd:public IWaterSensor
{

public:
	int chipSelect;
public:
	GravitySd(IWaterSensor* gravitySensor[]);
	~GravitySd();

	//初始化
	void setup();

	//更新写入SD卡数据
	void update();

	//接口继承，在这里没有实际用途
	double getValue();


private:
	//指向存放传感器数组的指针
	IWaterSensor** gravitySensor;
	//String dataString ;

	//文件句柄
	File dataFile;
	unsigned long sdDataUpdateTime;

	//连接字符串数据
	void connectString(double value);
};

