# Wakeuplight

## Volledig script
```arduino
#include <Arduino.h>
// We voegen de Neopixel library toe waarmee we de ledring kunnen aansturen
#include <Adafruit_NeoPixel.h>

// We voegen de Wifi en de NTPclient libraries toe waarmee we met wifi kunnen verbinden en de tijd kunnen ophalen
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// We stellen in hoe laat de lamp aan moet gaan
const int wakeupHour = 8;
const int wakeupMinute = 30;

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

// We maken een globale variabele aan waarin we onthouden of het nachlampje aan of uit staat
boolean lightOn = false;

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

  // We definiëren dat het knopje als input gebruik moet worden
  pinMode(BTN_PIN, INPUT);

  // We maken de ledstrip groen om aan te geven dat we succesvol opgestart zijn
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 255, 0);
  }
  strip.show();
  delay(500);
}

void loop() {
  // We updaten de NTPclient met de huidige tijd
  timeClient.update();

  // Als de huidige tijd overeen komt met de wekker tijd moet de lamp aan
  if (timeClient.getHours() == wakeupHour && timeClient.getMinutes() == wakeupMinute) {
    lightOn = true;
  }

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
```