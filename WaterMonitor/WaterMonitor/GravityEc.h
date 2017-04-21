/*********************************************************************
* GravityEc.h
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
* date    :  2017-04-17
**********************************************************************/

#pragma once
#include "GravityTemperature.h"
#include "WaterSensor.h"

//extern GravityTemperature ecTemperature;

class GravityEc:public IWaterSensor
{
public:
	//电导率传感器引脚
	int ECsensorPin;   

	//电导率数值
	double ECcurrent;


public:
	GravityEc(IWaterSensor*);
	~GravityEc();

	//初始化
	void setup();

	//更新传感器数据
	void update();

	//获取传感器数据
	double getValue();

private:
	//指向温度传感器的指针
	IWaterSensor* ecTemperature = NULL;

	
	static const int numReadings = 40;
	unsigned int readings[numReadings] = { 0 };      // the readings from the analog input
	int index;
	unsigned long AnalogValueTotal;      // the running total
	unsigned int AnalogAverage;
	unsigned int averageVoltage;      
	unsigned long AnalogSampleTime;
	unsigned long printTime;
	unsigned long tempSampleTime;
	unsigned long AnalogSampleInterval ; 
	unsigned long printInterval ;

	//计算平均值
	void calculateAnalogAverage();

	//计算电导率
	void calculateEc();
};

