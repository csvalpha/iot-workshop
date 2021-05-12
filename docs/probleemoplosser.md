# Probleemoplosser
Help, alles gaat mis! Gelukkig hebben we hier een aantal tips om je problemen op te lossen. Het is natuurlijk altijd mogelijk om iemand om hulp te vragen. Voor alle problemen hier niet beschreven raden we aan om het volgende liedje op vol volume af te spelen: [https://youtu.be/oeCVXHPZ9WY](https://youtu.be/oeCVXHPZ9WY).

## Software
### Ik pas de kleur van de pixels aan maar ik zie de ledring niet veranderen
Als je de `setPixelColor()` functie of de `setBrightness()` gebruikt in de Neopixel library zul je eerst de `show()` functie aan moeten roepen voordat je wijzigingen op de ledring getoond worden.

### Ik krijg een error dat ik niet naar de COM poort kan schrijven of dat deze bezet is
Onder Windows mag maar één programma tegelijkertijd met een COM poort communiceren. Als je dus een seriële monitor open hebt staan en tegelijkertijd de chip probeert te programmeren werkt dat niet. Controleer of er niet per ongeluk nog een verbinding open staat.

Mogelijk zijn er twee apparaten met hetzelfde COM poort nummer. Dit is een uitzonderlijk geval en heeft vaak te maken met verbonden bluetooth apparaten. Probeer een andere USB poort te gebruiken en controleer of je de goede poort geselecteerd hebt.

Het kan gebeuren dat er wat mis gaat en de COM poort in Windows gereserveerd blijft maar dat het programma dat deze reservering plaatste al is afgesloten of is gechashed. In dat geval is de enige oplossing om je computer opnieuw op te starten.

## Hardware
### Als ik mijn ledring felle kleuren of veel wit laat weergeven gaat hij uit
Hoe feller en witter de kleuren, hoe meer stroom de ledring gebruikt. Als de ledring volledig wit is op volle helderheid gebruikt hij ongeveer 2A. Het kan zijn dat de voeding die je gebruikt dit niet aan kan, kijk of je de kleuren minder fel kunt maken of zet je brightness iets lager.

### Er komt rook uit mijn microcontroller!
Trek snel de USB kabel er uit! Je hebt zojuist de magische rook laten ontsnappen. Zodra de magische rook, die alle elektronica laat werken, ontsnapt is kan het niet meer gerepareerd worden. De enige oplossing is huilen in een hoekje.
