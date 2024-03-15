#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#ifndef BUTTON_DEFAULT_PULLUP
#define BUTTON_DEFAULT_PULLUP true // default value for whether buttons should be INPUT_PULLUP (t) or INPUT (f)
#endif

#ifndef BUTTON_DEFAULT_INVERT
#define BUTTON_DEFAULT_INVERT false // default value for if a button's output is inverted
#endif

#ifndef BUTTON_DEFAULT_BUFFER_SIZE
#define BUTTON_DEFAULT_BUFFER_SIZE 35 // default size used for a "full" buffer (eg, button is "on")
#endif

#ifndef BUTTON_BUFFER_LIMIT
#define BUTTON_BUFFER_LIMIT 25 // value above full buffer size to limit the buffer to
#endif

#ifndef BUTTON_BUFFER_LATCH
#define BUTTON_BUFFER_LATCH 5 // extra value added to buffer upon reaching full buffer size, to avoid noise at the boundary between on/off
#endif

#ifndef BUTTON_BUFFER_RISE
#define BUTTON_BUFFER_RISE 3 // increment for buffer rising
#endif

#ifndef BUTTON_BUFFER_FALL
#define BUTTON_BUFFER_FALL 2 // decrement for buffer falling
#endif

class Button
{
private:
    byte m_pin;
    bool m_invert;
    int m_bufferSize;
    int m_bufferLimit;

    int m_buffer;

public:
    Button(byte pin);
    Button(byte pin, int bufferSize);
    Button(byte pin, bool pullup, int bufferSize);
    Button(byte pin, bool pullup, bool invert);
    Button(byte pin, bool pullup, bool invert, int bufferSize);
    void loop();
    bool pressed();
};

#endif