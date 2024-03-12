#include "leds.h"

void setupLEDs() {
  FastLED.addLeds<WS2812B, 5, GRB>(leds, 40);
}

void loopLEDs() {
    
  for (int i = 0; i < 40; i++) {
      leds[i] = CRGB::Red;
  }
  FastLED.show();
}