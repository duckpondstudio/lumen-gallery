#include <Arduino.h>
#include <FastLED.h>

// put function declarations here:

CRGB leds[40];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, 5>(leds, 40);
  for (int i = 0; i < 40; i++) {
      leds[i] = CRGB::Aquamarine;
  }
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
}
