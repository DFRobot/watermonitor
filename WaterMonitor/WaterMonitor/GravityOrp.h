/*********************************************************************
* GravityOrp.h
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
* date    :  2017-04-14
**********************************************************************/

#pragma once
#include <Arduino.h>
#include "WaterSensor.h"
class GravityOrp:public IWaterSensor
{
public:
	//orp传感器引脚
	int orpPin;

	//电压值
	double voltage;

	//校准偏移量
	float offset;
private:
	//orp值
	double orpValue;


	/*static const int arrayLength = 20;
	int orpArray[arrayLength];*/
	double avergeArray(int* arr, int number);

	double previousOrp;
	double currentOrp;
	double averageOrp;

public:
	GravityOrp();
	~GravityOrp();

	//初始化传感器
	void setup();

	//更新传感器数据
	void update();

	//获取传感器数据
	double getValue();
};

