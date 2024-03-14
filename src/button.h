#ifndef BUTTON_H
#define BUTTON_H

#ifndef BUTTON_BUFFER_LIMIT
#define BUTTON_BUFFER_LIMIT 30
#endif

#ifndef BUTTON_BUFFER_RISE
#define BUTTON_BUFFER_RISE 2
#endif

#ifndef BUTTON_BUFFER_FALL
#define BUTTON_BUFFER_FALL 3
#endif

class Button
{
    private:
        int m_pin;
        int m_bufferLimit;
        int m_buffer;

    public:
        Button(int pin);
        void loop() const;
};

#endif