#pragma once
/* ==========================================================================================================
This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware:

Version:     Opensprinkler Arduino 2.1.8

Date:        July 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Refer to the README file for more information

========================================================================================================== */

#ifndef _OS_ARDUINO_UNDEF_H_
#define _OS_ARDUINO_UNDEF_H_

#ifdef PIN_BUTTON_1 
    #undef PIN_BUTTON_1 
#endif

#ifdef PIN_BUTTON_2 
    #undef PIN_BUTTON_2 
#endif

#ifdef PIN_BUTTON_3 
    #undef PIN_BUTTON_3 
#endif

#ifdef PIN_RFTX 
    #undef PIN_RFTX 
#endif

#ifdef PORT_RF 
    #undef PORT_RF 
#endif

#ifdef PINX_RF 
    #undef PINX_RF 
#endif

#ifdef PIN_SR_LATCH 
    #undef PIN_SR_LATCH 
#endif

#ifdef PIN_SR_DATA 
    #undef PIN_SR_DATA 
#endif

#ifdef PIN_SR_CLOCK 
    #undef PIN_SR_CLOCK 
#endif

#ifdef PIN_SR_OE 
    #undef PIN_SR_OE 
#endif

#ifdef PIN_LCD_RS 
    #undef PIN_LCD_RS 
#endif

#ifdef PIN_LCD_EN 
    #undef PIN_LCD_EN 
#endif

#ifdef PIN_LCD_D4 
    #undef PIN_LCD_D4 
#endif

#ifdef PIN_LCD_D5 
    #undef PIN_LCD_D5 
#endif

#ifdef PIN_LCD_D6 
    #undef PIN_LCD_D6 
#endif

#ifdef PIN_LCD_D7 
    #undef PIN_LCD_D7 
#endif

#ifdef PIN_LCD_BACKLIGHT 
    #undef PIN_LCD_BACKLIGHT 
#endif

#ifdef PIN_LCD_CONTRAST 
    #undef PIN_LCD_CONTRAST 
#endif

#ifdef PIN_BOOST 
    #undef PIN_BOOST 
#endif

#ifdef PIN_BOOST_EN 
    #undef PIN_BOOST_EN 
#endif

#ifdef PIN_ETHER_CS 
    #undef PIN_ETHER_CS 
#endif

#ifdef PIN_SD_CS 
    #undef PIN_SD_CS 
#endif

#ifdef PIN_RAINSENSOR 
    #undef PIN_RAINSENSOR 
#endif

#ifdef PIN_FLOWSENSOR 
    #undef PIN_FLOWSENSOR 
#endif

#ifdef PIN_FLOWSENSOR_INT 
    #undef PIN_FLOWSENSOR_INT 
#endif

#ifdef PIN_EXP_SENSE 
    #undef PIN_EXP_SENSE 
#endif

#ifdef PIN_CURR_SENSE 
    #undef PIN_CURR_SENSE 
#endif

#ifdef PIN_CURR_DIGITAL 
    #undef PIN_CURR_DIGITAL 
#endif

//#ifdef IOEXP_PIN 
//    #undef IOEXP_PIN 
//#endif
//
//#ifdef MAIN_I2CADDR 
//    #undef MAIN_I2CADDR 
//#endif
//
//#ifdef MAIN_INPUTMASK 
//    #undef MAIN_INPUTMASK 
//#endif
//
//#ifdef ACDR_I2CADDR 
//    #undef ACDR_I2CADDR 
//#endif
//
//#ifdef DCDR_I2CADDR 
//    #undef DCDR_I2CADDR 
//#endif
//
//#ifdef LADR_I2CADDR 
//    #undef LADR_I2CADDR 
//#endif
//
//#ifdef EXP_I2CADDR_BASE 
//    #undef EXP_I2CADDR_BASE 
//#endif
//
//#ifdef LCD_I2CADDR 
//    #undef LCD_I2CADDR 
//#endif
//
//#ifdef PIN_RFRX 
//    #undef PIN_RFRX 
//#endif
//
//#ifdef PIN_PWR_RX 
//    #undef PIN_PWR_RX 
//#endif
//
//#ifdef PIN_PWR_TX 
//    #undef PIN_PWR_TX 
//#endif
//
//#ifdef PIN_SENSOR1 
//    #undef PIN_SENSOR1 
//#endif
//
//#ifdef PIN_SENSOR2 
//    #undef PIN_SENSOR2 
//#endif

#ifdef PIN_FREE_LIST 
    #undef PIN_FREE_LIST 
#endif
//
//#ifdef PIN_SR_DATA_ALT 
//    #undef PIN_SR_DATA_ALT 
//#endif

#endif  // _OS_ARDUINO_UNDEF_H_



