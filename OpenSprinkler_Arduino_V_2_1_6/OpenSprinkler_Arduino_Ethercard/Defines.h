/* OpenSprinkler Unified (AVR/RPI/BBB/LINUX) Firmware
 * Copyright (C) 2015 by Ray Wang (ray@opensprinkler.com)
 *
 * OpenSprinkler macro defines and hardware pin assignments
 * Feb 2015 @ OpenSprinkler.com
 *
 * This file is part of the OpenSprinkler library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _DEFINES_H
#define _DEFINES_H

#include <Arduino.h>
#include <Time.h>
#include "Config.h"

/** Firmware version, hardware version, and maximal values */
#define OS_FW_VERSION			216		// Firmware version: 216 means 2.1.6
										            // if this number is different from the one stored in non-volatile memory
										          // a device reset will be automatically triggered

#define OS_FW_MINOR				1		// Firmware minor version

/** Hardware version base numbers */
#define OS_HW_VERSION_BASE		0x00
#define OSPI_HW_VERSION_BASE	0x40
#define OSBO_HW_VERSION_BASE	0x80
#define SIM_HW_VERSION_BASE		0xC0

/** Hardware type macro defines */
#define HW_TYPE_AC				0xAC	// standard 24VAC for 24VAC solenoids only, with triacs
#define HW_TYPE_DC				0xDC	// DC powered, for both DC and 24VAC solenoids, with boost converter and MOSFETs
#define HW_TYPE_LATCH			0x1A	// DC powered, for DC latching solenoids only, with boost converter and H-bridges

/** File names */
#define WEATHER_OPTS_FILENAME "wtopts.txt"    // weather options file
#define STATION_ATTR_FILENAME "stns.dat"      // station attributes data file
#define STATION_SPECIAL_DATA_SIZE  23

#define FLOWCOUNT_RT_WINDOW		30    // flow count window (for computing real-time flow rate), 30 seconds

/** Station type macro defines */
#define STN_TYPE_STANDARD		0x00
#define STN_TYPE_RF				0x01
#define STN_TYPE_REMOTE			0x02
#define STN_TYPE_OTHER			0xFF

/** Sensor type macro defines */
#define SENSOR_TYPE_NONE		0x00
#define SENSOR_TYPE_RAIN		0x01
#define SENSOR_TYPE_FLOW		0x02
#define SENSOR_TYPE_OTHER		0xFF

