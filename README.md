

# WaterMonitor.ino

This sample code is mainly used to monitor water quality,including ph, temperature, dissolved oxygen, ec and orp,etc.



* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com)
* GitHub Link :https://github.com/DFRobot/watermonitor



* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.



## Step1:

Download and install the  Arduino IDE 1.8.2

* Software download link : https://www.arduino.cc/en/Main/Software



## Step2:

Install the library file：

* Copy the files from the github repository folder libraries to the libraries in the Arduino IDE 1.8.2 installation directory



## Step3:

#### Hardware connection 

* Hardware platform   : Arduino UNO, Arduino M0 Or Arduino Mega2560

#### Sensor pin: 

* EC  : A1

* PH  : A2

* ORP : A3

* RTC : I2C

* DO  : Serial port Rx(0),Tx(1)

* temperature:D5

* SD card attached to SPI bus as follows:

* Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 53

* and pin #53 (SS) must be an output

* M0:   Onboard SPI pin,CS - pin 4 (CS pin can be changed)

  ​

author  :  Jason(jason.ling@dfrobot.com)

version :  V1.0

date    :  2017-04-06