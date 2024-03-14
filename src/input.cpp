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

// SimpleEncoder encoder(PIN_BTN_ENC, PIN_ENC_A, PIN_ENC_B, encoderPositionOutput, -512, 512);

// long encoderPositionOutput = 0;
// long encoderPosition = 0;

// long encoderPositionOutput = 0;
static int encoderPosition = 0;

// RotaryEncoder encoder(PIN_ENC_A, PIN_ENC_B, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder *encoder = nullptr;

static bool interrupted;

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

     

    // int dptiA = digitalPinToInterrupt(PIN_ENC_A);
    // if (dptiA > -1)
    // {
    //     attachInterrupt(dptiA, updateEncoder, CHANGE);
    // }
    // int dptiB = digitalPinToInterrupt(PIN_ENC_B);
    // if (dptiB > -1)
    // {
    //     attachInterrupt(dptiB, updateEncoder, CHANGE);
    // }

    encoder = new RotaryEncoder(PIN_ENC_A, PIN_ENC_B, RotaryEncoder::LatchMode::TWO03);
}



ISR(INT0_vect) { updateEncoder(); }
ISR(PCINT0_vect) { updateEncoder(); }
// ISR(PCINT1_vect) { updateEncoder(); }

void loopInput()
{

    updateEncoder();

    int newPos = encoder->getPosition();
    if (newPos != encoderPosition)
    {
        encoderPosition = newPos;
    }

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

void updateEncoder()
{
    encoder->tick();
    
    // int newPos = encoder->getPosition();
    // if (newPos != encoderPosition)
    // {
    //     encoderPosition = newPos;
    // } else {

    //     if ((int)encoder->getDirection() == 1) {
    //         encoderPosition += 5;

    //     } else if ((int)encoder->getDirection() == -1) {
    //         encoderPosition -= 5;

    //     } else {
    //         // encoderPosition += 100;
    //     }

    //     encoder->setPosition(encoderPosition);
        
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
// long encoderValue() { return encoderPositionOutput; }
int encoderValue() { return encoderPosition; }