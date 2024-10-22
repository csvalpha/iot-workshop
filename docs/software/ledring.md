# Ledring

Om de kleuren en helderheid van de leds op de ledring aan te passen kun je gebruik maken van de Adafruit Neopixel library. Om deze te installeren ga je naar **Sketch > Library > Manage Libraries** en zoek je naar Adafruit Neopixel. Deze library geeft handige functies waarmee de leds aangestuurd kunnen worden op led ringen maar ook ledstrips.

## Functies
De library heeft de volgende functies.

  - `begin()` initialiseert het ledring object waarna het gebruikt kan worden.
  - `show()` schrijft de wijzigingen aan de pixel kleuren naar de ledring voor weergave.
  - `setPixelColor(n, red, green, blue)` zet de kleur van de pixel.
  - `fill(color, first, count)` zet de kleur van meerdere achtereenvolgende pixels.
  - `Color(red, green, blue)` converteerd losse waarden voor rood, groen en blauw naar een enkele kleurwaarde.
  - `ColorHSV(hue, saturation, value)` converteerd losse waarden voor hue, saturation en value naar een enkele kleurwaarde.
  - `getPixelColor(n)` geeft de kleur van een pixel.
  - `setBrightness(brightness)` zet de helderheid van de ledring met een waarde tussen de 0 en de 255.
  - `getBrightness()` geeft de helderheid van de ledring.
  - `clear()` verwijdert alle ingestelde kleuren van elke pixel.
  - `numPixels()` geeft het aantal pixels in de ledring.
  - `gamma32(color)` geeft een gamma gecorigeerde kleurwaarde terug.

## Voorbeeld
```arduino
#include <Adafruit_NeoPixel.h>

// Which pin on the ESP is connected to the NeoPixels?
#define LED_PIN D4

// How many leds are there on the ring?
#define LED_COUNT 60

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(255,   0,   0), 50); // Red
  colorWipe(strip.Color(  0, 255,   0), 50); // Green
  colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(10);             // Flowing rainbow cycle along the whole strip
  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
```

## Werking
Allereerst moet de library toegevoegd worden aan de applicatie.
```arduino
#include <Adafruit_NeoPixel.h>
```

Vervolgens slaan we op aan welke pin de ledring verbonden is en hoeveel pixels er op de ring zitten, in ons geval pin `D4` en 60 pixels. Daarna maken we een Neopixel strip object aan.
```arduino
#define LED_PIN D4
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
```

### setup()
In de `setup()` initializeren we het strip object door de `begin()` functie aan te roepen en zetten we alle pixels uit door de `show()` functie aan te roepen.
```arduino
void setup() {
  strip.begin();
  strip.show();
}
```

### Pixels een kleur geven
De kleur van een pixel kan ingesteld worden door middel van de `setPixelColor(n, red, green, blue)`. Daar bij is n het nummer van de pixel in de ring en zijn de kleuren gegeven als een getal tussen de 0 en 255. Het volgende voorbeeld zet de kleur van de 12e pixel naar magenta.
```arduino
strip.setPixelColor(11, 255, 0, 255);
```

Een alternatief is om de kleur van de pixel in te stellen met een kleurwaarde met de `setPixelColor(n, color)` functie. Daarvoor kun je de waarde van een kleur in een 32 bit getal opslaan zodat je hem later kunt hergebruiken. Hiervoor kun je de `Color(red, green, blue)` functie gebruiken. Het volgende voorbeeld slaat de kleur magenta op in een variabele en zet vervolgens de kleur van de 12e pixel naar magenta.
```arduino
uint32_t magenta = strip.Color(255, 0, 255);
strip.setPixelColor(11, magenta);
```

!!! caution "Let op! `setPixelColor()` heeft niet meteen effect op de leds"
    De ingestelde kleuren moeten eerst naar de ledring verstuurd worden. Daarvoor kun je de `show()` functie gebruiken.

De `show()` functie zorgt ervoor dat de voor de pixels ingestelde kleuren weergeven op de ledring.
```arduino
strip.show();
```

### Meerdere pixels een kleur geven
Je kunt meerdere pixels dezelfde kleur geven met de `fill(color, first, count)` functie. Daarbij is `color` een 32-bit kleur waarde, is `first` de eerste pixel die de kleur moet krijgen en is `count` het aantal pixels dat de kleur moeten krijgen. In het volgende voorbeeld worden de pixels 4 tot en met 8 de kleur magenta gegeven.
```arduino
uint32_t magenta = strip.Color(255, 0, 255);
strip.fill(magenta, 3, 5);
```

