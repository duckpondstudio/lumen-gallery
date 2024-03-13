#include "input.h"

// EasyButton properties 
EasyButton btnSat(PIN_BTN_SAT, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);
EasyButton btnVal(PIN_BTN_VAL, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);
EasyButton btnEnc(PIN_BTN_ENC, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);

void setupInput() {
    btnSat.begin();
    btnVal.begin();
    btnEnc.begin();
}
void loopInput() {
    btnSat.read();
    btnVal.read();
    btnEnc.read();
}

bool isPressedSat() { return btnSat.isPressed(); }
bool isPressedVal() { return btnVal.isPressed(); }
bool isPressedEnc() { return btnEnc.isPressed(); }