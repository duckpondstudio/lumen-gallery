#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#ifndef BUTTON_DEFAULT_PULLUP
#define BUTTON_DEFAULT_PULLUP false // default value for whether buttons should be INPUT_PULLUP (t) or INPUT (f)
#endif

#ifndef BUTTON_BUFFER_LIMIT
#define BUTTON_BUFFER_LIMIT 25 // value above full buffer size to limit the buffer to
#endif

#ifndef BUTTON_DEFAULT_BUFFER_SIZE
#define BUTTON_DEFAULT_BUFFER_SIZE 35 // default size used for a "full" buffer (eg, button is "on")
#endif

#ifndef BUTTON_BUFFER_LATCH
#define BUTTON_BUFFER_LATCH 5 // extra value added to buffer upon reaching full buffer size, to avoid noise at the boundary between on/off
#endif

#ifndef BUTTON_BUFFER_RISE
#define BUTTON_BUFFER_RISE 2 // increment for buffer rising
#endif

#ifndef BUTTON_BUFFER_FALL
#define BUTTON_BUFFER_FALL 3 // decrement for buffer falling 
#endif

class Button
{
    private:
        const int m_pin;
        const int m_bufferSize;
        const int m_bufferLimit;

        int m_buffer;

    public:
        Button(int pin);
        Button(int pin, bool pullup, int bufferSize);
        void loop();
        bool pressed();
};

#endif