# Klok

## Volledig script
```arduino
#include <Arduino.h>
// We voegen de Neopixel library toe waarmee we de ledring kunnen aansturen
#include <Adafruit_NeoPixel.h>

// We voegen de Wifi en de NTPclient libraries toe waarmee we met wifi kunnen verbinden en de tijd kunnen ophalen
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// We stellen het wifi netwerk en wachtwoord in
const char *ssid     = "netwerknaam";
const char *password = "wachtwoord";

// We maken een Wifi en NTPclient object aan
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// We definiëren aan welke pinnen we het knopje, de potentiometer en ledring aangesloten hebben
#define POT_PIN A0
#define BTN_PIN D8
#define LED_PIN D4

// Onze ledring heeft 60 ledjes, dit slaan we op en we maken een ledstrip object aan
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // We starten de ledstrip op en zetten hem aan
  strip.begin();

  // We maken de ledstrip rood om aan te geven dat we nog niet met wifi verbonden zijn
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.setBrightness(25);
  strip.show();

  // We maken verbinding met het wifi netwerk
  WiFi.begin(ssid, password);

  // Zolang we nog niet met het wifi verbonden zijn updaten we een pixel van de ring naar oranje
  int status = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    if (status < LED_COUNT) {
      strip.setPixelColor(status++, 255, 255, 0);
      strip.show();
    }
  }

  // We starten de NTPclient op en stellen de tijdszone in op GMT+2 (europese zomertijd)
  timeClient.begin();
  timeClient.setTimeOffset(7200);

  // We maken de ledstrip blauw om aan te geven dat we succesvol opgestart zijn
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 255);
  }
  strip.show();
  delay(500);
}

void loop() {
  // We updaten de NTPclient met de huidige tijd
  timeClient.update();
  int minuutPixel = timeClient.getMinutes();
  int uurPixel = (timeClient.getHours() % 12) * 5;
  int secondePixel = timeClient.getSeconds();

  for (int i = 0; i < strip.numPixels(); i++) {
    int red = (i == minuutPixel) ? 255 : 0;
    int green = (i == uurPixel) ? 255 : 0;
    int blue = (i == secondePixel) ? 255 : 0;

    if (i % 15 == 0 && !red && !green && !blue) {
      red = 255;
      green = 255;
      blue = 255;
    }

    strip.setPixelColor(LED_COUNT - 1 - i, red, green, blue);
  }

  // Vervolgens bepalen we hoe fel hij moet zijn door de waarde van de potmeter uit te lezen
  // Dit is een waarde tussen de 0 en 1024, de brightness moet ingesteld worden tussen 0 en 255, dus delen he het door 4
  int brightness = analogRead(POT_PIN) / 4;

  // We stellen de felheid van de ledring in
  strip.setBrightness(brightness);

  // We sturen alle instellingen die we gedaan hebben naar de ledring om weergeven te worden
  strip.show();

  delay(500);
}
```