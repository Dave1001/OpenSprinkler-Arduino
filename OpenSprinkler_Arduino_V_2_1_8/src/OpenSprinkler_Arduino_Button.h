/* ==========================================================================================================
This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware:

Version:     Opensprinkler Arduino 2.1.8

Date:        July 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Refer to the README file for more information

========================================================================================================== */

#ifndef _OPENSPRINKLER_ARDUINO_BUTTON_h
#define _OPENSPRINKLER_ARDUINO_BUTTON_h

#include <Arduino.h>
//#include "time/TimeLib.h"
#include "OpenSprinkler_Arduino_Debug.h"
#include "OpenSprinkler_Arduino_Pins.h"

#ifndef _DEFINES_H
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
#endif

    // Macros with friendly labels for LCD backlight / pin control
    #define LCD_BACKLIGHT_OFF()			digitalWrite( PIN_LCD_BACKLIGHT, LOW )
    #define LCD_BACKLIGHT_ON()			digitalWrite( PIN_LCD_BACKLIGHT, HIGH )
    #define LCD_BACKLIGHT_STATE(state)	{if( state ){digitalWrite( PIN_LCD_BACKLIGHT, HIGH );}else{digitalWrite( PIN_LCD_BACKLIGHT, LOW );} }

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

class OpenSprinkler_Arduino_ButtonClass
{
protected:
    byte sample();
    byte readBusy(byte pinButton, byte waitMode, byte button, byte isHolding);

 public:
	void begin();
    byte read(byte waitMode);
    //void print();
};

extern OpenSprinkler_Arduino_ButtonClass OpenSprinklerButton;

#endif

