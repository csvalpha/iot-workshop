# Voltage divider
!!! info "Je kunt dit hoofdstuk overslaan als je alleen maar wilt bouwen"
    We willen je graag wat achtergrondinformatie geven over het aansluiten van bepaalde componenten. Deze basis zou voldoende moeten zijn om de meeste componenten op een Arduino aan te kunnen sluiten. Oftewel, om alles te bouwen wat je maar zou willen.

Ha wat episch dat jij dit stukje door leest! Wellicht heb je al kennis van elektronica, stroom en andere machtig mooie dingen maar het kan heel goed zijn dat je die kennis nog niet hebt! We willen je graag de voltage divider uitleggen of in het Nederlands: ‘de spanningsdeler’. 

Een voltage divider is een circuit die de spanning (V) die aan het begin binnen komt in kleinere deelspanningen aan het einde splitst. Dit komt door een serieschakeling van weerstanden waardoor de totale spanning over de weerstanden wordt verdeelt. Mocht je de deelspanningen bij elkaar optellen dan krijg je, ja je raad het al, de totale begin spanning. En dit is samen te vatten in de voor iedereen wel bekende formule: V=I*R

![Formule Voltage Divider](../assets/images/Formula_Divider.png){ align=left }

De deelspanning die iedere weerstand krijgt hangt af van de grootte van de weerstanden en de spanning aan het einde hangt af van de verhouding tussen de twee weerstanden. Weerstanden van 9 Ohm + 10 Ohm geeft dus het zelfde resultaat als 9 kOhm + 10 kOhm.

![Circuit Voltage Divider](../assets/images/Vol_Divider.png){ align=right }

Helemaal leuk dit maar hoe werkt zo’n voltage divider dan nou precies. Zie het zo, als je begint 12V en je wil een output voltage (Vout) van 6V dan kan je een voltage divider gebruiken. Dit circuit splits de output voltage dan in bijvoorbeeld 2x 6V (6V naar ground en 6V als Vout). Belangrijk hier is dan een voltage divider de output voltage splitst in meerdere stukjes en dus niet verminderd. Als je de output voltage wilt verminderen dan moet je een transformator gebruiken :)
