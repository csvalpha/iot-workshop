# Introductie


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
###void setup()
De void setup() staat aan het begin van het script. In de void setup() staat alles wat we nodig gaan hebben tijdens het runnen van het script. Je kan het zien als een soort van boodschappenlijst alleen vervangen we de meel en boter voor pins en variablen. Zoals je wellicht heb gezien staat er na de void setup() twee accolades {}. Tussen deze twee accolades wordt alles gezet wat we in de setup willen hebben.

De void setup() wordt maar 1 keer gelezen door de Arduino en dat is na het opstarten van het programma.

###void loop()
In de void loop() vertel je de arduino wat het moet doen. Het is een beetje hetzelfde als het recept van een taart. We hebben tijdens de void setup() eerst boodchappen gedaan en nu gaan we met de void loop() het recept volgen. De instructies in de void loop() vorden oneindig lang herhaald, vandaar ook de naam!

Net zoals bij de void setup() begint en eindigd de void loop() met accolades. Het grote verschil, naast de herhaling, is dat er in de void loop() meerdere blokjes code kunen staan. Deze blokjes code noem je methods en die hebben ook allemaal weer hun eigen accolades. Zo verdeel de code in stukje met ieder een eigen functie.

###puntkomma
Iets waar arduino sketches heel erg van houden zijn puntkommas. Achter iedere regel moet een puntkomma! Met een ; sluit je een regel af en zeg je als het ware tegen de arduino: 'goed gedaan jonge, nu aan het werk met de volgende regel'. Het vergeten van een ; is ook een van de meest voorkomende redenen waarom een script het niet doet. 
## Comments
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

### Strings

## Besluiten maken

```arduino
if (condition) {
    // execute this code
}
```

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
