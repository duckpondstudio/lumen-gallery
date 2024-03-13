#include "input.h"

// EasyButton properties
// EasyButton btnSat(PIN_BTN_SAT, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);
// EasyButton btnVal(PIN_BTN_VAL, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);
// EasyButton btnEnc(PIN_BTN_ENC, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);

// EncoderButton encoder = EncoderButton(PIN_ENC_A, PIN_ENC_B, PIN_BTN_ENC);
// EncoderButton btnSat = EncoderButton(PIN_BTN_SAT);
// EncoderButton btnVal = EncoderButton(PIN_BTN_VAL);

// Encoder encoder(PIN_ENC_A, PIN_ENC_B);
// long encoderPosition = -999;

long encoderPosition = 0;
SimpleEncoder encoder(PIN_BTN_ENC, PIN_ENC_A, PIN_ENC_B, encoderPosition, -512, 512);


void setupInput()
{
    // btnSat.begin();
    // btnVal.begin();
    // btnEnc.begin();
}
void loopInput()
{
    // encoder.update();
    // btnSat.update();
    // btnVal.update();

    // if (encoder.CLOCKWISE) {
    //     encoderPosition++;
    // }
    // if (encoder.COUNTERCLOCKWISE) {
    //     encoderPosition--;
    // }
}

// bool isPressedSat() { return btnSat.buttonState(); }
// bool isPressedVal() { return btnVal.buttonState(); }
// bool isPressedEnc() { return encoder.buttonState(); }
bool isPressedSat() { return false; }
bool isPressedVal() { return false; }
bool isPressedEnc() { return false; }

byte encoderValueAsByte() { return encoderValue() % 256; }
// long encoderValue() { return encoder.getValue(); }
long encoderValue() { return encoderPosition; }