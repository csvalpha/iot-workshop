# Projectoverzicht
Nu je de ledring in elkaar gezet hebt en weet hoe je hem moet programmeren is het tijd er wat leuks mee te maken. We hebben een paar handleidingen en wat ideeën op een rij gezet.

## Projecthandleidingen
We hebben een aantal projecten die je met de ledring kunt maken. Deze zijn in oplopende mate van complexiteit, beginnend met een nachtlampje en eindigend met een koppeling met je agenda. We zullen stap voor stap door de code heen lopen en aan het eind zullen we de volledige code weergeven van het project. Heb je dus geen zin om zelf te programmeren dan kun je dus altijd onze code gebruiken.

### Beginners: Nachtlampje
Voor wie geen ervaring heeft met Arduino en programmeren is dit een mooi startproject. Door middel van het knopje kun je de ledring aan en uit zetten. De potentiometer bepaalt hoe fel de ledring is.

### Gemiddeld: Wakeuplight
We breiden het nachtlampje uit zodat het vanaf een vooraf ingestelde tijd langzaam aan gaat tot de maximale helderheid die met de potentiometer is ingesteld. Om de tijd te bepalen verbinden we met een wifi netwerk.

### Gevorderd: Klok
De ledring heeft exact 60 ledjes, en in het project met de wakeuplight hebben we geleerd hoe we de tijd van het internet kunnen ophalen. Logischerwijs is het dus ook mogelijk om een klok te maken. Dat is wat we in dit project zullen doen.

### Expert: Agenda
Via de internetverbinding is het ook mogelijk om contact te leggen met andere webservers. In dit project zullen we de tijd van de eerstvolgende afspraak in een online agenda ophalen. En daar kunnen we leuke dingen mee doen. We zullen een teller maken die aftelt naar je eerstvolgende afspraak. Maar met een kleine aanpassing kun je een wakeuplight maken dat automatisch de goede tijd kiest op basis van je agenda, of de teller combineren met een klok.

## Doe je eigen project
We zijn uiteraard heel benieuwd welke leuke andere ideeën je hebt met deze ledring. Misschien maak je wel een statusbalk waarmee je kunt zien hoelang het nog duurt totdat de frituur klaar is. Of koop je een luchtkwaliteitssensor en weergeef je de luchtkwaliteit in je studeerkamer. Laat het ons vooral weten en dan zullen we je project aan deze pagina toevoegen. De volgende ideeën en voorbeelden zijn al ingestuurd.

### Pixel chaser
Probeer op het juiste moment op het knopje te drukken in dit spel waarmee je je reactietijd kunt meten. Is optioneel ook als drankspel te spelen. Een beschrijving hoe je dit doet vind je in deze video: [https://www.youtube.com/watch?v=hjqtJA7gVQ0](https://www.youtube.com/watch?v=hjqtJA7gVQ0). De aangepaste code voor de ESP8266 vind je in [de repository van deze workshop](https://github.com/csvalpha/iot-workshop/blob/master/src/pixelchaser/pixelchaser.ino). Om deze code uit te voeren zul je de [OneButton](https://github.com/mathertel/OneButton) library moeten installeren, dit kan op dezelfde manier als beschreven voor de Neopixel library in het Software hoofdstuk.

### Aansturen met app
Het is mogelijk om de ledring aan te sturen door middel van een app. Hiervoor kun je de WLED library installeren op de microcontroller. Hoe je dat doet vind je hier [https://github.com/Aircoookie/WLED/wiki](https://github.com/Aircoookie/WLED/wiki). Vervolgens kun je de [Android](https://play.google.com/store/apps/details?id=com.aircoookie.WLED) of [iOS](https://apps.apple.com/us/app/wled/id1475695033) app gebruiken om de kleur van de ledring aan te passen en animaties op de ring te weergeven. Via WLED is het mogelijk om de ledring aan veel andere diensten te koppelen zoals Philips Hue en Amazon Alexa.

### Koppelen met Google Home
Met wat extra stappen is het mogelijk om de ledring aan te sturen via Google Home. Door de beperkingen in Google Home is de functionaliteit wat minimaal en is het redelijk wat werk om op te zetten. Hoe je dit precies doet lees je in de handleiding [WLED met IFTTT en Google Home](https://www.instructables.com/WLED-on-ESP8266-IFTTT-Google-Assistant/).

### Weerbericht
Door een koppeling met buienradar wordt weergeven wat de weersverwachting van vandaag is. Voor dit project is helaas nog geen voorbeeldcode beschikbaar.

### Spotify discolicht
Hoe vet is het als je een discolamp hebt die automatisch mee knippert op het tempo van je huidige Spotify liedje. Via de spotify api kun je het tempo, de dansbaarheid en het energielevel van het huidige liedje ophalen en daar de ledring op aanpassen. Voor dit project is helaas nog geen voorbeeldcode beschikbaar.
