/*********************************************************************
* GravityPh.cpp
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
* date    :  2017-04-07
**********************************************************************/

#include "GravityPh.h"


GravityPh::GravityPh():sensorPin(A2), offset(0.0f), 
samplingInterval(20),pHValue(0),voltage(0)
{
}

//********************************************************************************************
// 函数名称: setup()
// 函数说明：初始化ph传感器
//********************************************************************************************
void GravityPh::setup()
{
	pinMode(sensorPin, INPUT);
}


//********************************************************************************************
// 函数名称: update()
// 函数说明：更新传感器数值
//********************************************************************************************
void GravityPh::update()
{
	static unsigned long samplingTime = millis();
	static unsigned long printTime = millis();
	static int pHArrayIndex = 0;
	if (millis() - samplingTime > samplingInterval)
	{
		//pHArray[pHArrayIndex++] = analogRead(this->sensorPin);

		currentVoltage = analogRead(this->sensorPin);
		averageVoltage = (currentVoltage + previousVoltage) / 2;
		previousVoltage = averageVoltage;

		voltage = averageVoltage*5.0 / 1024.0;
		/*Serial.print("voltage = ");
		Serial.println(voltage);*/
		pHValue = 3.5*voltage + this->offset;
		samplingTime = millis();
	}
}

//void GravityPh::update()
//{
//	static unsigned long samplingTime = millis();
//	static unsigned long printTime = millis();
//	static int pHArrayIndex = 0;
//	if (millis() - samplingTime > samplingInterval)
//	{
//		//pHArray[pHArrayIndex++] = analogRead(this->sensorPin);
//
//		currentVoltage = analogRead(this->sensorPin);
//		averageVoltage = (currentVoltage + previousVoltage) / 2;
//		previousVoltage = averageVoltage;
//
//		if (pHArrayIndex == GravityPh::arrayLength)
//			pHArrayIndex = 0;
//		voltage = avergearray(pHArray, GravityPh::arrayLength)*5.0 / 1024.0;
//		/*Serial.print("voltage = ");
//		Serial.println(voltage);*/
//		pHValue = 3.5*voltage + this->offset;
//		samplingTime = millis();
//	}
//}



//********************************************************************************************
// 函数名称: avergearray()
// 函数说明：计算平均值
//********************************************************************************************
double GravityPh::avergearray(int* arr, int number) {
	int i;
	int max, min;
	double avg;
	long amount = 0;
	if (number <= 0) {
		//Serial.println("Error number for the array to avraging!/n");
		return 0;
	}
	if (number<5) {   //less than 5, calculated directly statistics
		for (i = 0;i<number;i++) {
			amount += arr[i];
		}
		avg = amount / number;
		return avg;
	}
	else {
		if (arr[0]<arr[1]) {
			min = arr[0];max = arr[1];
		}
		else {
			min = arr[1];max = arr[0];
		}
		for (i = 2;i<number;i++) {
			if (arr[i]<min) {
				amount += min;        //arr<min
				min = arr[i];
			}
			else {
				if (arr[i]>max) {
					amount += max;    //arr>max
					max = arr[i];
				}
				else {
					amount += arr[i]; //min<=arr<=max
				}
			}//if
		}//for
		avg = (double)(amount / (number - 2));
	}//if
	return avg;
}


//********************************************************************************************
// 函数名称: getValue()
// 函数说明：返回传感器数据
//********************************************************************************************
double GravityPh::getValue()
{
	return this->pHValue;
}


