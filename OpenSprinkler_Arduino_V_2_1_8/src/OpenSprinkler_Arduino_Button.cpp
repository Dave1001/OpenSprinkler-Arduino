/* ==========================================================================================================
This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware:

Version:     Opensprinkler Arduino 2.1.8

Date:        July 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Refer to the README file for more information

========================================================================================================== */

#include "OpenSprinkler_Arduino_Button.h"

void OpenSprinkler_Arduino_ButtonClass::begin()
{
    // initialize the Analog IO pin as input
    pinMode(BUTTON_ADC_PIN, INPUT);
}

// Wait for button
byte OpenSprinkler_Arduino_ButtonClass::readBusy(byte pinButton, byte waitMode, byte button, byte isHolding)
{
    int holdTime = 0;

    if (waitMode == BUTTON_WAIT_NONE || (waitMode == BUTTON_WAIT_HOLD && isHolding))
    {
        if (this->sample() == BUTTON_NONE) return BUTTON_NONE;
        return button | (isHolding ? BUTTON_FLAG_HOLD : 0);
    }

    while (this->sample() != BUTTON_NONE &&
        (waitMode == BUTTON_WAIT_RELEASE || (waitMode == BUTTON_WAIT_HOLD && holdTime<BUTTON_HOLD_MS)))
    {
        delay(BUTTON_DELAY_MS);
        holdTime += BUTTON_DELAY_MS;
    };
    if (isHolding || holdTime >= BUTTON_HOLD_MS)
        button |= BUTTON_FLAG_HOLD;
    return button;
}

// Read button and returns button value 'OR'ed with flag bits
byte OpenSprinkler_Arduino_ButtonClass::read(byte waitMode)
{
    static byte old = BUTTON_NONE;
    byte curr = BUTTON_NONE;
    byte isHolding = (old&BUTTON_FLAG_HOLD);

    delay(BUTTON_DELAY_MS);

    curr = this->sample();
    // A normal opensprinkler is only 3 buttons - map them to the five buttons of the LCD shield
    // Button 1 = Increase  = Up and Right
    // Button 2 = Decrease = Down and Left
    // Button 3 = Select = Select
    switch (curr)
    {
    case BUTTON_UP:
    case BUTTON_RIGHT:
        curr = this->readBusy(BUTTON_ADC_PIN, waitMode, BUTTON_1, isHolding);
        break;

    case BUTTON_DOWN:
    case BUTTON_LEFT:
        curr = this->readBusy(BUTTON_ADC_PIN, waitMode, BUTTON_2, isHolding);
        break;

    case BUTTON_SELECT:
        curr = this->readBusy(BUTTON_ADC_PIN, waitMode, BUTTON_3, isHolding);
        break;

    default:
        curr = BUTTON_NONE;
    }

    /* set flags in return value */
    byte ret = curr;
    if (!(old&BUTTON_MASK) && (curr&BUTTON_MASK))
        ret |= BUTTON_FLAG_DOWN;
    if ((old&BUTTON_MASK) && !(curr&BUTTON_MASK))
        ret |= BUTTON_FLAG_UP;

    old = curr;
    return ret;
}

byte OpenSprinkler_Arduino_ButtonClass::sample()
{
    unsigned int buttonVoltage;

    //read the button ADC pin voltage
    buttonVoltage = analogRead(BUTTON_ADC_PIN);

    //sense if the voltage falls within valid voltage windows
    if (buttonVoltage < (RIGHT_10BIT_ADC + BUTTONHYSTERESIS))
    {
        return BUTTON_RIGHT;
    }
    else if (buttonVoltage >= (UP_10BIT_ADC - BUTTONHYSTERESIS)
        && buttonVoltage <= (UP_10BIT_ADC + BUTTONHYSTERESIS))
    {
        return BUTTON_UP;
    }
    else if (buttonVoltage >= (DOWN_10BIT_ADC - BUTTONHYSTERESIS)
        && buttonVoltage <= (DOWN_10BIT_ADC + BUTTONHYSTERESIS))
    {
        return BUTTON_DOWN;
    }
    else if (buttonVoltage >= (LEFT_10BIT_ADC - BUTTONHYSTERESIS)
        && buttonVoltage <= (LEFT_10BIT_ADC + BUTTONHYSTERESIS))
    {
        return BUTTON_LEFT;
    }
    else if (buttonVoltage >= (SELECT_10BIT_ADC - BUTTONHYSTERESIS)
        && buttonVoltage <= (SELECT_10BIT_ADC + BUTTONHYSTERESIS))
    {
        return BUTTON_SELECT;
    }
    else
        return BUTTON_NONE;
}

//void OpenSprinkler_Arduino_ButtonClass::print()
//{
//    if (hour() <= 9)
//        DEBUG_PRINT(F("0"));
//    DEBUG_PRINT(hour());
//    DEBUG_PRINT(F(":"));
//
//    if (minute() <= 9)
//        DEBUG_PRINT(F("0"));
//    DEBUG_PRINT(minute());
//    DEBUG_PRINT(F(":"));
//
//    if (second() <= 9)
//        DEBUG_PRINT(F("0"));
//    DEBUG_PRINT(second());
//    DEBUG_PRINT(F(" Buttons: TODO"));
//
//    DEBUG_PRINTLN();
//}

OpenSprinkler_Arduino_ButtonClass OpenSprinklerButton;

