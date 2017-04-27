/*********************************************************************************************
* GravityDo.cpp
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
*********************************************************************************************/

#include "GravityDo.h"

GravityDo::GravityDo() 
{

}


GravityDo::~GravityDo()
{
}


//********************************************************************************************
// 函数名称: setup()
// 函数说明：初始化传感器
//********************************************************************************************
void GravityDo::setup()
{
	Serial.begin(9600);
	sensorstring.reserve(30); 
}


//********************************************************************************************
// 函数名称: update()
// 函数说明：更新传感器数值
//********************************************************************************************
void GravityDo::update()
{
	static boolean sensor_string_complete = false;
	if (Serial.available() > 0)
	{
		char inchar = (char)Serial.read();
		this->sensorstring += inchar;
		if (inchar == '\r')
			sensor_string_complete = true;
	}
	if (sensor_string_complete == true)
	{
		if (isdigit(this->sensorstring[0]))
			doValue = this->sensorstring.toFloat();
		this->sensorstring = "";
		sensor_string_complete = false;
	}
}

//********************************************************************************************
// 函数名称: getValue()
// 函数说明：返回传感器数据
//********************************************************************************************
double GravityDo::getValue()
{
	return doValue;
}

//
//void serialEvent() {                                  //if the hardware serial port_0 receives a char
//	inputstring = Serial.readStringUntil(13);           //read the string until we see a <CR>
//	input_string_complete = true;                       //set the flag used to tell if we have received a completed string from the PC 
//}
