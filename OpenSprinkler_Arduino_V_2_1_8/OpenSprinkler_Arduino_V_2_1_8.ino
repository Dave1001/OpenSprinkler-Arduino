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

#include <Arduino.h>
#include <Wire.h>

#ifndef ESP8266
#include <SdFat.h>
#endif

#include "OpenSprinkler.h"

extern OpenSprinkler os;

#ifdef OPENSPRINKLER_ARDUINO_W5100  
    EtherCardWrapper<EtherCardW5100> ether;
    byte EtherCardW5100::buffer[ETHER_BUFFER_SIZE];
#elif defined (OPENSPRINKLER_ARDUINO_ENC28J60)
    EtherCardWrapper<EtherCard> ether;
    byte Ethernet28J60::buffer[ETHER_BUFFER_SIZE];
#else
    #error Please define a network card in OpenSprinkler_Arduino.h
#endif  // OPENSPRINKLER_ARDUINO

void do_setup();
void do_loop();

void setup()
{
    DEBUG_BEGIN(115200);
    DEBUG_PRINTLN(F("--------------------"));
    DEBUG_FLUSH();

    do_setup();
    do_setup_spi();
    do_setup_heartbeat();
    do_setup_autoreboot();
}

void loop()
{
    do_loop();
    do_heartbeat();
}

// --------------------------------------------------
// This code is needed to handle multiple SPI devices - all the CS pins for each SPI device
// need to be pulled high to avoid interefering with each other (ethernet, SD, RF24 etc)
void do_setup_spi()
{
    for (int i = 0; i < PIN_SPI_DEVICES; i++)
    {
        pinMode(PIN_SPI_CS_LIST[i], OUTPUT);
        digitalWrite(PIN_SPI_CS_LIST[i], HIGH);
    }
}

// --------------------------------------------------
#ifdef OPENSPRINKLER_ARDUINO_HEARTBEAT
unsigned long nextHeartbeatMillis = 0;
unsigned long heartbeatCount = 0;

void do_setup_heartbeat()
{
    pinMode(PIN_HEARTBEAT, OUTPUT);
    digitalWrite(PIN_HEARTBEAT, LED_STATE_OFF);
    nextHeartbeatMillis = millis() + 1000;
}

void do_heartbeat()
{
    if (millis() > nextHeartbeatMillis)
    {
        DEBUG_PRINT(F("."));
        if (heartbeatCount != 0 && heartbeatCount % 40 == 0)
            DEBUG_PRINTLN();
        heartbeatCount++;
        nextHeartbeatMillis += 1000;
        digitalWrite(PIN_HEARTBEAT, (digitalRead(PIN_HEARTBEAT) == LED_STATE_OFF ? LED_STATE_ON : LED_STATE_OFF));
    }
}
#else
void setupHeartbeat() {}
void do_heartbeat() {}
#endif // OPENSPRINKLER_ARDUINO_HEARTBEAT

// --------------------------------------------------
#ifdef OPENSPRINKLER_ARDUINO_AUTOREBOOT 
void do_setup_autoreboot()
{
    Alarm.alarmRepeat(AUTO_REBOOT_HR, AUTO_REBOOT_MIN, AUTO_REBOOT_SEC, do_reboot);
}

void(*resetPointer) (void) = 0; // AVR software reset function
void do_reboot()
{
    resetPointer();
}
#else
void do_setup_autoreboot() {}
#endif // OPENSPRINKLER_ARDUINO_AUTOREBOOT

// --------------------------------------------------

