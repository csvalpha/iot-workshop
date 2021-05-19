# Knopje
Knoppies! Helemaal leuk! Eigenlijk is een knopje net zoals een ophaalbrug. Wanneer de ophaalbrug open is kan er geen verkeer door heen en wanneer deze weer dicht is kan je er weer over heen fietsen. Zo gaat het met een knopje ook. 
Een knopje overbrugt een gat in een circuit. Als er een gat is het circuit zit betekent dit dat de stroom niet verder kan. Wanneer een knopje dan ingedrukt wordt, wordt er als het ware een brug gecreëerd waardoor de stroom weer verder.
    
![Knopje](../assets/images/Button.png)

## Solderen
Soldeer een draad vanaf de `3V3` aansluiting aan een van de aansluitingen van het knopje. Op de afbeelding is dit een rode draad die aan de `3V3` aansluiting van de potentiometer gesoldeerd is. Soldeer vervolgens een draad van de andere aansluiding van het knopje naar de `D8` pin van de ESP.
    
![Knopje aansluiting op esp](../assets/images/hardware-potentiometer.jpg)

Vervolgens kun je de weerstand als pull-down resisor solderen. Daarvoor soldeer je de ene kant van de weerstand aan `D8` en de andere kant aan de `GND` pin. Let op dat de weerstand geen andere pinnen of elektronische componenten raakt. Je zou voor de zekerheid wat tape kunnen gebruiken.

![Pull-down resistor aansluiting op esp](../assets/images/hardware-knopje.jpg)

!!! tip "Dit is een goed moment om je hardware te testen"
    Tenzij je erg veel zelfvertrouwen hebt raden we je aan om op dit moment je hardware te testen. Controleer eerst goed of geen van je draden elkaar raken waar dat niet zou moeten. Plaats zo nodig preventief wat tape. Volg de stappen in [Arduino IDE](../software]) om vervolgens de [test code](../software/#test-code) uit te voeren. Als alles correct aangesloten is zal er een regenboog over de ledring cirkelen. Door aan de draaiknop te draaien moet deze sneller of langzamer gaan draaien. Als je het knopje indrukt moet deze stoppen met draaien. Werkt alles? Gefeliciteerd! Dan kun je nu door naar de behuizing.
