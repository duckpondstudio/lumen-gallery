#ifndef PINDEF_H
#define PINDEF_H

/* NOTE: when changing pins, especially LEDS / ENC_A / ENC_B,
         remember to update interrupts in input.cpp as needed!
*/

#define PIN_LEDS 7 // FastLED data pin

#define PIN_ENC_A 8 // Rotary Encoder read pin A, INT0 / PCINT10
#define PIN_ENC_B 4 // Rotary Encoder read pin B, Non-int / PCINT4 / A4 / ADC4

#define PIN_BTN_SAT 3 // Button (LED colour, Saturation control)
#define PIN_BTN_VAL 6 // Button (LED colour, Value control)
#define PIN_BTN_ENC 5 // Button (Rotary Encoder)

#endif