/** Non-volatile memory (NVM) defines */
#if defined(ARDUINO)

	/** 2KB NVM (ATmega644) data structure:
	  * |         |     |  ---STRING PARAMETERS---      |           |   ----STATION ATTRIBUTES-----      |          |
	  * | PROGRAM | CON | PWD | LOC | JURL | WURL | KEY | STN_NAMES | MAS | IGR | MAS2 | DIS | SEQ | SPE | OPTIONS  |
	  * |  (996)  |(12) |(36) |(48) | (40) | (40) |(24) |   (768)   | (6) | (6) |  (6) | (6) | (6) | (6) |  (48)    |
	  * |         |     |     |     |      |      |     |           |     |     |      |     |     |     |          |
	  * 0        996  1008   1044  1092  1132   1172   1196        1964  1970  1976   1982  1988  1994  2000      2048
	  */

	/** 4KB NVM (ATmega1284) data structure:
	  * |         |     |  ---STRING PARAMETERS---      |           |   ----STATION ATTRIBUTES-----      |          |
	  * | PROGRAM | CON | PWD | LOC | JURL | WURL | KEY | STN_NAMES | MAS | IGR | MAS2 | DIS | SEQ | SPE | OPTIONS  |
	  * |  (2438) |(12) |(36) |(48) | (48) | (48) |(24) |   (1344)  | (7) | (7) |  (7) | (7) | (7) | (7) |   (56)   |
	  * |         |     |     |     |      |      |     |           |     |     |      |     |     |     |          |
	  * 0       2438  2450   2486  2534  2582   2630   2654        3998  4005  4012   4019  4026  4033  4040      4096
	  */

	#if defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega1284__) // for 4KB NVM

		#define MAX_EXT_BOARDS    6  // maximum number of exp. boards (each expands 8 stations)
		#define MAX_NUM_STATIONS  ((1+MAX_EXT_BOARDS)*8)  // maximum number of stations

		#define NVM_SIZE            4096  // For AVR, nvm data is stored in EEPROM, ATmega1284 has 4K EEPROM
		#define STATION_NAME_SIZE   24    // maximum number of characters in each station name

		#define MAX_PROGRAMDATA     2438  // program data
		#define MAX_NVCONDATA       12    // non-volatile controller data
		#define MAX_USER_PASSWORD   36    // user password
		#define MAX_LOCATION        48    // location string
		#define MAX_JAVASCRIPTURL   48    // javascript url
		#define MAX_WEATHERURL      48    // weather script url
		#define MAX_WEATHER_KEY     24    // weather api key

	#else

		// OPENSPRINKLER_ARDUINO
		// #define MAX_EXT_BOARDS		2  // maximum number of exp. boards (each expands 8 stations)

		#define MAX_NUM_STATIONS	((1+MAX_EXT_BOARDS)*8)  // maximum number of stations

		#define NVM_SIZE            2048  // For AVR, nvm data is stored in EEPROM, ATmega644 has 2K EEPROM
		#define STATION_NAME_SIZE   16    // maximum number of characters in each station name

		#define MAX_PROGRAMDATA     996   // program data
		#define MAX_NVCONDATA       12     // non-volatile controller data
		#define MAX_USER_PASSWORD   36    // user password
		#define MAX_LOCATION        48    // location string
		#define MAX_JAVASCRIPTURL   40    // javascript url
		#define MAX_WEATHERURL      40    // weather script url
		#define MAX_WEATHER_KEY     24    // weather api key,

	#endif

#else // NVM defines for RPI/BBB/LINUX

	// These are kept the same as AVR for compatibility reasons
	// But they can be increased if needed
	#define NVM_FILENAME        "nvm.dat" // for RPI/BBB, nvm data is stored in a file

	#define MAX_EXT_BOARDS    6  // maximum number of exp. boards (each expands 8 stations)
	#define MAX_NUM_STATIONS  ((1+MAX_EXT_BOARDS)*8)  // maximum number of stations

	#define NVM_SIZE            4096
	#define STATION_NAME_SIZE   24    // maximum number of characters in each station name

	#define MAX_PROGRAMDATA     2438  // program data
	#define MAX_NVCONDATA       12     // non-volatile controller data
	#define MAX_USER_PASSWORD   36    // user password
	#define MAX_LOCATION        48    // location string
	#define MAX_JAVASCRIPTURL   48    // javascript url
	#define MAX_WEATHERURL      48    // weather script url
	#define MAX_WEATHER_KEY     24    // weather api key

#endif  // end of NVM defines

