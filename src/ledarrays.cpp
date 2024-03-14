#include "ledarrays.h"

// -2: LED_LINE_RAW
// -1: LED_LINE_BYTEVALUES
//  0: LED_HORZ
//  1: LED_VERT
//  2: LED_MIRROR
//  3: LED_RADIAL
//  4: LED_DIAGONAL
//  5: LED_DIAGONAL_ALT
//  6: LED_WAVE
//  7: LED_WAVE_ALT

byte getLEDValue(int arrayIndex, int valueIndex)
{
    switch (arrayIndex)
    {
    case -2:
        return pgm_read_byte_near(LED_LINE_RAW + valueIndex);
    case -1:
        return pgm_read_byte_near(LED_LINE_BYTEVALUES + valueIndex);
    default:
    case 0:
        return pgm_read_byte_near(LED_HORZ + valueIndex);
    case 1:
        return pgm_read_byte_near(LED_VERT + valueIndex);
    case 2:
        return pgm_read_byte_near(LED_MIRROR + valueIndex);
    case 3:
        return pgm_read_byte_near(LED_RADIAL + valueIndex);
    case 4:
        return pgm_read_byte_near(LED_DIAGONAL + valueIndex);
    case 5:
        return pgm_read_byte_near(LED_DIAGONAL_ALT + valueIndex);
    case 6:
        return pgm_read_byte_near(LED_WAVE + valueIndex);
    case 7:
        return pgm_read_byte_near(LED_WAVE_ALT + valueIndex);
    }
}

// read via progmem
// byte b = pgm_read_byte_near(array + index);
// return b;
// return array[index]; // read stored as sram (default)