# Introductie

In dit hoofdstuk hopen we je een basis uitleg van programmeren in C++ te geven met de Arduino library. We zullen alle belangrijke punten en concepten kort aanstippen. Hopelijk is dit voldoende om mee aan de slag te gaan of heb je hiermee voldoende aanknopingspunten om verdere informatie op te zoeken.

## Basis programma

Ieder Arduino script heeft altijd twee blokken: void setup() en de void loop().

```arduino
#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
```

### void setup()

De void setup() staat aan het begin van het script. In de void setup() staat alles wat we nodig gaan hebben tijdens het runnen van het script. Je kan het zien als een soort van boodschappenlijst alleen vervangen we de meel en boter voor pins en variablen. Zoals je wellicht heb gezien staat er na de void setup() twee accolades {}. Tussen deze twee accolades wordt alles gezet wat we in de setup willen hebben.

De void setup() wordt maar 1 keer gelezen door de Arduino en dat is na het opstarten van het programma.

### void loop()

In de void loop() vertel je de arduino wat het moet doen. Het is een beetje hetzelfde als het recept van een taart. We hebben tijdens de void setup() eerst boodchappen gedaan en nu gaan we met de void loop() het recept volgen. De instructies in de void loop() vorden oneindig lang herhaald, vandaar ook de naam!

Net zoals bij de void setup() begint en eindigd de void loop() met accolades. Het grote verschil, naast de herhaling, is dat er in de void loop() meerdere blokjes code kunen staan. Deze blokjes code noem je methods en die hebben ook allemaal weer hun eigen accolades. Zo verdeel de code in stukje met ieder een eigen functie.

### Puntkomma

Iets waar arduino sketches heel erg van houden zijn puntkommas. Achter iedere regel moet een puntkomma! Met een ; sluit je een regel af en zeg je als het ware tegen de arduino: 'goed gedaan jonge, nu aan het werk met de volgende regel'. Het vergeten van een ; is ook een van de meest voorkomende redenen waarom een script het niet doet.

## Comments

Naast het feit dat je in een script tegen de Arduino vertelt wat het moet doen is het soms ook even heel fijn om tegen jezelf te praten of om even uit te leggen wat je aan het doen bent. Voor deze gevallen kan je een comment plaatsen.

Wanneer je een comment plaatst zeg je eigenlijk tegen de Arduino:'Wat ik hier opschrijf gaat jou helemaal niets aan en daar hoef jij dan ook niets mee te doen'.

```arduino
// single line comment
```

```arduino
/*
 Multi
 line 
 comment
*/
```

## Variabelen

Goed, het is tijd om een jeugdtraumaatje op te halen. Ik neme je mee terug naar de rekenles op de basisschool. Je zit voor in de klas, let goed op en opeens vraagt de juf of meester aan jou: 'Als Pietje 9 appels heeft en hij geeft 4 appels weg, hoeveel appels heeft Pietje dan nog?' Met de volste overtuiging zeg jij: '4 juf'. Wat heb je lekker opgelet en je kan niet wachten op het complimentje dat je van de juf gaat krijgen. Maar tot je grote schrik krijg je helemaal geen comlimentje maar de juf zegt: '4 wat? 4 koeien? 4 broden? 4 euro?' Oh ja! Dat wa ook zo: '4 appels juf!'

Net zoals de 4 appels moet ook alles in een script een naam hebben. Dit noemen we variablem. Variablen vertegenvoordigen een getal of een tekst met een logische naam. Voorbeelden zijn bijvoorbeeld ledPin of onTime. Variablen kun je waardes geven.

Even weer terug naar het jeugdtrauma. Appels is in dat geval het variable. Aan het begin (void setup()) had Pietje 9 appels en tijdens de eerste run van de void loop() heeft pietje er 4 weg gegeven. Hier kan je goed zien dat de waardes van variablen door het hele script heen kunnen veranderen en dus niet perse een vast waarde hebben!

### Declaratie en gebruik

```arduino
int variable;
```

```arduino
int variable = 0;
variable = 10;
```

### Datatypes

| Naam                  | Keyword  | Omschrijving                       | Minimum     | Maximum    |
|-----------------------|----------|------------------------------------|-------------|------------|
| Integer               | `int`    | Gehele getallen                    | -2147483648 | 2147483647 |
| Character             | `char`   | Letters                            | 0           | 255        |
| Boolean               | `bool`   | Waar of niet waar                  | 0 (`False`) | 1 (`True`) |
| Floating point        | `float`  | Kommagetallen                      |             |            |
| Double floating point | `double` | Kommagetallen met dubbele precisie |             |            |