/** NVM data addresses */
#define ADDR_NVM_PROGRAMS      (0)   // program starting address
#define ADDR_NVM_NVCONDATA     (ADDR_NVM_PROGRAMS+MAX_PROGRAMDATA)
#define ADDR_NVM_PASSWORD      (ADDR_NVM_NVCONDATA+MAX_NVCONDATA)
#define ADDR_NVM_LOCATION      (ADDR_NVM_PASSWORD+MAX_USER_PASSWORD)
#define ADDR_NVM_JAVASCRIPTURL (ADDR_NVM_LOCATION+MAX_LOCATION)
#define ADDR_NVM_WEATHERURL    (ADDR_NVM_JAVASCRIPTURL+MAX_JAVASCRIPTURL)
#define ADDR_NVM_WEATHER_KEY   (ADDR_NVM_WEATHERURL+MAX_WEATHERURL)
#define ADDR_NVM_STN_NAMES     (ADDR_NVM_WEATHER_KEY+MAX_WEATHER_KEY)
#define ADDR_NVM_MAS_OP        (ADDR_NVM_STN_NAMES+MAX_NUM_STATIONS*STATION_NAME_SIZE) // master op bits
#define ADDR_NVM_IGNRAIN       (ADDR_NVM_MAS_OP+(MAX_EXT_BOARDS+1))  // ignore rain bits
#define ADDR_NVM_MAS_OP_2      (ADDR_NVM_IGNRAIN+(MAX_EXT_BOARDS+1)) // master2 op bits
#define ADDR_NVM_STNDISABLE    (ADDR_NVM_MAS_OP_2+(MAX_EXT_BOARDS+1))// station disable bits
#define ADDR_NVM_STNSEQ        (ADDR_NVM_STNDISABLE+(MAX_EXT_BOARDS+1))// station sequential bits
#define ADDR_NVM_STNSPE        (ADDR_NVM_STNSEQ+(MAX_EXT_BOARDS+1)) // station special bits (i.e. non-standard stations)
#define ADDR_NVM_OPTIONS       (ADDR_NVM_STNSPE+(MAX_EXT_BOARDS+1))  // options

/** Default password, location string, weather key, script urls */
#define DEFAULT_PASSWORD          "opendoor"
#define DEFAULT_LOCATION          "Boston,MA"

#error Deliberate error - please edit 'defines.h' to add your Weather Underground API key (refer to https://opensprinkler.freshdesk.com/support/solutions/articles/5000017312-using-weather-adjustments )
#define DEFAULT_WEATHER_KEY       "0000000000000000"	// replace this key with your own, then delete the #error line above

#define DEFAULT_JAVASCRIPT_URL    "https://ui.opensprinkler.com/js"
#define DEFAULT_WEATHER_URL       "weather.opensprinkler.com"

/** Macro define of each option
  * Refer to OpenSprinkler.cpp for details on each option
  */
typedef enum
{
    OPTION_FW_VERSION = 0,
    OPTION_TIMEZONE,
    OPTION_USE_NTP,
    OPTION_USE_DHCP,
    OPTION_STATIC_IP1,
    OPTION_STATIC_IP2,
    OPTION_STATIC_IP3,
    OPTION_STATIC_IP4,
    OPTION_GATEWAY_IP1,
    OPTION_GATEWAY_IP2,
    OPTION_GATEWAY_IP3,
    OPTION_GATEWAY_IP4,
    OPTION_HTTPPORT_0,
    OPTION_HTTPPORT_1,
    OPTION_HW_VERSION,
    OPTION_EXT_BOARDS,
    OPTION_SEQUENTIAL_RETIRED,
    OPTION_STATION_DELAY_TIME,
    OPTION_MASTER_STATION,
    OPTION_MASTER_ON_ADJ,
    OPTION_MASTER_OFF_ADJ,
    OPTION_SENSOR_TYPE,
    OPTION_RAINSENSOR_TYPE,
    OPTION_WATER_PERCENTAGE,
    OPTION_DEVICE_ENABLE,
    OPTION_IGNORE_PASSWORD,
    OPTION_DEVICE_ID,
    OPTION_LCD_CONTRAST,
    OPTION_LCD_BACKLIGHT,
    OPTION_LCD_DIMMING,
    OPTION_BOOST_TIME,
    OPTION_USE_WEATHER,
    OPTION_NTP_IP1,
    OPTION_NTP_IP2,
    OPTION_NTP_IP3,
    OPTION_NTP_IP4,
    OPTION_ENABLE_LOGGING,
    OPTION_MASTER_STATION_2,
    OPTION_MASTER_ON_ADJ_2,
    OPTION_MASTER_OFF_ADJ_2,
    OPTION_FW_MINOR,
    OPTION_PULSE_RATE_0,
    OPTION_PULSE_RATE_1,
    OPTION_REMOTE_EXT_MODE,
    OPTION_RESET,
    NUM_OPTIONS	// total number of options
} OS_OPTION_t;

