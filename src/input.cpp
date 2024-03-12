#include "input.h"


EasyButton btnSat(BTN_PIN_SAT, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);
EasyButton btnVal(BTN_PIN_VAL, BTNS_DEBOUNCE, BTNS_PULLUP, BTNS_INVERT);

void setupInput() {
    btnSat.begin();
    btnVal.begin();
}
void loopInput() {

    btnSat.read();
    btnVal.read();

}

bool isPressedSat() { return btnSat.isPressed(); }
bool isPressedVal() { return btnVal.isPressed(); }