#### Casten

### Operators

Operators zijn symbolen die aangeven dat er een bepaalde wiskundige of logische manipulatie gedaan moet worden.

#### Wiskundig

| Operator              | Omschrijving                        |
|-----------------------|-------------------------------------|
| +                     | getallen bij elkaar optellen        |
| -                     | getallen van elkaar aftrekken       |
| *                     | getallen met elkaar vermenigvuldigen|
| /                     | Getallen door elkaar delen          |
| %                     | Rest van een deling                 |

#### Toewijzingen

| Operator                | Omschrijving                                     |
|-------------------------|--------------------------------------------------|
| + =                     | Wijst het resultaat van een toevoeging toe       |
| - =                     | Wijst het resultaat va een aftrekking toe        |
| * =                     | Wijst het resultaat van een vermenigvuldiging toe|
| %                       | Wijst de rest van een divisie toe                |
| &                       | Wijst het resultaat van een logische AND toe*    |
| \|                      | Wijst het resultaat van een logische OR toe      |
| !                       | Geeft aan dat iets, niet, is                     |

##### AND operator

Een AND operator is een boolean operator.  Een boolean heeft maar twee mogelijke resultaten: Waar(1) op niet waar(0). Een boolean heeft verschillende inputs. Bij een simpele boolean zijn er twee inputs.

Een AND Operator is waar (1) wanneer alle inputs ook waar zijn. Even een voorbeeldje:
Boolean: Ruben en Hilke hebben allebei blond haar
Input 1: Ruben heeft bruin haar
Input 2: Hilke heeft blond haar
Wanneer we naar de input kijken kunnen we zien dat maar 1 van de twee inputs klopt. Ruben heeft helemaal geen blond haar. Dit houdt in dat de AND operator een onwaar of een 0 terug geeft.

We zouden de input ook anders op kunnen schrjiven:
Input 1: Ruben !blond (Zie je wat hier gebeurd, er wordt nu aangegeven dat Ruben geen blond haar heeft. Wat hij wel heeft is onduidelijk maar dat doet er nu niet toe!)
Input 2: Hilke heeft blond haar

##### OR operator

Een OR operator lijkt hele erg op de AND operator. Er is alleen een groot verschil: Om ervoor te zorgen dat de boolean waar (1) terug geeft hoeft er maar 1 van de inputs waar te zijn.

Als we dan weer gaan kijken naar het eerdere voorbeeld:
Boolean: Ruben en Hilke hebben allebei blond haar
Input 1: Ruben heeft bruin haar
Input 2: Hilke heeft blond haar
Daar waar het resultaat van de AND operator niet waar (0) was is deze bij de OR operator wel waar (1). 1 van de inputs klopt, Hilke heeft namelijk blond haar.

#### Vergelijkingen

| Operator              | Omschrijving                              |
|-----------------------|-------------------------------------------|
| <                     | Waarde x is kleiner dan waarde y          |
| <=                    | Waarde x is kleiner of gelijk aan waarde y|
| >                     | Waarde x is groter dan waarde x           |
| >=                    | Waarde x is groter of gelijk aan waarde y |
| ==                    | Waarde x is waarde y                      |

### Scope

Wanneer je een script schrijft heb je zolas eerder vermeld variablen nodig (ja, ik tune toch nog een keertje in op het jeugdtrauma). Nu heb je keuze tussen twee smaakjes van dat trauma eehhhh keuze tussen twee soorten variablen: global variables en local variables

#### Global variables

Global variables zijn variables die gedeclared zijn buiten functies en die global variables kunnen dus gebruikt worden door iedere funcite. Ze zijn zeg maar niet in een hokje gestopt en iedere functie kan aanspraak maken op een global variable. Een global variable is een soort van Albert Heijn, iedereen heeft toegang tot een Albert Heijn en wij mogen naar harte lust appels, Grolsch en andere vernaperingen halen.

#### Local variables

Local variables zijn net wat anders. Een local variable wordt gedeclared in een specifieke functie en deze variable kan dan ook alleen maar worden gebruikt binnen die specifieke functie. Het is dus geen Albert Heijn maar de koelkast op Shine. Niet iedereen heeft toegang tot die koelkast maar iedereen op huize Shine mag wel alles in de koelkast gebruiken.

