#include "input.h"

static int encoderPosition = 0;

RotaryEncoder *encoder = nullptr;

Button btnSat(PIN_BTN_SAT);
Button btnVal(PIN_BTN_VAL);
Button btnEnc(PIN_BTN_ENC);

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
    btnSat.loop();
    btnVal.loop();
    btnEnc.loop();
}

bool isPressedSat() { return btnSat.pressed(); }
bool isPressedVal() { return btnVal.pressed(); }
bool isPressedEnc() { return btnEnc.pressed(); }

byte encoderValueAsByte() { return encoderValue() % 256; }
int encoderValue() { return encoderPosition; }