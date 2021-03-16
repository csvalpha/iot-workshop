#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define POT_PIN A0
#define BTN_PIN D8
#define LED_PIN D4
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
long firstPixelHue = 0;

void rainbow(int wait) {
  if (firstPixelHue < 5 * 65536) {
    firstPixelHue += 256;
    for (int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
  else {
    firstPixelHue = 0;
  }
}

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(100);

  pinMode(BTN_PIN, INPUT);
}

void loop() {
  if (!digitalRead(BTN_PIN)) {
    rainbow(analogRead(POT_PIN)/100);
  }
}