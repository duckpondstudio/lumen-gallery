#include "input.h"

// EasyButton properties 
// EasyButton btnSat(PIN_BTN_SAT, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);
// EasyButton btnVal(PIN_BTN_VAL, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);
// EasyButton btnEnc(PIN_BTN_ENC, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);

EncoderButton encoder = EncoderButton(PIN_ENC_A, PIN_ENC_B, PIN_BTN_ENC);
EncoderButton btnSat = EncoderButton(PIN_BTN_SAT);
EncoderButton btnVal = EncoderButton(PIN_BTN_VAL);

void setupInput() {
    // btnSat.begin();
    // btnVal.begin();
    // btnEnc.begin();
}
void loopInput() {
    encoder.update();
    btnSat.update();
    btnVal.update();
}

bool isPressedSat() { return btnSat.buttonState(); }
bool isPressedVal() { return btnVal.buttonState(); }
bool isPressedEnc() { return encoder.buttonState(); }