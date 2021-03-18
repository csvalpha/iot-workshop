#include <Arduino.h>
// We voegen de Neopixel library toe waarmee we de ledring kunnen aansturen
#include <Adafruit_NeoPixel.h>

// We definiëren aan welke pinnen we het knopje, de potentiometer en ledring aangesloten hebben
#define POT_PIN A0
#define BTN_PIN D8
#define LED_PIN D4

// Onze ledring heeft 60 ledjes, dit slaan we op en we maken een ledstrip object aan
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// We maken een globale variabele aan waarin we onthouden of het nachlampje aan of uit staat
boolean lightOn = true;

void setup() {
  // We starten de ledstrip op en zetten hem aan
  strip.begin();
  strip.show();

  // We definiëren dat het knopje als input gebruik moet worden
  pinMode(BTN_PIN, INPUT);
}

void loop() {
  // Als het knopje ingedrukt wordt moet het lampje aan of uit gaan
  if (digitalRead(BTN_PIN)) {
    // We veranderen de waarde naar het tegenovergestelde van zijn vorige waarde, aan wordt dus uit en uit wordt aan
    lightOn = !lightOn;

    // We wachten heel even om rekening te houden met bouncen
    delay(300);

    // Om te voorkomen dat de ledring gaat knipperen wachten we tot het knopje losgelaten is
    while(digitalRead(BTN_PIN)) {
      delay(100);
    }
  }

  // We bepalen of het nachtlampje aan moet staan
  if (lightOn) {  
    // Zo ja dan stellen we eerst de kleur in van elke pixel
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 255, 255, 75);
    }

    // Vervolgens bepalen we hoe fel hij moet zijn door de waarde van de potmeter uit te lezen
    // Dit is een waarde tussen de 0 en 1024, de brightness moet ingesteld worden tussen 0 en 255, dus delen he het door 4
    int brightness = analogRead(POT_PIN) / 4;

    // We stellen de felheid van de ledring in
    strip.setBrightness(brightness);
  } else {
    // Als hij uit moet staan zetten we de felheid op 0
    strip.setBrightness(0);
  }

  // We sturen alle instellingen die we gedaan hebben naar de ledring om weergeven te worden
  strip.show();
}