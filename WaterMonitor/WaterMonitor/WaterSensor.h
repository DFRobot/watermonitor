﻿/*********************************************************************
* WaterSensor.h
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
* date    :  2017-04-06
**********************************************************************/
#pragma once
class IWaterSensor
{
public:
	virtual void setup()		= 0;
	virtual void update()		= 0;
	virtual double getValue()	= 0;
};