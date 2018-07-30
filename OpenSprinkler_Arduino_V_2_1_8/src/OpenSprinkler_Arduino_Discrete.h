/* ==========================================================================================================
This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware

Version:     Opensprinkler 2.1.8

Date:        July 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Refer to the README file for more information

========================================================================================================== */

#ifndef _OPENSPRINKLER_ARDUINO_DISCRETE_H_
#define _OPENSPRINKLER_ARDUINO_DISCRETE_H_

#include <Arduino.h>
#include "OpenSprinkler_Arduino_Debug.h"
#include "OpenSprinkler_Arduino_Pins.h"

class OpenSprinklerArduinoDiscreteClass
{
protected:
    // pin definitions for discrete pinouts
    const static uint8_t pin[];

    // quantity of discrete pinouts
    const static uint8_t pin_qty;

    // maximum boards (each with 8 stations) - includes the controller itself
    const static uint8_t board_qty;

 public:
	void begin();
    void apply(byte enabled, byte *stationBytes, byte stationBoards);
    void set(byte boardID, byte stationByte);
};

extern OpenSprinklerArduinoDiscreteClass OpenSprinklerDiscrete;

#endif