/** Log Data Type */
#define LOGDATA_STATION    0x00
#define LOGDATA_RAINSENSE  0x01
#define LOGDATA_RAINDELAY  0x02
#define LOGDATA_WATERLEVEL 0x03
#define LOGDATA_FLOWSENSE  0x04

#undef OS_HW_VERSION

/** Hardware defines */
#if defined(ARDUINO)

	#if F_CPU==8000000L
		#define OS_HW_VERSION (OS_HW_VERSION_BASE+20)
	#elif F_CPU==12000000L
		#define OS_HW_VERSION (OS_HW_VERSION_BASE+21)
	#elif F_CPU==16000000L
		#if defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega1284__)
			#define OS_HW_VERSION (OS_HW_VERSION_BASE+23)
		#else
			#define OS_HW_VERSION (OS_HW_VERSION_BASE+22)
		#endif
	#endif

/* ========================================================
   PINOUT AND DEFINES FOR OPENSPRINKLER_ARDUINO

   The following are the pins used by Dave's Arduino opensprinkler 
   You'll need to adjust them accordingly for your hardware config

   The pinouts below are arranged by pin number to ensure no conflicts
*/
#ifdef OPENSPRINKLER_ARDUINO
	#define PIN_D0				0		// Serial port - do not use
	#define PIN_D1				1		// Serial port - do not use
	#define PIN_LCD_D4			2		// Freetronics LCD - see Note 1 below
	#define PIN_LCD_BACKLIGHT	3		// Freetronics LCD backlight
	#define PIN_W5100_SD_CS		4		// W5100 SD card chip select - see Note 1 below
	#define PIN_LCD_D5			5		// Freetronics LCD
	#define PIN_LCD_D6			6		// Freetronics LCD
	#define PIN_LCD_D7			7		// Freetronics LCD

	#define PIN_LCD_RS			8		// Freetronics LCD
	#define PIN_LCD_EN			9		// Freetronics LCD
	#define PIN_W5100_ETHER_CS	10		// W5100 Ethernet chip select pin
	#define PIN_D11				11
	#define PIN_D12				12
	#define PIN_HEARTBEAT		13		// Pin to show a heartbeat LED 

	#define PIN_D14				14		// Serial 3 (don't use unless you really want to)
	#define PIN_D15				15		// Serial 3 (don't use unless you really want to)
	#define PIN_D16				16		// Serial 2 (don't use unless you really want to)
	#define PIN_D17				17		// Serial 2 (don't use unless you really want to)
	#define PIN_D18				18		// Serial 1 (don't use unless you really want to)
	#define PIN_D19				19		// Serial 1 (don't use unless you really want to)
	#define PIN_D20				20		// I2C Interface - SDA (do not use) 
	#define PIN_D21				21		// I2C Interface - SCL (do not use)

	#define PIN_STN_S09			22		// Watering stations 17 to 24 (Note 2 below)
	#define PIN_STN_S13			23		// Watering stations 17 to 24 (Note 2 below)
	#define PIN_STN_S10			24		// Watering stations 17 to 24 (Note 2 below)
	#define PIN_STN_S14			25		// Watering stations 17 to 24 (Note 2 below)
	#define PIN_STN_S11			26		// Watering stations 17 to 24 (Note 2 below)
	#define PIN_STN_S15			27		// Watering stations 17 to 24 (Note 2 below)
	#define PIN_STN_S12			28		// Watering stations 17 to 24 (Note 2 below)
	#define PIN_STN_S16			29		// Watering stations 17 to 24 (Note 2 below)

	#define PIN_STN_S17			30		// Watering stations 9 to 16 (Note 2 below)
	#define PIN_STN_S18			31		// Watering stations 9 to 16 (Note 2 below)
	#define PIN_STN_S19			32		// Watering stations 9 to 16 (Note 2 below)
	#define PIN_STN_S20			33		// Watering stations 9 to 16 (Note 2 below)
	#define PIN_ETHERCARD_SD_CS	34		// SD card chip select pin for Dave's ENC28J60 config
	#define PIN_D35				35		// not used (Note 4 below)
	#define PIN_STN_S21			36		// Watering stations 9 to 16 (Note 2 below)
	#define PIN_STN_S22			37		// Watering stations 9 to 16 (Note 2 below)
	#define PIN_STN_S23			38		// Watering stations 9 to 16 (Note 2 below)
	#define PIN_STN_S24			39		// Watering stations 9 to 16 (Note 2 below)

	#define PIN_STN_S04			40		// Watering stations 1 to 8 (Note 2 below)	
	#define PIN_STN_S08			41		// Watering stations 1 to 8 (Note 2 below)
	#define PIN_STN_S03			42		// Watering stations 1 to 8 (Note 2 below)
	#define PIN_STN_S07			43		// Watering stations 1 to 8 (Note 2 below)
	#define PIN_STN_S02			44		// Watering stations 1 to 8 (Note 2 below)
	#define PIN_STN_S06			45		// Watering stations 1 to 8 (Note 2 below)
	#define PIN_STN_S01			46		// Watering stations 1 to 8 (Note 2 below)
	#define PIN_STN_S05			47		// Watering stations 1 to 8 (Note 2 below)

	#define PIN_D48				48		// not used (Note 4 below)
	#define PIN_D49				49		// not used (Note 4 below)
	#define PIN_D50				50		// SPI Interface (don't use unless you want conflicts)
	#define PIN_D51				51		// SPI Interface (don't use unless you want conflicts)
	#define PIN_D52				52		// SPI Interface (don't use unless you want conflicts)
	#define PIN_ETHERCARD_CS	53		// Ethernet controller chip select pin for Daves' ENC28J60 config

	#define BUTTON_ADC_PIN		A0		// A0 is the LCD button ADC input
	#define PIN_A1				A1		// not used (Note 4 below)
	#define PIN_A2				A2		// not used (Note 4 below)
	#define PIN_A3				A3		// not used (Note 4 below)
	#define PIN_A4				A4		// not used (Note 4 below)
	#define PIN_A5				A5		// not used (Note 4 below)
	#define PIN_A6				A6		// not used (Note 4 below)
	#define PIN_A7				A7		// not used (Note 4 below)

	// The pins below are unused - adjust them for your hardware 
	#define PIN_LCD_CONTRAST	A8		// LCD contrast pin (Note 3 below / not used)  
	#define PIN_RF_DATA			A9		// RF data pin (Note 3 below / not used)
	#define PIN_RAINSENSOR		A10		// rain sensor (Note 3 below / not used)
	#define PIN_FLOWSENSOR		A11		// flow sensor (currently shared with rain sensor) (Note 3 below / not used)
  	#define PIN_FLOWSENSOR_INT	A12		// flow sensor interrupt pin (INT1)  (Note 3 below / not used)
	#define PIN_EXP_SENSE		A13		// expansion board sensing pin (A4) (Note 3 below / not used)
	#define PIN_CURR_SENSE		A14		// current sensing pin (A7) (Note 3 below / not used)
	#define PIN_CURR_DIGITAL	A15		// digital pin index for A7 (Note 3 below / not used)

	/* Notes:
	Note 1 -	D4 on the Freetronics LCD shield clashes with the chipselect pin for the SD card that is also D4 on some W5100 shields.
				You may need to jumper it to D2 as described at: http://forum.freetronics.com/viewtopic.php?t=770 

	Note 2 -	These pins provide the control signal to switch watering solenoids on and off
				(i.e. not using a shift register like the regular opensprinkler hardware) 

	Note 3 -	This define is not used by opensprinkler_arduino hardware - it is just set to an unused pin / should be harmless
				You'll need to set the correct pins for these items if you have them connected

	Note 4 -	You can use these pins for an extra expansion board if you need (must be in increments of x 8)
	*/

	// Define the chipselect pins for all SPI devices attached to the arduino
	// Unused pins needs to be pulled high otherwise SPI doesn't work properly
	#define SPI_DEVICES   4 		  // number of SPI devices
	const uint8_t spi_cs_pin[] =	  // CS pin for each device
	{
		PIN_W5100_SD_CS,
		PIN_W5100_ETHER_CS,
		PIN_ETHERCARD_SD_CS,		
		PIN_ETHERCARD_CS
	};

	#ifdef OPENSPRINKLER_ARDUINO_DISCRETE
		/* READ ME - PIN_EXT_BOARDS defines the total number of discrete digital IO pins
		used to control watering stations. There are 8 stations per extender board, that
		MUST have PIN_EXT_BOARDS x 8  pins defined below (otherwise you'll get out of range
		issues with the array of pins defined in OpenSprinklerGen2.cpp) */

		#define MAX_EXT_BOARDS		2  // maximum number of exp. boards (each expands 8 stations)
		#define PORT_RF				PORTA
		#define PINX_RF				PINA3
	#endif

	#ifdef OPENSPRINKLER_ARDUINO_FREETRONICS_LCD
		// some example macros with friendly labels for LCD backlight / pin control
		#define LCD_BACKLIGHT_OFF()			digitalWrite( PIN_LCD_BACKLIGHT, LOW )
		#define LCD_BACKLIGHT_ON()			digitalWrite( PIN_LCD_BACKLIGHT, HIGH )
		#define LCD_BACKLIGHT(state)		{if( state ){digitalWrite( PIN_LCD_BACKLIGHT, HIGH );}else{digitalWrite( PIN_LCD_BACKLIGHT, LOW );} }

		// ADC readings expected for the 5 buttons on the ADC input
		#define RIGHT_10BIT_ADC		0		// right
		#define UP_10BIT_ADC		145		// up
		#define DOWN_10BIT_ADC		329		// down
		#define LEFT_10BIT_ADC		505		// left
		#define SELECT_10BIT_ADC	741		// select
		#define BUTTONHYSTERESIS	10		// hysteresis for valid button sensing window

		#define BUTTON_RIGHT		1		// values used for detecting analog buttons
		#define BUTTON_UP			2		// 
		#define BUTTON_DOWN			3		// 
		#define BUTTON_LEFT			4		// 
		#define BUTTON_SELECT		5		//   
	#endif // OPENSPRINKLER_ARDUINO_FREETRONICS_LCD

	typedef const char prog_char;
	typedef const char prog_uchar;

	// Auto reboot time
	#define REBOOT_HR				12		// hour to perform daily reboot
	#define REBOOT_MIN				00		// min  to perform daily reboot
	#define REBOOT_SEC				00		// sec  to perform daily reboot

