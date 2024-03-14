#include "button.h"

Button::Button(int pin, bool pullup, int bufferSize = BUTTON_BUFFER_DEFAULT_SIZE)
    : m_pin{pin},
      m_bufferSize{bufferSize},
      m_bufferLimit{bufferSize + BUTTON_BUFFER_LIMIT}
{
    pinMode(pin, pullup ? INPUT_PULLUP : INPUT);
}

void Button::loop()
{
    bool state = digitalRead(m_pin);

    if (state)
    {
        if (m_buffer < m_bufferLimit)
        {
            bool latched = !pressed();
            m_buffer += BUTTON_BUFFER_RISE;
            if (!latched && pressed()) {
                m_buffer += BUTTON_BUFFER_LATCH;
            }
            if (m_buffer > m_bufferLimit)
            {
                m_buffer = m_bufferLimit;
            }
        }
    }
    else
    {
        if (m_buffer > 0)
        {
            m_buffer -= BUTTON_BUFFER_FALL;
            if (m_buffer < 0)
            {
                m_buffer = 0;
            }
        }
    }
}

bool Button::pressed() {
    return m_buffer >= m_bufferSize;
}