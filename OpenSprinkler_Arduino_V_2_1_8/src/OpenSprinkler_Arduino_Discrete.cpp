/* ==========================================================================================================
This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware

Version:     Opensprinkler 2.1.8

Date:        July 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Refer to the README file for more information

========================================================================================================== */

#include "OpenSprinkler_Arduino_Discrete.h"

const uint8_t OpenSprinklerArduinoDiscreteClass::board_qty = 3;
const uint8_t OpenSprinklerArduinoDiscreteClass::pin_qty = 24;
const uint8_t OpenSprinklerArduinoDiscreteClass::pin[24] =
{
    PIN_STN_S01, PIN_STN_S02, PIN_STN_S03, PIN_STN_S04, PIN_STN_S05, PIN_STN_S06, PIN_STN_S07, PIN_STN_S08,
    PIN_STN_S09, PIN_STN_S10, PIN_STN_S11, PIN_STN_S12, PIN_STN_S13, PIN_STN_S14, PIN_STN_S15, PIN_STN_S16,
    PIN_STN_S17, PIN_STN_S18, PIN_STN_S19, PIN_STN_S20, PIN_STN_S21, PIN_STN_S22, PIN_STN_S23, PIN_STN_S24
};

void OpenSprinklerArduinoDiscreteClass::begin()
{
    // initialize the Digital IO pins as outputs:
    for (uint8_t i = 0; i < pin_qty; i++)
    {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], PIN_STATE_OFF);
    }
}

void OpenSprinklerArduinoDiscreteClass::apply(byte enabled, byte *stationBytes, byte stationBoards)
{
    // Shift out all station board values from the lowest to the highest
    // Any station boards greater than board_qty are ignored
    for (byte boardID = 0; boardID < board_qty; boardID++)
    {
        if (enabled)
            set(boardID, stationBytes[boardID]);
        else
        {
            set(boardID, 0);    // all off
        }
    }
}

void OpenSprinklerArduinoDiscreteClass::set(byte boardID, byte stationByte)
{
    uint8_t pin_num, pin_state;

    // Shift out all station bit values from the highest bit to the lowest
    // Any station pins greater than pin_qty are ignored
    for (uint8_t stationID = 0; stationID < 8; stationID++)
    {
        pin_num = (boardID * 8) + stationID;
        if (pin_num > pin_qty)
            break;

        pin_state = (stationByte & ((byte)1 << stationID)) ? PIN_STATE_ON : PIN_STATE_OFF;

        digitalWrite(pin[pin_num], pin_state);
    }
}

OpenSprinklerArduinoDiscreteClass OpenSprinklerDiscrete;

