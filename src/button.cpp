#include "button.h"

Button::Button(int pin)
    : m_pin{pin},
      m_invert{BUTTON_DEFAULT_INVERT},
      m_bufferSize{BUTTON_DEFAULT_BUFFER_SIZE},
      m_bufferLimit{BUTTON_DEFAULT_BUFFER_SIZE + BUTTON_BUFFER_LIMIT},
      m_buffer{0}
{
    pinMode(pin, BUTTON_DEFAULT_PULLUP ? INPUT_PULLUP : INPUT);
}
Button::Button(int pin,
               int bufferSize = BUTTON_DEFAULT_BUFFER_SIZE)
    : m_pin{pin},
      m_invert{BUTTON_DEFAULT_INVERT},
      m_bufferSize{bufferSize},
      m_bufferLimit{bufferSize + BUTTON_BUFFER_LIMIT},
      m_buffer{0}
{
    pinMode(pin, BUTTON_DEFAULT_PULLUP ? INPUT_PULLUP : INPUT);
}
Button::Button(int pin,
               bool pullup = BUTTON_DEFAULT_PULLUP,
               int bufferSize = BUTTON_DEFAULT_BUFFER_SIZE)
    : m_pin{pin},
      m_invert{BUTTON_DEFAULT_INVERT},
      m_bufferSize{bufferSize},
      m_bufferLimit{bufferSize + BUTTON_BUFFER_LIMIT},
      m_buffer{0}
{
    pinMode(pin, pullup ? INPUT_PULLUP : INPUT);
}
Button::Button(int pin,
               bool pullup = BUTTON_DEFAULT_PULLUP,
               bool invert = BUTTON_DEFAULT_INVERT)
    : m_pin{pin},
      m_invert{invert},
      m_bufferSize{BUTTON_DEFAULT_BUFFER_SIZE},
      m_bufferLimit{BUTTON_DEFAULT_BUFFER_SIZE + BUTTON_BUFFER_LIMIT},
      m_buffer{0}
{
    pinMode(pin, pullup ? INPUT_PULLUP : INPUT);
}
Button::Button(int pin,
               bool pullup = BUTTON_DEFAULT_PULLUP,
               bool invert = BUTTON_DEFAULT_INVERT,
               int bufferSize = BUTTON_DEFAULT_BUFFER_SIZE)
    : m_pin{pin},
      m_invert{invert},
      m_bufferSize{bufferSize},
      m_bufferLimit{bufferSize + BUTTON_BUFFER_LIMIT},
      m_buffer{0}
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
            bool latched = pressed();
            m_buffer += BUTTON_BUFFER_RISE;
            if (!latched && pressed())
            {
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
            bool latched = !pressed();
            m_buffer -= BUTTON_BUFFER_FALL;
            if (!latched && !pressed())
            {
                m_buffer -= BUTTON_BUFFER_LATCH;
            }
            if (m_buffer < 0)
            {
                m_buffer = 0;
            }
        }
    }
}

// returns true if the button is pressed (or false, if invert is set true)
bool Button::pressed()
{
    return m_invert ? m_buffer < m_bufferSize : m_buffer >= m_bufferSize;
}