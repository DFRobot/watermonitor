/*********************************************************************
* GravitySd.cpp
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:SD card datalogger,Data write format:
* "Year,Month,Day,Hour,Minues,Second,pH,temp(C),DO(mg/l0,ec(s/m),orp(mv)"
*
* Product Links:http://www.dfrobot.com.cn/goods-1142.html
*
* SD card attached to SPI bus as follows:
* UNO:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 4 (CS pin can be changed)
* and pin #10 (SS) must be an output
* Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 53
* and pin #53 (SS) must be an output
* M0:   Onboard SPI pin,CS - pin 4 (CS pin can be changed)
*
* author  :  Jason
* version :  V1.0
* date    :  2017-04-19
**********************************************************************/



//#define DEBUG_MEAG2560
//#define DEBUG_M0

//#if defined(__SAMD21G18A__)


//SD卡片选引脚
#if  defined(__AVR_ATmega2560__)

const int CsPin = 53;

#else

const int CsPin = 4;

#endif

#include "GravitySd.h"
#include "string.h"
#include <SPI.h>

#include "GravityRtc.h"

extern GravityRtc rtc;
String dataString = "";

GravitySd::GravitySd(IWaterSensor* gravitySensor[]) :chipSelect(CsPin),sdDataUpdateTime(0)
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

#ifdef DEBUG_M0
	SerialUSB.print(F("Initializing SD card..."));
#endif // DEBUG_M0

#ifdef DEBUG_MEAG2560
	Serial.print(F("Initializing SD card..."));
#endif // DEBUG_MEAG2560
	
	pinMode(SS, OUTPUT);

	if (!SD.begin(chipSelect)) {

#ifdef DEBUG_M0
		SerialUSB.println(F("Card failed, or not present"));
#endif // DEBUG_M0

#ifdef DEBUG_MEAG2560
		Serial.println(F("Card failed, or not present"));
#endif // DEBUG_MEAG2560
		// don't do anything more:
		return;
	}

#ifdef DEBUG_M0
	SerialUSB.println(F("card initialized."));
#endif // DEBUG_M0

#ifdef DEBUG_MEAG2560
	Serial.println(F("card initialized."));
#endif // DEBUG_MEAG2560

	//写入文件头
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
	if (millis() - sdDataUpdateTime > 2000) //2000ms
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

#ifdef DEBUG_M0
	SerialUSB.println(dataString);
#endif // DEBUG_M0

#ifdef DEBUG_MEAG2560
	Serial.println(dataString);
#endif // DEBUG_MEAG2560

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