#endif // OPENSPRINKLER_ARDUINO

#ifndef OPENSPRINKLER_ARDUINO_DISCRETE

	// maximum number of exp. boards (each expands 8 stations)
	#define MAX_EXT_BOARDS		5  

	// hardware pins
	#define PIN_BUTTON_1		31		// button 1
	#define PIN_BUTTON_2		30		// button 2
	#define PIN_BUTTON_3		29		// button 3
	#define PIN_RF_DATA			28		// RF data pin
	#define PORT_RF				PORTA
	#define PINX_RF				PINA3

	#define PIN_SR_LATCH		3		// shift register latch pin
	#define PIN_SR_DATA			21		// shift register data pin
	#define PIN_SR_CLOCK		22		// shift register clock pin
	#define PIN_SR_OE			1		// shift register output enable pin
#endif // OPENSPRINKLER_ARDUINO_DISCRETE

#ifndef OPENSPRINKLER_ARDUINO_FREETRONICS_LCD
	// regular 16x2 LCD pin defines
	#define PIN_LCD_RS			19		// LCD rs pin
	#define PIN_LCD_EN			18		// LCD enable pin
	#define PIN_LCD_D4			20		// LCD d4 pin
	#define PIN_LCD_D5			21		// LCD d5 pin
	#define PIN_LCD_D6			22		// LCD d6 pin
	#define PIN_LCD_D7			23		// LCD d7 pin
	#define PIN_LCD_BACKLIGHT	12		// LCD backlight pin
	#define PIN_LCD_CONTRAST	13		// LCD contrast pin