```arduino hl_lines="4 5"
int value = 10; // this is a global variable

void setup() {
  int scopedValue; // this variable exists only in this scope
  scopedValue = 11;
}

void loop() {
  // value is accessible here, scopedValue not
}
```

### Arrays

Een array is een lijst van waarden. Alle waarden in de array moeten hetzelfde datatype hebben en binnen Arduino is het verplicht om vooraf aan te geven hoe lang de array is, oftewel hoeveel waarden er in passen. Vervolgens kun je de verschillende waarden in de lijst opvragen en aanpassen.

#### Een array aanmaken

Je maakt een array aan door aan te geven welk datatype hij heeft en hoe lang de array moet zijn. Bijvoorbeeld een lijst van 6 integers.

```arduino
int integerArray[6];
```

Het is ook mogelijk om meteen waarden in de lijst te stoppen, bijvoorbeeld een lijst met alle weekdagen. Je hoeft dan niet persé de lengte nog op te geven, dat snap de compiler dan wel.

```arduino
String weekDays[]= {"Zondag", "Maandag", "Dinsdag", "Woensdag", "Donderdag", "Vrijdag", "Zaterdag"};
```

#### Waarden uit een array halen

Je kunt een waarde uit een bepaalde plek in de array halen aan de hand van de index van de waarde. Als we bijvoorbeeld de 5e waarde uit de array willen halen doen we dat op de volgende manier.

```arduino
int waarde = integerArray[4];
```

Daarbij moet je er op letten dat het eerste element in de array op index positie 0 staat. Programmeurs beginnen met tellen bij 0, dus het eerste element heeft index 0 en in een array met 6 waarden is de index van het laatste element dus 5.

Een ander aandachtspunt is dat je niet een waarde uit de array kunt opvragen die niet bestaat, bijvoorbeeld bij een array met lengte 6 geeft een poging om de waarde op index 6 op te halen een error, immers deze bestaat niet.

#### Waarden in een array stoppen

Je voegt een waarde aan een array toe op de volgende manier.

```arduino
integerArray[4] = 100;
```

#### Lengte van de array bepalen

Mocht je willen weten hoe lang een array is dan kun je de `sizeof(array)` functie gebruiken.

### Strings

Strings kun je gebruiken om woorden of zinnen in op te slaan. Eigenlijk zijn Stings een beetje bijzonder, in essentie is een woord of zin namelijk een lijst van letters. Een String bestaat dus eigenlijk uit een array van `char`s in volgorde. En dat maakt dat er wat speciale dingen gelden voor het werken met Strings. Meer informatie daarover vind je [in de reference](https://www.arduino.cc/reference/en/language/variables/data-types/stringobject/).

#### Een string aanmaken

Je maakt een string aan op de volgende manier.

```arduino
String zin = "Hello World!";
```

Handig om te weten is dat als je aan de string een enter toe wil voegen je daarvoor `\n` kunt gebruiken en een tab is `\t`.

## Besluiten maken

We zijn nu aangekomen bij een van de belangrijkste pricipes van programmeren, if-statements. Hiermee kun je bepalen of bepaalde stukken wel of niet uitgevoerd moeten worden. Een if statement heeft een conditie, en als die conditie waar is dan wordt de code uitgevoerd. De conditie kan van alles zijn zoals een boolean variabele, een vergelijking of een combinatie daarvan met and of or statements er tussen.

```arduino
if (condition) {
    // execute this code
}
```

Je kunt ook een alternatief geven voor als de conditie niet waar is door middel van een `else`. Met `else if` kun je code toevoegen die uitgevoerd wordt als de if en alle voorgaande else if condities niet waar zijn en de else if conditie wel.

```arduino
if (condition1) {
    // execute this code if condition 1
} else if (condition2) {
    // execute this code if not condition 1 but condition2
} else {
    // execute this code if neither condition 1 nor condition2
}
```

## Loops

### For loop

```arduino
for (int i = 0; i < 10; i++) {
    // execute this code 10 times
}
```

### While loop

```arduino
while (condition) {
    // execute this code until condition is false
}
```

## Seriële communicatie

```arduino
#include <Arduino.h>

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // Print the line "Hello World!"
  Serial.println("Hello World!");

  // wait for 1 second before printing again
  delay(1000); 
}
```

## Functies

```arduino
void function() {
    // execute code here
}
```

```arduino
int add(int param1, int param2) {
    return param1 + param2;
}
```

## Conclusie
