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


#include <SoftwareSerial.h>                           //we have to include the SoftwareSerial library, or else we can't use it
#define rx 2                                          //define what pin rx is going to be
#define tx 3                                          //define what pin tx is going to be

SoftwareSerial myserial(rx, tx);                      //define how the soft serial port is going to work

String inputstring = "";                              //a string to hold incoming data from the PC
String sensorstring = "";                             //a string to hold the data from the Atlas Scientific product
boolean input_string_complete = true;                //have we received all the data from the PC
boolean sensor_string_complete = true;               //have we received all the data from the Atlas Scientific product

GravityDo::GravityDo() : sensor_string_complete(false)
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
	myserial.begin(9600);                               //set baud rate for the software serial port to 9600
	inputstring.reserve(10);                            //set aside some bytes for receiving data from the PC
	sensorstring.reserve(30);                           //set aside some bytes for receiving data from Atlas Scientific product
}


//********************************************************************************************
// 函数名称: update()
// 函数说明：更新传感器数值
//********************************************************************************************
void GravityDo::update()
{

	if (input_string_complete) {                         //if a string from the PC has been received in its entirety
		myserial.print(inputstring);                      //send that string to the Atlas Scientific product
		myserial.print('\r');                             //add a <CR> to the end of the string 
		inputstring = "";                                 //clear the string
		input_string_complete = false;                    //reset the flag used to tell if we have received a completed string from the PC
	}

	if (myserial.available() > 0) {                     //if we see that the Atlas Scientific product has sent a character
		char inchar = (char)myserial.read();              //get the char we just received
		sensorstring += inchar;                           //add the char to the var called sensorstring
		if (inchar == '\r') {                             //if the incoming character is a <CR>
			sensor_string_complete = true;                  //set the flag
		}
	}


	if (sensor_string_complete == true) {                //if a string from the Atlas Scientific product has been received in its entirety
		//Serial.println(sensorstring);                     //send that string to the PC's serial monitor
		if (isdigit(sensorstring[0])) {                   //if the first character in the string is a digit
			doValue = sensorstring.toFloat();                    //convert the string to a floating point number so it can be evaluated by the Arduino
			if (doValue >= 6.0) {                                //if the DO is greater than or equal to 6.0
				Serial.println("high");                       //print "high" this is demonstrating that the Arduino is evaluating the DO as a number and not as a string
			}
			if (doValue <= 5.99) {                               //if the DO is less than or equal to 5.99
				Serial.println("low");                        //print "low" this is demonstrating that the Arduino is evaluating the DO as a number and not as a string
			}
		}
		sensorstring = "";                                //clear the string
		sensor_string_complete = false;                   //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
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