#endif // OPENSPRINKLER_ARDUINO_FREETRONICS_LCD

#ifndef OPENSPRINKLER_ARDUINO_DISCRETE
	// DC controller pin defines
	#define PIN_BOOST			20		// booster pin
	#define PIN_BOOST_EN		23		// boost voltage enable pin
#endif // OPENSPRINKLER_ARDUINO_DISCRETE

#ifndef OPENSPRINKLER_ARDUINO_DISCRETE
	#define PIN_RAINSENSOR			11    // rain sensor is connected to pin D3
	#define PIN_FLOWSENSOR			11    // flow sensor (currently shared with rain sensor, change if using a different pin)
	#define PIN_FLOWSENSOR_INT		1     // flow sensor interrupt pin (INT1)
	#define PIN_EXP_SENSE			4     // expansion board sensing pin (A4)
	#define PIN_CURR_SENSE			7     // current sensing pin (A7)
	#define PIN_CURR_DIGITAL		24    // digital pin index for A7
#endif

// Ethernet buffer size
#if defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega1284__)
	#define ETHER_BUFFER_SIZE		1500  // ATmega1284 has 16K RAM, so use a bigger buffer
#else
	#define ETHER_BUFFER_SIZE		960   // ATmega644 has 4K RAM, so use a smaller buffer
