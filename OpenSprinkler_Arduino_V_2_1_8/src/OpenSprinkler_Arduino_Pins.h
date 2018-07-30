/* ==========================================================================================================
This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware:

Version:     Opensprinkler Arduino 2.1.8

Date:        July 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Refer to the README file for more information

========================================================================================================== */
#pragma once

#ifndef _OS_ARDUINO_PINS_H_
#define _OS_ARDUINO_PINS_H_

#include <Arduino.h>
#include "Opensprinkler_Arduino_Pins_Undef.h"

/*
PINOUT AND DEFINES FOR OPENSPRINKLER_ARDUINO

The following are the pins used by Dave's Arduino opensprinkler
This assumes an Arduino ATMEGA2560 - you'll need to adjust the
pins accordingly for your hardware config

The pinouts below are arranged by pin number to ensure no conflicts
*/
#define PIN_D0				0		// Not assigned / ATMEGA2560 Serial 0
#define PIN_D1				1		// Not assigned / ATMEGA2560 Serial 0
#define PIN_LCD_D4			2		// Freetronics LCD (Note 1 below)
#define PIN_LCD_BACKLIGHT	3		// Freetronics LCD backlight
#define PIN_W5100_SD_CS		4		// W5100 SD Card Chipselect (Note 1 below)
#define PIN_LCD_D5			5		// Freetronics LCD
#define PIN_LCD_D6			6		// Freetronics LCD
#define PIN_LCD_D7			7		// Freetronics LCD

#define PIN_LCD_RS			8		// Freetronics LCD
#define PIN_LCD_EN			9		// Freetronics LCD
#define PIN_W5100_ETHER_CS	10		// W5100 Ethernet Chipselect
#define PIN_D11		        11      // Not assigned (Note 4 below)
#define PIN_D12	            12      // Not assigned (Note 4 below)
#define PIN_HEARTBEAT		13		// Pin to show a heartbeat LED 

#define PIN_BUTTON_1		14		// Not assigned / ATMEGA2560 Serial 3 
#define PIN_BUTTON_2		15		// Not assigned / ATMEGA2560 Serial 3 
#define PIN_BUTTON_3		16		// Not assigned / ATMEGA2560 Serial 2 
#define PIN_D17				17		// Not assigned / ATMEGA2560 Serial 2 
#define PIN_D18				18		// GPIO Watering Station (Note 2 below)
#define PIN_D19				19		// GPIO Watering Station (Note 2 below)
#define PIN_D20				20		// I2C Interface - SDA (do not use) 
#define PIN_D21				21		// I2C Interface - SCL (do not use)

#define PIN_STN_S09			22		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S13			23		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S10			24		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S14			25		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S11			26		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S15			27		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S12			28		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S16			29		// GPIO Watering Station (Note 2 below)

#define PIN_STN_S17			30		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S18			31		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S19			32		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S20			33		// GPIO Watering Station (Note 2 below)
#define PIN_ENC28J60_SD_CS	34		// ENC28J60 SD Card Chipselect
#define PIN_D35		        35		// Not assigned (Note 4 below)
#define PIN_STN_S21			36		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S22			37		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S23			38		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S24			39		// GPIO Watering Station (Note 2 below)

#define PIN_STN_S04			40		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S08			41		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S03			42		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S07			43		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S02			44		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S06			45		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S01			46		// GPIO Watering Station (Note 2 below)
#define PIN_STN_S05			47		// GPIO Watering Station (Note 2 below)

#define PIN_BOOST			48		// Booster pin (Note 3 below) (default for opensprinkler is pin 20)
#define PIN_BOOST_EN		49		// Boost voltage enable pin (Note 3 below) (default for opensprinkler is pin 23)
#define PIN_D50				50		// Ethernet and SD Card SPI Interface
#define PIN_D51				51		// Ethernet and SD Card SPI Interface
#define PIN_D52				52		// Ethernet and SD Card SPI Interface
#define PIN_ENC28J60_CS	    53		// ENC28J60 Ethernet Chipselect

