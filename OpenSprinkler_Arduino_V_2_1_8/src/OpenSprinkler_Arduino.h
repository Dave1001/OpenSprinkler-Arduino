/* ====================================================

Version:	OpenSprinkler_Arduino 2.1.8

Date:		July 2018

Repository: https://github.com/plainolddave/OpenSprinkler-Arduino

License:	Creative Commons Attribution-ShareAlike 3.0 license

About:		This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware:
				- Arduino Mega 2560 (or any Arduino MCU that can handle compiled code size of around 70K)
				- Freetronics LCD Keypad Shield
				- Discrete IO outputs for standard watering stations, instead of using a shift register
                - Either WiznetW5100 or ENC28J60 Ethernet interface

			In general the approach is to make minimum changes necessary to:
				1) deconflict between Rays libraries that have been modified away from standard Arduino
				2) get alternative hardware to run
				3) debug

			PLUS this version adds a couple of additional functions:
				- automatically reboot daily to ensure stable operation
				- heartbeat function to say 'alls well' - flashes an LED and the ':' on the LCD time at 1Hz

			Otherwise the code is pretty much 'as is' from https://github.com/OpenSprinkler/OpenSprinkler-Firmware

			Changes from Rays original code are marked with OPENSPRINKLER_ARDUINO (or variations thereof)

            Refer to "README.md' for known issues and bugs

			As always - FULL CREDIT to Ray for all his hard work to build and maintain the Open Sprinkler project!
*/
#ifndef _OS_ARDUINO_H_
#define _OS_ARDUINO_H_

// ------------------------------------------------------------
// Compiler switches - comment out these defines to substitute different hardware & functions
// You can also search the project for these keywords to find where the code has been modified
// ------------------------------------------------------------

#define OPENSPRINKLER_ARDUINO
#define OPENSPRINKLER_ARDUINO_DISCRETE			// use discrete IO instead of a shift register to control sprinkler outputs
#define OPENSPRINKLER_ARDUINO_FREETRONICS_LCD	// use Freetronics LCD with keypad
#define OPENSPRINKLER_ARDUINO_AUTOREBOOT		// this is an optional function to reboot daily to ensure stable operation
#define OPENSPRINKLER_ARDUINO_HEARTBEAT			// this is an optional function to say 'alls well' - flashes an LED, and the ':' on the LCD time at 1Hz
//#define OPENSPRINKLER_ARDUINO_W5100		    // use the standard Arduino Wiznet5100 Ethernet interface
#define OPENSPRINKLER_ARDUINO_ENC28J60	        // use the less common Opensprinkler enc28j60 Ethernet interface

#include <Arduino.h>
#include "OpenSprinkler_Arduino_Debug.h"

// ------------------------------------------------------------
#ifdef OPENSPRINKLER_ARDUINO

    #include "OpenSprinkler_Arduino_Pins.h"

#endif // OPENSPRINKLER_ARDUINO

// ------------------------------------------------------------
#ifdef OPENSPRINKLER_ARDUINO_DISCRETE

#include "OpenSprinkler_Arduino_Discrete.h"

#endif // OPENSPRINKLER_ARDUINO_DISCRETE

// ------------------------------------------------------------
#ifdef OPENSPRINKLER_ARDUINO_FREETRONICS_LCD

    #include "OpenSprinkler_Arduino_Button.h"

#endif // OPENSPRINKLER_ARDUINO_FREETRONICS_LCD

// ------------------------------------------------------------
#ifdef OPENSPRINKLER_ARDUINO_AUTOREBOOT

    #include "..\TimeAlarms.h"

    // Auto reboot time
    #define AUTO_REBOOT_HR	    12		// hour to perform daily reboot
    #define AUTO_REBOOT_MIN	    00		// min  to perform daily reboot
    #define AUTO_REBOOT_SEC	    00		// sec  to perform daily reboot

#endif // OPENSPRINKLER_ARDUINO_AUTOREBOOT

// ------------------------------------------------------------
#ifdef OPENSPRINKLER_ARDUINO_HEARTBEAT

    // nothing to set up

#endif // OPENSPRINKLER_ARDUINO_HEARTBEAT

// ------------------------------------------------------------
#ifdef OPENSPRINKLER_ARDUINO_W5100

#include "network/EtherCardWrapper.h"
#include "network/EtherCardW5100.h"

// Set up the right pins for the ethernet controller in use
#define PIN_ETHER_CS    PIN_W5100_ETHER_CS
#define PIN_SD_CS       PIN_W5100_SD_CS

extern EtherCardWrapper<EtherCardW5100> ether; // Global declaration of ether (define in the .ino file)

#elif defined (OPENSPRINKLER_ARDUINO_ENC28J60)

#include "network/EtherCardWrapper.h"
#include "network/EtherCard.h"

    // Set up the right pins for the ethernet controller in use
#define PIN_ETHER_CS    PIN_ENC28J60_CS
#define PIN_SD_CS       PIN_ENC28J60_SD_CS

extern EtherCardWrapper<EtherCard> ether; // Global declaration of ether

#else

#error Please select a network interface

#endif

#endif  // _OS_ARDUINO_H_