De `clear()` functie kan gebruikt worden om alle pixels uit te zetten.
```arduino
strip.clear();
```

Met `numPixels()` kun je het aantal pixels in de ring opvragen. Dit kun je gebruiken in een for loop om alle pixels een kleur te geven. Het volgende voorbeeld maakt een kleurverloop van rood naar blauw over de hele ring.
```arduino
for (int i = 0; i < strip.numPixels(); i++) {
  int offset = (int) (255 / strip.numPixels()) * i;
  strip.setPixelColor(i, 255 - offset, 0, offset);
}
```

### Helderheid
De helderheid van de hele ledring kan met `setBrightness(value)` ingesteld worden. Daarbij is `value` een waarde tussen de 0 voor uit en 255 voor maximale helderheid. Om de ledring op een kwart helderheid te zetten kun je dus de volgende code gebruiken:
```arduino
strip.setBrightness(64);
```

!!! caution "Let op! `setBrightness()` heeft niet meteen effect op de leds"
    De ingestelde helderheid moeten eerst naar de ledring verstuurd worden. Daarvoor kun je de `show()` functie gebruiken.
    
!!! info "`setBrightness()` is eigenlijk bedoeld om maar één keer aangeroepen te worden in de `setup()`"
    Het is dus eigenlijk niet de bedoeling om hem voor animaties te gebruiken. Het is beter om met eigen logica de helderheid van je pixels aan te passen als je hier animaties mee wilt maken. Dit komt omdat de functie de waarden van je pixel data in het RAM aanpast en daarmee informatie verloren gaat, het is een "lossy" operatie.

### HSV kleuren
De Neopixel library ondersteunt ook het gebruik van kleuren in de "HSV" (hue-saturation-value) kleurruimte als alternatief voor de gebruikelijke RGB (red-green-blue). Voor sommige effecten is dit veel gebruiksvriendelijker, bijvoorbeeld voor het regenboog effect (zeer populair onder creaters). Een HSV kleur kan met de `ColorHSV()` opgeslagen worden als RGB waarde.
```arduino
uint32_t rgbcolor = strip.ColorHSV(hue, saturation, value);
```

![het HSV kleurenwiel](../assets/images/hue-saturation-value.png){ align=left }

Daarbij zijn de volgende parameters van belang:

  - `hue` is een 16-bit nummer dat start bij 0 voor rood en de kleurcirkel via geel (65536/6), groen (65536/3), cyaan (65536/2), blauw (65536*2/3) en magenta (65536*5/6) weer bij rood aan komt (65536).
  - `saturation` is een 8-bit nummer dat de verzadiging van de kleur aangeeft waarbij 0 onverzadigd is en 255 maximale verzadiging.
  - `value` is een 8-bit nummer dat de helderheid van de kleur aangeeft waarbij 0 zwart is en 255 maximale helderheid.

Als je alleen een pure kleur wilt met maximale verzadiging en helderheid dan kun je de functie ook aanroepen met alleen de hue:
```arduino
uint32_t rgbcolor = strip.ColorHSV(hue);
```

#### Gamma correctie
Als je veel met kleuren werkt zul je merken dat wanneer je faded tussen kleuren het soms lijkt alsof ze overmatig helder of flets er uit zien. Dit komt omdat nummeriek de kleurwaarden goed zijn maar de perceptie van onze ogen iets anders is. Daarvoor kun je zogenaamde gamma correctie gebruiken, hoe dat precies werkt wordt [hier uitgelegd](https://learn.adafruit.com/led-tricks-gamma-correction). De `gamma32(color)` functie neemt een RGB waarde en corrigeert deze zodat hij optisch correct is.
```arduino
uint32_t rgbcolor = strip.gamma32(strip.ColorHSV(hue, sat, val));
```

#### Een regenboog maken
Stel je wilt je ledstrip voorzien van een regenboogeffect (zeer belangrijk, dit wil je weten) dan doe je dat als volgt:
```arduino
for(int i = 0; i < strip.numPixels(); i++) {
  int hue = i * 65536L / strip.numPixels();
  uint32_t color = strip.gamma32(strip.ColorHSV(hue));
  strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
}
```

## Meer informatie
Voor meer informatie kun je naar de [github repo](https://github.com/adafruit/Adafruit_NeoPixel) van de library of vind je in de [Neopixel Uberguide](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use).
