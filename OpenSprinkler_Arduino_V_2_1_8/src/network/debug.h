/* ==========================================================================================================
This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware:

Version:     Opensprinkler 2.1.8

Date:        May 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Refer to the README file for more information

========================================================================================================== */
#pragma once

#ifndef _SERIAL_DEBUG_H_
#define _SERIAL_DEBUG_H_

#ifndef SERIAL_DEBUG
#define SERIAL_DEBUG
#endif

#ifdef DEBUG_BEGIN
#undef DEBUG_BEGIN
#endif

#ifdef DEBUG_PRINT
#undef DEBUG_PRINT
#endif

#ifdef DEBUG_PRINTLN
#undef DEBUG_PRINTLN
#endif

#ifdef DEBUG_PRINTIP
#undef DEBUG_PRINTIP
#endif

#ifdef DEBUG_DELAY
#undef DEBUG_DELAY
#endif

#ifdef DEBUG_PRINTF
#undef DEBUG_PRINTF
#endif

#ifdef DEBUG_FLUSH
#undef DEBUG_FLUSH
#endif

#ifdef DEBUG_STREAM
#undef DEBUG_STREAM
#endif

#ifdef SERIAL_DEBUG
#define DEBUG_BEGIN(x)      Serial.begin(x)
#define DEBUG_PRINT(x)      Serial.print(x)
#define DEBUG_PRINTLN(x)    Serial.println(x)
#define DEBUG_PRINTIP(x)    ether.printIp("IP:",x)
#define DEBUG_DELAY(x)      delay(x)
#define DEBUG_PRINTF(x,y)   Serial.print(x, y)
#define DEBUG_FLUSH()       Serial.flush()
#define DEBUG_STREAM(...)	Serial << __VA_ARGS__

#else
#define DEBUG_BEGIN(x)      {}
#define DEBUG_PRINT(x)      {}
#define DEBUG_PRINTLN(x)    {}
#define DEBUG_PRINTIP(x)    {}
#define DEBUG_DELAY(x)      {}
#define DEBUG_PRINTF(x,y)   {}
#define DEBUG_FLUSH(...)    {}
#define DEBUG_STREAM(...)	{}
#endif

#endif  // _DEBUG_H_