#endif

#ifdef OPENSPRINKLER_ARDUINO_WDT
	#define 	wdt_reset()   __asm__ __volatile__ ("wdr")  // watchdog timer reset
#endif	// OPENSPRINKLER_ARDUINO_WDT

#define SERIAL_DEBUG
#if defined(SERIAL_DEBUG) /** Serial debug functions */
	#define DEBUG_BEGIN(x)		Serial.begin(x)
	#define DEBUG_PRINT(x)		Serial.print(x)
	#define DEBUG_PRINTF(x,y)	Serial.print(x, y)
	#define DEBUG_PRINTLN(x)	Serial.println(x)
#else
	#define DEBUG_BEGIN(x)		{}
	#define DEBUG_PRINT(x)		{}
	#define DEBUG_PRINTF(x,y)	{}
	#define DEBUG_PRINTLN(x)	{}
#endif

typedef unsigned char   uint8_t;
typedef unsigned int    uint16_t;
typedef int int16_t;

#else // Hardware defines for RPI/BBB

/** OSPi pin defines */
#if defined(OSPI)

	#define OS_HW_VERSION    OSPI_HW_VERSION_BASE
	#define PIN_SR_LATCH      22    // shift register latch pin
	#define PIN_SR_DATA       27    // shift register data pin
	#define PIN_SR_DATA_ALT   21    // shift register data pin (alternative, for RPi 1 rev. 1 boards)
	#define PIN_SR_CLOCK       4    // shift register clock pin
	#define PIN_SR_OE         17    // shift register output enable pin
	#define PIN_RAINSENSOR    14    // rain sensor
	#define PIN_FLOWSENSOR    14    // flow sensor (currently shared with rain sensor, change if using a different pin)
	#define PIN_RF_DATA       15    // RF transmitter pin
	#define PIN_BUTTON_1      23    // button 1
	#define PIN_BUTTON_2      24    // button 2
	#define PIN_BUTTON_3      25    // button 3

