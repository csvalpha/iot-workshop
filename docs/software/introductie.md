# Introductie


## Basis programma


```arduino
#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
```

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


#### Toewijzingen

#### Vergelijkingen


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