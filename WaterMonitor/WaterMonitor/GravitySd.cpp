/*********************************************************************
* GravitySd.cpp
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

#include "GravitySd.h"
#include "string.h"
#include <SPI.h>

#include "GravityRtc.h"

extern GravityRtc rtc;
String dataString = "";

GravitySd::GravitySd(IWaterSensor* gravitySensor[]) :chipSelect(53),sdDataUpdateTime(0)
{
	this->gravitySensor = gravitySensor;
}


GravitySd::~GravitySd()
{
}

//********************************************************************************************
// 函数名称: setup()
// 函数说明：初始化SD卡
//********************************************************************************************
void GravitySd::setup()
{

	Serial.print("Initializing SD card...");

	if (!SD.begin(chipSelect)) {
		Serial.println("Card failed, or not present");
		// don't do anything more:
		return;
	}
	Serial.println("card initialized.");
	dataFile = SD.open("sensor.csv", FILE_WRITE);
	if (dataFile && dataFile.position() == 0) {
		dataFile.println("Year,Month,Day,Hour,Minues,Second,pH,temp(C),DO(mg/l0,ec(s/m),orp(mv)");
		dataFile.close();
	}
		
}


//********************************************************************************************
// 函数名称: update()
// 函数说明: 更新SD卡中的数据
//********************************************************************************************
void GravitySd::update()
{
	if (millis() - sdDataUpdateTime > 2000)
	{
		
		dataString = "";
		//年月日时分秒
		dataString += String(rtc.year,10);
		dataString += ",";
		dataString += String(rtc.month, 10);
		dataString += ",";
		dataString += String(rtc.day, 10);
		dataString += ",";
		dataString += String(rtc.hour, 10);
		dataString += ",";
		dataString += String(rtc.minute, 10);
		dataString += ",";
		dataString += String(rtc.second, 10);
		dataString += ",";
	
		//ph
		if (this->gravitySensor[0] != NULL) {
			connectString(this->gravitySensor[0]->getValue());
		}
		else
			connectString(0);
			
		//温度
		if (this->gravitySensor[1] != NULL) {
			connectString(this->gravitySensor[1]->getValue());
		}
		else
			connectString(0);

		//DO
		if (this->gravitySensor[2] != NULL) {
			connectString(this->gravitySensor[2]->getValue());
		}
		else
			connectString(0);

		//EC
		if (this->gravitySensor[3] != NULL) {
			connectString(this->gravitySensor[3]->getValue());
		}
		else
			connectString(0);

		//Orp
		if (this->gravitySensor[4] != NULL) {
			connectString(this->gravitySensor[4]->getValue());
		}
		else
			connectString(0);

		//写入SD卡
		dataFile = SD.open("sensor.csv", FILE_WRITE);
		if (dataFile) {
			dataFile.println(dataString);
			dataFile.close();
			//Serial.println(dataString);
		}

		sdDataUpdateTime = millis();
	}
}

//********************************************************************************************
// 函数名称: getValue()
// 函数说明: 接口继承，在这里没有实际用途
//********************************************************************************************
double GravitySd::getValue()
{
	return 0.0;
}


//********************************************************************************************
// 函数名称: connectString()
// 函数说明: 连接字符串数据
//********************************************************************************************
void GravitySd::connectString(double value)
{
	dataString += String(value, 10);
	dataString += ",";
}