/** BBB pin defines */
#elif defined(OSBO)

	#define OS_HW_VERSION    OSBO_HW_VERSION_BASE
	// these are gpio pin numbers, refer to
	// https://github.com/mkaczanowski/BeagleBoneBlack-GPIO/blob/master/GPIO/GPIOConst.cpp
	#define PIN_SR_LATCH      60    // P9_12, shift register latch pin
	#define PIN_SR_DATA       30    // P9_11, shift register data pin
	#define PIN_SR_CLOCK      31    // P9_13, shift register clock pin
	#define PIN_SR_OE         50    // P9_14, shift register output enable pin
	#define PIN_RAINSENSOR    48    // P9_15, rain sensor is connected to pin D3
	#define PIN_FLOWSENSOR    48    // flow sensor (currently shared with rain sensor, change if using a different pin)
	#define PIN_RF_DATA       51    // RF transmitter pin

#else
	// For Linux or other software simulators
	// use fake hardware pins
	#if defined(DEMO)
		#define OS_HW_VERSION 255   // assign hardware number 255 to DEMO firmware
	#else
		#define OS_HW_VERSION SIM_HW_VERSION_BASE
	#endif
	#define PIN_SR_LATCH    0
	#define PIN_SR_DATA     0
	#define PIN_SR_CLOCK    0
	#define PIN_SR_OE       0
	#define PIN_RAINSENSOR  0
	#define PIN_FLOWSENSOR  0
	#define PIN_RF_DATA     0
#endif

#define ETHER_BUFFER_SIZE   16384

#define DEBUG_BEGIN(x)          {}  /** Serial debug functions */
#define ENABLE_DEBUG
#if defined(ENABLE_DEBUG)
	inline  void DEBUG_PRINT ( int x )
	{
		printf ( "%d", x );
	}
	inline  void DEBUG_PRINT ( const char*s )
	{
		printf ( "%s", s );
	}
	#define DEBUG_PRINTLN(x)        {DEBUG_PRINT(x);printf("\n");}
#else
	#define DEBUG_PRINT(x) {}
	#define DEBUG_PRINTLN(x) {}
#endif

inline void itoa ( int v,char *s,int b )
{
    sprintf ( s,"%d",v );
}
inline void ultoa ( unsigned long v,char *s,int b )
{
    sprintf ( s,"%lu",v );
}
#define now()       time(0)

/** Re-define avr-specific (e.g. PGM) types to use standard types */
#define pgm_read_byte(x) *(x)
#define PSTR(x)      x
#define strcat_P     strcat
#define strcpy_P     strcpy
#define PROGMEM
typedef const char		prog_char;
typedef const char		prog_uchar;
typedef const char*		PGM_P;
typedef unsigned char   uint8_t;
typedef short           int16_t;
typedef unsigned short  uint16_t;
typedef bool			boolean;

#endif  // end of Hardawre defines

#define TMP_BUFFER_SIZE     128  // scratch buffer size

/** Other defines */
// button values
#define BUTTON_1            0x01
#define BUTTON_2            0x02
#define BUTTON_3            0x04

// button status values
#define BUTTON_NONE         0x00  // no button pressed
#define BUTTON_MASK         0x0F  // button status mask
#define BUTTON_FLAG_HOLD    0x80  // long hold flag
#define BUTTON_FLAG_DOWN    0x40  // down flag
#define BUTTON_FLAG_UP      0x20  // up flag

// button timing values
#define BUTTON_DELAY_MS        1  // short delay (milliseconds)
#define BUTTON_HOLD_MS      1000  // long hold expiration time (milliseconds)

// button mode values
#define BUTTON_WAIT_NONE       0  // do not wait, return value immediately
#define BUTTON_WAIT_RELEASE    1  // wait until button is release
#define BUTTON_WAIT_HOLD       2  // wait until button hold time expires

#define DISPLAY_MSG_MS      2000  // message display time (milliseconds)

typedef unsigned char byte;
typedef unsigned long ulong;

#endif  // _DEFINES_H


