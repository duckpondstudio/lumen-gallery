#include "input.h"


EasyButton btnSat(BTN_PIN_SAT);
EasyButton btnVal(BTN_PIN_VAL);

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