#include "input.h"

static int encoderPosition = 0;

RotaryEncoder *encoder = nullptr;

// OneButtonTiny btnSat = OneButtonTiny(PIN_BTN_SAT, BTNS_ACTIVE_LOW, BTNS_PULLUP);
// OneButtonTiny btnVal = OneButtonTiny(PIN_BTN_SAT, BTNS_ACTIVE_LOW, BTNS_PULLUP);
// OneButtonTiny btnEnc = OneButtonTiny(PIN_BTN_SAT, BTNS_ACTIVE_LOW, BTNS_PULLUP);

// Button btnSat(PIN_BTN_SAT, BTNS_DEBOUNCE);
// Button btnVal(PIN_BTN_VAL, BTNS_DEBOUNCE);
// Button btnEnc(PIN_BTN_ENC, BTNS_DEBOUNCE);

void setupInput()
{
    // btnSat.begin();
    // btnVal.begin();
    // btnEnc.begin();

    // 11.2.2 on ATtinyX4 datasheet
    // GIMSK General Interrupt Mask Register
    // (1 << INT0) bit 6 (INT0) enables interrupt INT0,
    //    external interrupt (arduino pin 2, chip pin 5)
    //    This tells the GIMSK that we're gonna be using INT0
    // (1 << PCIE0) enables Pin Change Interrupt Enable 0,
    //    which is connected to PCMSK0, prepping the GIMSK to use
    //    PCINT0 thru PCINT7, whichever ones we enable (7)
    // PCMSK0 |= (1 << PCINT7) enables PCINT7 for interrupts
    //    (arduino pin 3/A7, chip pin 6)
    // sei(); enables global interrupts

    GIMSK |= (1 << INT0) | (1 << PCIE0);
    PCMSK0 |= (1 << PCINT7);
    sei(); // enable global interrupt
    // create new encoder
    encoder = new RotaryEncoder(PIN_ENC_A, PIN_ENC_B, RotaryEncoder::LatchMode::TWO03);
}

ISR(INT0_vect) { updateEncoder(); }
ISR(PCINT0_vect) { updateEncoder(); }

void loopInput()
{
    updateEncoder();
    updateButtons();

    int newPos = encoder->getPosition();
    if (newPos != encoderPosition)
    {
        encoderPosition = newPos;
    }
}

void updateEncoder()
{
    encoder->tick();
}
void updateButtons()
{
    // btnSat.tick();
    // btnVal.tick();
    // btnEnc.tick();
}

// bool isPressedSat() { return isButtonPressed(btnSat); }
// bool isPressedVal() { return isButtonPressed(btnVal); }
// bool isPressedEnc() { return isButtonPressed(btnEnc); }
// bool isPressedSat() { return btnSat.pressed(); }
// bool isPressedVal() { return btnVal.pressed(); }
// bool isPressedEnc() { return btnEnc.pressed(); }
bool isPressedSat() { return false; }
bool isPressedVal() { return false; }
bool isPressedEnc() { return false; }

// bool isButtonPressed(OneButtonTiny btn)
// {
//     switch ((int)btn.state())
//     {
//     case 2:
//     case 6:
//         return true;
//     }
//     return false;

//     // case OneButtonTiny::stateMachine_t::OCS_DOWN:
//     // case OneButtonTiny::stateMachine_t::OCS_PRESS:
//     // define FiniteStateMachine
//     // OCS_INIT = 0,
//     // OCS_DOWN = 1,  // button is down
//     // OCS_UP = 2,    // button is up
//     // OCS_COUNT = 3,
//     // OCS_PRESS = 6,  // button is hold down
//     // OCS_PRESSEND = 7,
// }

byte encoderValueAsByte() { return encoderValue() % 256; }
int encoderValue() { return encoderPosition; }