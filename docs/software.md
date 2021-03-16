# Software

## Arduino IDE installeren

## WEMOS D1 Mini instellingen toevoegen

## Adafruit Neopixel library toevoegen

## Code compileren en uploaden

### Test code
Gebruik de volgende code om te testen of je hardware goed werkt. Als alles correct aangesloten is zal er een regenboog over de ledring cirkelen. Door aan de draaiknop te draaien moet deze sneller of langzamer gaan draaien. Als je het knopje indrukt moet deze stoppen met draaien.

> **Help! Er is wat mis!**  
> Blijf kalm en kijk in de [probleemoplosser](./probleemoplosser.md).

```c++
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
```