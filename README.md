UPDATE MAY 2018 - V2.1.8 IS IN BETA
-----------------------------------
OpenSprinkler_Arduino V2.0.0 - superceded / it contains deprecated types that will no longer compile in the Arduino IDE OpenSprinkler_Arduino V2.0.7 - superceded / it contains deprecated types that will no longer compile in the Arduino IDE OpenSprinkler_Arduino V2.1.6 - superceded / may still work however 2.1.8 offers several advantages 
OpenSprinkler_Arduino V2.1.8	- beta test / based on the unified firmware at https://github.com/OpenSprinkler/OpenSprinkler-Firmware

PLEASE see the 'Notes' section below for some known issues

Overview
--------

OpenSprinkler-Arduino is a fork of Ray's OpenSprinkler code thats amended to use alternative hardware:

- Arduino Mega 2560 (Arduino MCU that can handle compiled code size of around 60K)
- Your choice of ethernet:
	Wiznet W5100 Ethernet with onboard SD Card or
	Enc28j60 ethernet with external SD card
- Freetronics LCD Keypad Shield
- Discrete IO outputs for standard sprinkler stations instead of using a shift register 

PLUS this version adds a couple of additional functions:
- ability to reboot daily to ensure stable operation
- heartbeat function to say 'all's well' - flashes an LED and the ':' on the LCD time at 1Hz

In general the approach is to make the minimum changes necessary to use standard Arduino libraries, and to get alternative hardware to run, and to debug. Otherwise the code is pretty much 'as is' from https://github.com/OpenSprinkler/OpenSprinkler-Firmware

Changes from Rays original code are marked with OPENSPRINKLER_ARDUINO (or variations thereof)

As always - FULL CREDIT to Ray for all his hard work to build and maintain the Open Sprinkler project!

Important Note
--------------
Refer to:
- 'OpenSprinkler_Arduino.h' for options to substitute different hardware and turn functions on or off.
- 'OpenSprinkler_Arduino_Pins.h' to customise pinouts for your particular hardware
See the developers notes below for known issues and limitations

Current Release
---------------

Version:     Opensprinkler V2.1.8 / BETA

Date:        July 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Hardware
--------
   
You'll need:

- Arduino Mega 2560 (or any Arduino with enough progmem to handle binary sketch size of around 60Kb compiled) from [Arduino Mega]

- Freetronics LCD Shield from [Freetronics LCD] - This is a fairly common 16x2 LCD, however the main difference is the buttons are onboard the shield and are all sampled using one analog pin (each button has its own ADC voltage read from pin A0 to indicate which one was pressed). 

