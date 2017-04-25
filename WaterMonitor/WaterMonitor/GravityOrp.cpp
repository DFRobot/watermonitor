/*********************************************************************
* GravityOrp.cpp
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

#include "GravityOrp.h"


//********************************************************************************************
// 函数名称: avergeArray()
// 函数说明：滑动平均滤波
//********************************************************************************************
double GravityOrp::avergeArray(int * arr, int number)
{
	//int i;
	//int max, min;
	//double avg;
	//long amount = 0;
	//if (number <= 0) {
	//	printf("Error number for the array to avraging!/n");
	//	return 0;
	//}
	//if (number<5) {   //less than 5, calculated directly statistics
	//	for (i = 0;i<number;i++) {
	//		amount += arr[i];
	//	}
	//	avg = amount / number;
	//	return avg;
	//}
	//else {
	//	if (arr[0]<arr[1]) {
	//		min = arr[0];max = arr[1];
	//	}
	//	else {
	//		min = arr[1];max = arr[0];
	//	}
	//	for (i = 2;i<number;i++) {
	//		if (arr[i]<min) {
	//			amount += min;        //arr<min
	//			min = arr[i];
	//		}
	//		else {
	//			if (arr[i]>max) {
	//				amount += max;    //arr>max
	//				max = arr[i];
	//			}
	//			else {
	//				amount += arr[i]; //min<=arr<=max
	//			}
	//		}//if
	//	}//for
	//	avg = (double)amount / (number - 2);
	//}//if
	//return avg;
}

GravityOrp::GravityOrp():orpPin(A3), voltage(5.0), offset(0), orpValue(0.0)
{
}


GravityOrp::~GravityOrp()
{
}

//********************************************************************************************
// 函数名称: setup()
// 函数说明：初始化传感器
//********************************************************************************************
void GravityOrp::setup()
{
}



//********************************************************************************************
// 函数名称: update()
// 函数说明：更新传感器数值
//********************************************************************************************
void GravityOrp::update()
{
	static unsigned long orpTimer = millis();   //analog sampling interval
	static unsigned long printTime = millis();
	static int orpArrayIndex = 0;
	if (millis() >= orpTimer)
	{
		orpTimer = millis() + 20;
		currentOrp = analogRead(orpPin);    //read an analog value every 20ms
		averageOrp = (previousOrp + currentOrp) / 2;
		previousOrp = averageOrp;

		//convert the analog value to orp according the circuit
		this->orpValue = ((30 * this->voltage * 1000) - (75 * averageOrp*this->voltage * 1000 / 1024)) / 75 - this->offset;
	}

}


//********************************************************************************************
// 函数名称: getValue()
// 函数说明：返回传感器数据
//********************************************************************************************
double GravityOrp::getValue()
{
	return this->orpValue;
}
