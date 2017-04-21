/*********************************************************************
* GravityLcd.cpp
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

#include "GravityLcd.h"
#include "U8glib.h"
#include "GravityRtc.h"
#include "Arduino.h"

U8GLIB_NHD_C12864 u8g(13, 11, 10, 9, 8);

extern GravityRtc rtc;


//定义显示屏每一行的显示位置
int stringOnePosition = 0;
int stringTwoPosition = 23;
int stringThreePosition = 49;
int stringFourPosition = 72;
int stringFivePosition = 92;
int stringSixPosition = 110;

int stringOneLineHigh = 10;
int stringTwoLineHigh = 24;
int stringThreeLineHigh = 38;
int stringFourLineHigh = 52;
int stringFiveLineHigh = 64;

GravityLcd::GravityLcd()
{
}


GravityLcd::~GravityLcd()
{
}


//********************************************************************************************
// 函数名称: setup()
// 函数说明：初始化LCD
//********************************************************************************************
void GravityLcd::setup()
{
	// flip screen, if required
	// u8g.setRot180();

	// set SPI backup if required
	//u8g.setHardwareBackup(u8g_backup_avr_spi);

	// assign default color value
	if (u8g.getMode() == U8G_MODE_R3G3B2) {
		u8g.setColorIndex(255);     // white
	}
	else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
		u8g.setColorIndex(3);         // max intensity
	}
	else if (u8g.getMode() == U8G_MODE_BW) {
		u8g.setColorIndex(1);         // pixel on
	}
	else if (u8g.getMode() == U8G_MODE_HICOLOR) {
		u8g.setHiColorByRGB(255, 255, 255);
	}

}



//********************************************************************************************
// 函数名称: update()
// 函数说明：刷新LCD显示
//********************************************************************************************
void GravityLcd::update()
{
	dtostrf(rtc.year, 4, 0, year);
	dtostrf(rtc.month, 2, 0, month);
	dtostrf(rtc.day, 2, 0, day);
	dtostrf(rtc.hour, 2, 0, hour);
	dtostrf(rtc.minute, 2, 0, minute);
	dtostrf(rtc.second, 2, 0, second);

	if (millis() - displayUpdateTime >500)
	{
		displayUpdateTime = millis();
		u8g.firstPage();
		do {
			draw();
		} while (u8g.nextPage());
	}
}


//********************************************************************************************
// 函数名称: draw()
// 函数说明：绘制显示屏的一帧图像
//********************************************************************************************
void GravityLcd::draw()
{
	// graphic commands to redraw the complete screen should be placed here  
	// u8g.setFont(u8g_font_unifont);
	//u8g.setFont(u8g_font_osb21);
	u8g.setFont(u8g_font_5x8);//4x6 5x7 5x8 6x10 6x12 6x13
							  // u8g.setFontRefHeightText();
							  //u8g.setFontPosTop();

							  //第一行
	u8g.drawStr(stringOnePosition, stringOneLineHigh, "PH");
	u8g.drawStr(stringTwoPosition, stringOneLineHigh, ph);
	u8g.drawStr(stringThreePosition, stringOneLineHigh, " ");
	u8g.drawStr(stringFourPosition - 3, stringOneLineHigh, "Temp");
	u8g.drawStr(stringFivePosition, stringOneLineHigh, temp);
	u8g.drawStr(stringSixPosition, stringOneLineHigh, "c");

	//第二行
	u8g.drawStr(stringOnePosition, stringTwoLineHigh, "DO");
	u8g.drawStr(stringTwoPosition, stringTwoLineHigh, Do);
	u8g.drawStr(stringThreePosition - 5, stringTwoLineHigh, "mg/L ");
	u8g.drawStr(stringFourPosition - 2, stringTwoLineHigh, "EC");
	u8g.drawStr(stringFivePosition, stringTwoLineHigh, ec);
	u8g.drawStr(stringSixPosition, stringTwoLineHigh, "s/m");

	//第三行
	u8g.drawStr(stringOnePosition, stringThreeLineHigh, "ORP");
	u8g.drawStr(stringTwoPosition, stringThreeLineHigh, orp);
	u8g.drawStr(stringThreePosition - 5, stringThreeLineHigh, "mv ");

	//第四行
	u8g.drawStr(stringOnePosition, stringFourLineHigh, "DATE");
	u8g.drawStr(stringTwoPosition, stringFourLineHigh, year);
	if (rtc.month < 10)
	{
		u8g.drawStr(stringThreePosition + 5, stringFourLineHigh, "0");
		u8g.drawStr(stringThreePosition + 6, stringFourLineHigh, month);
	}
	else
		u8g.drawStr(stringThreePosition + 5, stringFourLineHigh, month);

	if (rtc.day < 10)
	{
		u8g.drawStr(stringFourPosition, stringFourLineHigh, "0");
		u8g.drawStr(stringFourPosition + 1, stringFourLineHigh, day);
	}
	else
		u8g.drawStr(stringFourPosition, stringFourLineHigh, day);

	u8g.drawStr(stringFivePosition, stringFourLineHigh, "mom");

	//第五行
	u8g.drawStr(stringOnePosition, stringFiveLineHigh, "TIME");

	if (rtc.hour < 10)
	{
		u8g.drawStr(stringTwoPosition, stringFiveLineHigh, "0");
		u8g.drawStr(stringTwoPosition+1, stringFiveLineHigh, hour);
	}
	else
		u8g.drawStr(stringTwoPosition, stringFiveLineHigh, hour);
	u8g.drawStr(stringTwoPosition + 10, stringFiveLineHigh, ":");

	if (rtc.minute < 10)
	{
		u8g.drawStr(stringTwoPosition + 16, stringFiveLineHigh, "0");
		u8g.drawStr(stringTwoPosition + 17, stringFiveLineHigh, minute);
	}
	else
		u8g.drawStr(stringTwoPosition + 16, stringFiveLineHigh, minute);
	u8g.drawStr(stringTwoPosition + 28, stringFiveLineHigh, ":");
	if (rtc.second < 10)
	{
		u8g.drawStr(stringTwoPosition + 34, stringFiveLineHigh, "0");
		u8g.drawStr(stringTwoPosition + 35, stringFiveLineHigh, second);
	}
	else
		u8g.drawStr(stringTwoPosition + 34, stringFiveLineHigh, second);
}