#define BUTTON_ADC_PIN		A0		// A0 is the LCD button ADC input
#define PIN_ANALOG1         A1		// Not assigned (Note 4 below)
#define PIN_RFTX		    A2		// Assigned to PIN_RFTX (Note 3 below) (default for opensprinkler is pin 28)
#define PINX_RF		        A3		// Assigned to PINX_RF (Note 3 below)
#define PIN_SR_LATCH		A4		// Assigned to PIN_SR_LATCH (Note 3 below)
#define PIN_SR_DATA		    A5		// Assigned to PIN_SR_DATA (Note 3 below)
#define PIN_SR_CLOCK		A6		// Assigned to PIN_SR_CLOCK (Note 3 below)
#define PIN_SR_OE		    A7		// Assigned to PIN_SR_OE (Note 3 below)

// The pins below are unused - adjust them for your hardware 
#define PIN_LCD_CONTRAST	A8		// LCD contrast pin (Note 3 below / not used)  
#define PIN_RF_DATA			A9		// RF data pin (Note 3 below / not used)
#define PIN_RAINSENSOR		A10		// Rain sensor (Note 3 below / not used)
#define PIN_FLOWSENSOR		A11		// Flow sensor (currently shared with rain sensor) (Note 3 below / not used)
#define PIN_FLOWSENSOR_INT	A12		// Flow sensor interrupt pin (INT1)  (Note 3 below / not used)
#define PIN_EXP_SENSE		A13		// Expansion board sensing pin (A4) (Note 3 below / not used)
#define PIN_CURR_SENSE		A14		// Current sensing pin (A7) (Note 3 below / not used)
#define PIN_CURR_DIGITAL	A15		// Digital pin index for A7 (Note 3 below / not used)

#define PORT_RF		        PORTA   // RF Data Port definition

/* 
Notes:

Note 1 -	D4 on the Freetronics LCD shield clashes with the chipselect pin for the SD card that is also D4 on some W5100 shields.
            You may need to jumper it to D2 as described at: http://forum.freetronics.com/viewtopic.php?t=770

Note 2 -	These pins provide the GPIO control signal to switch watering solenoids on and off
            (i.e. not using a shift register like the regular opensprinkler hardware). If your processor has more or less pins,
            then define them in the PIN_FREE_LIST below so they can be allocated as a watering station. 

Note 3 -	This define is not used by Opensprinkler_arduino hardware - it is just set to an unused pin / should be harmless
            You'll need to set the correct pins for these items if you have them connected

Note 4 -	You can use these pins for an extra expansion board or GPIO if you need
*/

// Define the chipselect pins for all SPI devices attached to the arduino
// Unused pins needs to be pulled high otherwise SPI doesn't work properly
#define PIN_SPI_DEVICES   4 		    // number of SPI devices
const uint8_t PIN_SPI_CS_LIST[] =	    // CS pin for each device
{
    PIN_W5100_SD_CS,
    PIN_W5100_ETHER_CS,
    PIN_ENC28J60_SD_CS,
    PIN_ENC28J60_CS
};

// Free GPIO pins
#define PIN_FREE_LIST { \
        PIN_D18, \
        PIN_D18, \
        PIN_STN_S09, \
        PIN_STN_S13, \
        PIN_STN_S10, \
        PIN_STN_S14, \
        PIN_STN_S11, \
        PIN_STN_S15, \
        PIN_STN_S12, \
        PIN_STN_S16, \
        PIN_STN_S17, \
        PIN_STN_S18, \
        PIN_STN_S19, \
        PIN_STN_S20, \
        PIN_STN_S21, \
        PIN_STN_S22, \
        PIN_STN_S23, \
        PIN_STN_S24, \
        PIN_STN_S04, \
        PIN_STN_S08, \
        PIN_STN_S03, \
        PIN_STN_S07, \
        PIN_STN_S02, \
        PIN_STN_S06, \
        PIN_STN_S01, \
        PIN_STN_S05 }

// Invert these if needed for your hardware
#define PIN_STATE_ON    HIGH     
#define PIN_STATE_OFF   LOW

// Invert these if needed for your hardware
#define LED_STATE_ON    HIGH     
#define LED_STATE_OFF   LOW

#endif  // _OS_ARDUINO_PINS_H_




