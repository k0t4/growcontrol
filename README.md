# growcontrol

It is a project to control how to grow different plants with arduino.

I'm working with atom https://atom.io and the plugin PlatfomrIO https://platformio.org for running arduino.

You can observe two different folders:

	- lib: All the necessary libraries for running GrowControl in arduino or atom.
	- scr: The main.cpp is the brain. Open this.

But if you prefer to open the whole project in atom, you can click platformio.ini. Then connect your arduino mega and upload.

I'm using an arduino mega with the following electronic cable connections:

	- COMMUNICATION. RTC Real Time Clocks. DS3231
		- C20 SDA
		- C21 SCL

	- DIGITAL. DHT TEMPERATURE AND HUMIDITY SENSOR. DTH22
		- D40
		- D38
		- D36

	- DIGITAL. 1-Wire Digital Thermometer. DS18B20
		- D32

	- DIGITAL. DISPLAY TOUCH 2.4 SPI. ILI9341
		- D26
		- D28
		- In the middle of arduino mega: 
			- SCK
			- MOSI-SDI
			- SDO-MISO

	- DIGITAL PWM. RELAYS OPTOACOPLADOS
		- D2 FAN 1
		- D3 FAN 2
		- D4 LIGTH
		- D5 WATER PUMP
		- D6 HEATER
		- D7
		- D8 SOS


	- ANALOG. HIGROMETER
		- A0
		- A1
	
	- ANALOG. LDR LIGHT SENSOR
		- A7