- Any DS1307 or DS3231 (preferred) Real Time Clock ($1 from [Ebay DS1307] or [Ebay DS3231] 

- Any 5V relay card that can be driven from Arduino digitial output pins. 

- Power supplies(s), ethernet switch, bits & pieces to hook it all up 

Plus either:

- Wiznet W5100 Ethernet Shield (i.e. Arduino 'standard') - $7 from [Ebay W5100]

 or

- ENC28J60 Ethernet Shield (same as Ray uses for Opensprinkler) - $6 from [Ebay ENC28J60]

Installation
------------

To install and compile this code you need:
   
   1.  Arduino IDE -> http://arduino.cc/
   As an alternative, I use Visual Studio 2015 plus the Visual Micro add-on from here -> http://www.visualmicro.com/
   Visual Micro is relatively inexpensive and provides solid debugging support (much easier than 'Serial.print' statements)
  
   2.  Libraries:
   
   Libraries used with this code are now 'built in' - you *shouldn't* need to download them seperately
   Standard libraries that are installed as part of the Arduino IDE are:
- "Wire.h"          Standard Arduino Library
- "LiquidCrystal.h" Standard Arduino Library
- "SPI.h"           Standard Arduino Library
- "Ethernet.h"      Standard Arduino Library
- "EthernetUdp.h"   Standard Arduino Library

   Additional libraries used for this build are from the following sources (with many thanks for the hard work of each developer). These are included with the source code so you *shouldn't* need to download them seperately:
- "ICMPPing.h"      https://github.com/BlakeFoster/Arduino-Ping
- "Time.h"          http://www.pjrc.com/teensy/td_libs_Time.html 
- "TimeAlarms.h"    http://www.pjrc.com/teensy/td_libs_TimeAlarms.html 
- "DS1307RTC.h"     http://www.pjrc.com/teensy/td_libs_DS1307RTC.html
- "SDFat.h"         https://github.com/greiman/SdFat

  NOTE - unless you're careful, you may have some issues with the libraries above co-existing with your built-in Arduino libraries. The easiest way to fix it is to remove OpenSprinkler and any others of the above libraries from your Arduino library folder. 

  Assuming you have the libraries above installed, the code here *should* compile without too many issues (good luck!)

[Freetronics LCD]:http://www.freetronics.com/collections/shields/products/lcd-keypad-shield
[Ebay W5100]:http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR3.TRC0.A0.H0.Xw5100+shield&_nkw=w5100+shield&_sacat=0
[Ebay ENC28J60]:http://www.ebay.com/sch/i.html?_odkw=enc28j60&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR0.TRC0.H0.Xenc28j60+shield.TRS0&_nkw=enc28j60+shield&_sacat=0
[Ebay DS1307]:http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR10.TRC2.A0.H0.Xds1307&_nkw=ds1307&_sacat=0
[Ebay DS3231]:http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2047675.m570.l1313.TR9.TRC2.A0.H0.Xds3231.TRS0&_nkw=ds3231&_sacat=0
[Arduino Mega]:http://arduino.cc/en/Main/arduinoBoardMega2560
  
Notes
----------------------

If you're trying to make it work:

- To switch between ENC28J60 and the Wiznet W5100 ethernet hardware, comment/uncomment the OPENSPRINKLER_ARDUINO_ENC28J60 and OPENSPRINKLER_ARDUINO_W5100 compiler flags in "OpenSprinkler_Arduino.h" (you'll need at least one flag uncommented for it to compile).

- ESP8266 hardware has not been tested - you're on your own there!

- For the ENC28J60 Version, I'm using non-standard pinouts for SPI so you'll definately need to update 'OpenSprinkler_Arduino_Pins.h' to customise the chipselect pins for your particular SD card and ethernet hardware

- For the Wiznet W5100 Version:
	- previously there was a problem downloading weather (packetloop didn't seem to handle it correctly 2 out of 3 attempts) - this seems to be more stable under V2.1.8
	- the IFTTT interface is not implemented yet (currently the httpPostVar function in EtherCardW5100.h is just a stub).

- Library conflicts:
	- if you're not careful you'll get a whole bunch (kind of like .dll hell from Windows in the old days before .net)
	- I STRONGLY recommend:
		- get rid of any Opensprinkler code you may have in your Arduino 'library' folder
		- use the library files I've uploaded to Github in the folder for this release 

- Chipselect pins for SPI:
	-  D4 on the Freetronics LCD shield clashes with the chipselect pin for the SD card on some W5100 shields. You may need to jumper it to D2 as described at http://forum.freetronics.com/viewtopic.php?t=770

- Multiple Simultaneous Button Presses:
	- some of the functionality on the 'real' Opensprinkler hardware works when multiple buttons are pressed at the same time
	- the buttons on freetronics shield can only be detected one at a time therefore any 'multi-button-press- functions are disabled

If you're a developer:

- Software IDE
	- I'm using Visual Studio 2015 Community Edition plus Visual Micro to build and upload code.
	- this release was tested to compile using Arduino IDE Version current at the time of upload (only) 

- LCD Backlight Dimming
	- no idea how dimming of the LCD backlight on the 'real' opensprinkler works / this code just implements simple on(bright) or off 

- Discrete Outputs:
	- the number of discrete pins that are mapped to standard stations is pre-defined as 24 (this is a nice fit for the Arduino ATMEGA2560 hardware, but there are a couple more spare pins if you really need them). 
	- You'll need to edit "OpenSprinkler_Arduino_Pins.h" if you want more - make sure they're in multiples of 8 

- Hardware Version is preset to OpenSprinkler 2.3:
	- this allows you 'Advanced' settings and to use couple of GPIO pins if you wish. 
	- Pins D18 and D19 should work OK - others are not mapped (note you'd need to update the UI main.js also if you want to use different pins)

- ICMP Library
	- if you use the source library, it may need an include guard on ICMPPing.h (duh)

- Hostname 
	- at this stage hostname isn't implemented for the Opensprinkler W5100 version - you'll need to access by its IP address. A workaround is to assign a hostname in your DHCP server (I use 'opensprinkler.local')
	- this seems to be a limitation of the Arduino Ethernet library / I haven't gotten around to fixing it yet using one of the work-around libraries

- Port Number
	- port number is currently hard coded (default is 80) until I figure out how to change it dynamically when initialising the EthernetServer object

