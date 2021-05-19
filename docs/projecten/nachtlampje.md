# Nachtlampje
Welkom bij deze handleiding om een nachtlampje te maken. Alle achtergrondinformatie over de functies en methodes die we gaan gebruiken kun je in het software hoofdstuk vinden. We zullen stap voor stap door de code heen lopen en afsluiten met een voorbeeld van de volledige code. Maar nu eerst een overzicht van de werking.

We zullen in het programma beginnen met alle instellingen die nodig zijn om de ledstrip aan te sturen en het knopje en de potentiometer uit te lezen. Vervolgens zullen we in de `loop()` bepalen of het knopje ingedrukt wordt en het lampje aan of uit zetten. Als het lampje aan moet staan dan zullen we de potentiometer uitlezen hoe fel dat moet zijn en de ledring met die felheid aanzetten.

## Voorbereiding
We beginnen met het importeren van de Neopixel library die we nodig hebben om de ledring mee aan te sturen.
```arduino
#include <Adafruit_NeoPixel.h>
```

Daarna definiëren we variabelen waarin we opslaan aan welke pinnen we het knopje, de potentiometer en ledring aangesloten hebben.
```arduino
#define POT_PIN A0
#define BTN_PIN D8
#define LED_PIN D4
```

Vervolgens maken we een strip object aan dat de communicatie met de ledring zal verzorgen.
```arduino
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
```

Tot slot maken we een variabele aan waarin we opslaan of de ledring aan of uit moet staan.
```arduino
boolean lightOn = true;
```

## Setup
Vervolgens in de `setup()` starten we de ledstrip op met de `begin()` functie en zetten hem aan met de `show()` functie. Als je nu niet de `show()` functie zou aanroepen zul je zien dat een of meerdere leds op de ring willekeurig aan zullen staan. Aansluitend zorgen we er voor dat de pin waaraan het knopje is verbonden als input uitgelezen moet worden door middel van de `pinMode()` functie.

```arduino
void setup() {
  // We starten de ledstrip op en zetten hem aan
  strip.begin();
  strip.show();

  // We definiëren dat het knopje als input gebruik moet worden
  pinMode(BTN_PIN, INPUT);
}
```

## Loop
In de `loop()` staat alle code die herhaald uitgevoerd moet worden. Hierin zullen we bepalen of het knopje ingedrukt wordt en of de ledring aan moet en hoe helder.

### Indrukken knopje
Met de `digitalRead()` functie kunnen we bepalen of het knopje ingedrukt wordt of niet. Vervolgens kunnen we in `lightOn` opslaan of de ring aan of uit moet staan. Als hij aan staat moet hij uit en vice-versa. Dus dan komen we tot de volgende code.

```arduino
// Als het knopje ingedrukt wordt moet het lampje aan of uit gaan
if (digitalRead(BTN_PIN)) {
  // We veranderen de waarde naar het tegenovergestelde van zijn vorige waarde, aan wordt dus uit en uit wordt aan
  lightOn = !lightOn;
}
```

#### Debouncen
Als je bovenstaande code zou gebruiken zul je merken dat de ledring willekeurig zal knipperen en zodra je het knopje loslaat hij ofwel aan ofwel uit staat. Dat komt doordat er twee problemen zijn. Allereerst bouncing, dat is dat wanneer je het knopje indrukt hij niet meteen volledig contact maakt maar een beetje "stuitert". Vanuit de code gezien heeft dat het effect alsof je heel snel achter elkaar het knopje indrukt. De makkelijkste oplossing is om even te wachten voordat we verder gaan om de bounce periode voorbij te gaan. Daarvoor kun je de `delay()` functie gebruiken. Persoonlijk gebruik ik vaak een delay van 300 miliseconden, dan weet je zeker dat het bouncen wel voorbij is.

Het andere probleem is dat het zo kan zijn dat iemand het knopje ingedrukt houd. In dat geval zal de ring gaan knipperen, en dat is ook een beetje raar. Dus na het debouncen is het slim om te wachten totdat de gebruiker het knopje losgelaten heeft.

Om deze twee punten op te lossen komen we tot de volgende code.
```arduino
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
```

### Weergeven ledring
Omdat het een nachtlampje is willen we hem een iets gelig licht geven. Dat kan door de waarde van het blauwe licht iets lager te maken dan de recht. Die kleur kunnen we voor elke pixel als volgt instellen.
```arduino
for (int i = 0; i < strip.numPixels(); i++) {
  strip.setPixelColor(i, 255, 255, 75);
}
```

Vervolgens willen we de helderheid van de ring aanpassen aan de stand van de potentiometer. Dus moeten we de waarde daarvan eerst uitlezen met de `analogRead()` funcie en opslaan. De helderheid van de ledring moet ingesteld worden met een waarde tussen de 0 en de 255 maar de maximale waarde die uit de `analogRead()` functie komt is 1023, dus delen we die door 4. Daarna stellen we de helderheid van de strip ermee in.
```arduino
int brightness = analogRead(POT_PIN) / 4;
strip.setBrightness(brightness);
```

Dit alles moet natuurlijk alleen gebeuren als de ledring aan moet staan. Als hij uit moet staan dan moet de helderheid 0 zijn. Dit kan met een if statement als volgt.
```arduino
if (lightOn) {  
  // Alles om het lampje aan te zetten en de helderheid in te stellen
} else {
  // Als hij uit moet staan zetten we de felheid op 0
  strip.setBrightness(0);
}
```

Tot slot moeten we niet vergeten om de wijzingen aan de pixels naar de ledring te versturen.
```arduino
strip.show();
```

## Volledig script
Als je alle stappen gevolgd hebt moet je op de volgende code uitkomen.
```arduino
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
```
