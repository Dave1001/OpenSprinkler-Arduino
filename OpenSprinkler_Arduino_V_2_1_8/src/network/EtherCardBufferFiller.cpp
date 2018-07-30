/* ==========================================================================================================
This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware:

EtherCardW5100.h and EtherCardW5100.cpp implements a minimal set of functions
as a wrapper to replace the ENC28J60 EtherCard class libraries with the standard
Arduino Wiznet5100 Ethernet library.

Version:     Opensprinkler 2.1.8

Date:        May 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Refer to the README file for more information

========================================================================================================== */

#include <stdarg.h>
#include "EtherCardBufferFiller.h"

#ifndef ESP8266

   /// <summary>
   /// ethercard.cpp - convert a two byte word to ascii
   /// </summary>
   /// <param name="value"></param>
   /// <param name="ptr"></param>
   /// <returns></returns>
char* BufferFiller::wtoa(uint16_t value, char* ptr)
{
    if (value > 9)
        ptr = wtoa(value / 10, ptr);
    *ptr = '0' + value % 10;
    *++ptr = 0;
    return ptr;
}

void BufferFiller::emit_p(PGM_P fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    for (;;) {
        char c = pgm_read_byte(fmt++);
        if (c == 0)
            break;
        if (c != '$') {
            *ptr++ = c;
            continue;
        }
        c = pgm_read_byte(fmt++);
        switch (c) {
        case 'D':
            //wtoa(va_arg(ap, uint16_t), (char*) ptr);
            itoa(va_arg(ap, uint16_t), (char*)ptr, 10);  // ray
            break;
#ifdef FLOATEMIT
        case 'T':
            dtostrf(va_arg(ap, double), 10, 3, (char*)ptr);
            break;
#endif
        case 'H': {
            char p1 = va_arg(ap, uint16_t);
            char p2;
            p2 = (p1 >> 4) & 0x0F;
            p1 = p1 & 0x0F;
            if (p1 > 9) p1 += 0x07; // adjust 0x0a-0x0f to come out 'a'-'f'
            p1 += 0x30;             // and complete
            if (p2 > 9) p2 += 0x07; // adjust 0x0a-0x0f to come out 'a'-'f'
            p2 += 0x30;             // and complete
            *ptr++ = p2;
            *ptr++ = p1;
            continue;
        }
        case 'L':
            //ltoa(va_arg(ap, long), (char*) ptr, 10);
            ultoa(va_arg(ap, long), (char*)ptr, 10); // ray
            break;
        case 'S':
            strcpy((char*)ptr, va_arg(ap, const char*));
            break;
        case 'F': {
            PGM_P s = va_arg(ap, PGM_P);
            char d;
            while ((d = pgm_read_byte(s++)) != 0)
                *ptr++ = d;
            continue;
        }
        case 'E': {
            byte* s = va_arg(ap, byte*);
            char d;
            while ((d = eeprom_read_byte(s++)) != 0)
                *ptr++ = d;
            continue;
        }
        default:
            *ptr++ = c;
            continue;
        }
        ptr += strlen((char*)ptr);
    }
    va_end(ap);
}

#endif
