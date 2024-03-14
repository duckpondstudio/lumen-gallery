#ifndef LEDARRAYS_H
#define LEDARRAYS_H

#include <Arduino.h>

const PROGMEM byte LED_LINE_RAW[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
const PROGMEM byte LED_LINE_BYTEVALUES[] = {0, 7, 13, 20, 26, 33, 39, 46, 52, 59, 65, 72, 78, 85, 92, 98, 105, 111, 118, 124, 131, 137, 144, 150, 157, 163, 170, 177, 183, 190, 196, 203, 209, 216, 222, 229, 235, 242, 248, 255};
const PROGMEM byte LED_HORZ[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
const PROGMEM byte LED_VERT[] = {0, 28, 57, 85, 113, 142, 169, 198, 227, 255, 0, 28, 57, 85, 113, 142, 169, 198, 227, 255, 0, 28, 57, 85, 113, 142, 169, 198, 227, 255, 0, 28, 57, 85, 113, 142, 169, 198, 227, 255};
const PROGMEM byte LED_MIRROR[] = {0, 64, 128, 191, 255, 255, 191, 128, 64, 0, 0, 64, 128, 191, 255, 255, 191, 128, 64, 0, 0, 64, 128, 191, 255, 255, 191, 128, 64, 0, 0, 64, 128, 191, 255, 255, 191, 128, 64, 0};
const PROGMEM byte LED_RADIAL[] = {0, 39, 88, 152, 213, 213, 152, 88, 39, 0, 53, 103, 169, 224, 255, 255, 224, 170, 103, 53, 53, 103, 170, 224, 255, 255, 224, 170, 103, 53, 0, 39, 88, 152, 213, 213, 152, 88, 39, 0};
const PROGMEM byte LED_DIAGONAL[] = {0, 27, 50, 73, 99, 124, 150, 172, 193, 228, 238, 232, 205, 180, 152, 123, 94, 66, 36, 11, 27, 53, 80, 108, 137, 166, 194, 218, 238, 243, 255, 247, 224, 200, 172, 145, 116, 88, 59, 35};
const PROGMEM byte LED_DIAGONAL_ALT[] = {35, 59, 88, 116, 145, 172, 200, 224, 247, 255, 243, 238, 218, 194, 166, 137, 108, 80, 53, 27, 11, 36, 66, 94, 123, 152, 180, 205, 232, 238, 228, 193, 172, 150, 124, 99, 73, 50, 27, 0};
const PROGMEM byte LED_WAVE[] = {232, 213, 189, 165, 139, 113, 84, 69, 40, 0, 25, 48, 75, 10, 129, 155, 181, 207, 235, 255, 255, 235, 207, 181, 155, 129, 103, 75, 48, 25, 0, 40, 69, 84, 113, 139, 165, 189, 213, 232};
const PROGMEM byte LED_WAVE_ALT[] = {0, 40, 69, 84, 113, 139, 165, 189, 213, 232, 255, 235, 207, 181, 155, 129, 103, 75, 48, 25, 25, 48, 75, 103, 129, 155, 181, 207, 235, 255, 232, 213, 189, 165, 139, 113, 84, 69, 40, 0};

byte getLEDArray(int arrayIndex);
byte getLEDValue(int arrayIndex, int valueIndex);

#endif