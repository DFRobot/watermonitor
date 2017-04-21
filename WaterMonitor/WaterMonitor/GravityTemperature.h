/*********************************************************************
* GravityTemperature.h
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
* date    :  2017-04-12
**********************************************************************/

#pragma once
#include "WaterSensor.h"
#include "OneWire.h"
#define StartConvert 0
#define ReadTemperature 1

class GravityTemperature : public IWaterSensor 
{
public:
	//温度传感器引脚
	int temperaturePin;
	double temperature;

public:
	GravityTemperature(OneWire *temp);
	~GravityTemperature();

	//初始化
	void setup();

	//更新传感器数据
	void update();

	//获取传感器数据
	double getValue();

private:

	OneWire *temp;
	unsigned long tempSampleInterval = 850;
	unsigned long tempSampleTime;

	//解析温度数据
	double TempProcess(bool ch);
};

