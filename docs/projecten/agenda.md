# Agenda
In dit project gaan we de tijd van de eerstvolgende google agenda afspraak ophalen en een balk laten aftellen totdat de afspraak begint. Allereest zullen we een Google script schrijven dat je agenda uitleest en een lijstje met afspraken voor de komende 24 uur opstelt. De ESP kan vervolgens via een url dat lijstje opvragen en de balk weergeven. De enige hobbel in het opvragen van de data is dat er een redirect in zit met een tweede url voordat we de echte data kunnen opvragen.

## Google script
Volg de volgende stappen om het google script aan te maken.

### Script aanmaken
Navigeer naar [https://script.google.com](https://script.google.com), log in met je google account waar ook je agenda aan verbonden is en maak een nieuw project aan door op de `Nieuw project` knop te drukken.

### Script schrijven
In de editor kunnen we vervolgens een script schrijven. Allereerst moeten we verbinding maken met de agenda. Hiervoor moet je de naam van de kalender invullen, vaak is dit je gmail email adres.
```javascript
var cal = CalendarApp.getCalendarById('calendar-name');
if (cal == undefined) {
  return ContentService.createTextOutput("no access to calendar");
}
```

Vervolgens berekenen we de start en eindtijd waartussen we alle agenda afspraken willen ophalen. In dit geval een periode van 24 uur vanaf nu.
```javascript
var start = new Date();
const oneday = 24*3600000; // [msec]
const stop = new Date(start.getTime() + 7 * oneday);
```

We halen alle events in deze periode uit de agenda op.
```javascript
var events = cal.getEvents(start, stop);
```

Daarna maken we een string aan waaraan we alle agenda afspraken van onszelf of waarvan we aangegeven hebben dat we aanwezig zijn toevoegen. We voegen aan die string de startijd in miliseconden epoch, de starttijd in tekst, of het event de hele dag duurt en de titel toe van elkaar gescheiden met een tab. Is dat wat veel als we eigenlijk alleen de tijd in epoch van de eerstvolgende afspraak nodig hebben? Ja eigenlijk wel, maar dit is een demo, het werkt, en nu heb je meer kennis om er ook andere dingen mee te doen.
```javascript
var str = '';
for (var ii = 0; ii < events.length; ii++) {

  var event=events[ii];    
  var myStatus = event.getMyStatus();

  switch(myStatus) {
    case CalendarApp.GuestStatus.OWNER:
    case CalendarApp.GuestStatus.YES:
    case CalendarApp.GuestStatus.MAYBE:
      str += event.getStartTime().getTime() + '\t' +
             event.getStartTime() + '\t' +
             event.isAllDayEvent() + '\t' +
             event.getTitle() +'\n';
      break;
    default:
      break;
  }
}
return ContentService.createTextOutput(str);
```

### Script implementeren
Rechtsboven zie je als het goed is een blauwe "implementeren" knop. Die moeten we gebruiken om een link voor het script te genereren. Maak een nieuwe implementatie aan. Kies als type een `web-app`, voer hem uit als jezelf en kies bij toegang voor iedereen. Dit betekend technisch gezien dat iedereen met de url je agenda kan zien. Nu is de url heel erg moeilijk te gokken, maar denk er wel even over na. Als ik beveiliging moet gaan uitleggen gaan we allemaal huilen, iets voor een andere keer.

Noteer van je implementatie de Implementatie-ID. Die hebben we straks nodig om de data op te halen.

### Volledig script
Voor de volledigheid hier het hele script.
```javascript
function doGet(e) {
  var cal = CalendarApp.getCalendarById('calendar-name');
  if (cal == undefined) {
    return ContentService.createTextOutput("no access to calendar");
  }

  var start = new Date();
  const oneday = 24*3600000; // [msec]
  const stop = new Date(start.getTime() + 7 * oneday);
  Logger.log(start);
  Logger.log(stop);
  
  var events = cal.getEvents(start, stop);
  
  var str = '';
  for (var ii = 0; ii < events.length; ii++) {

    var event=events[ii];    
    var myStatus = event.getMyStatus();
    
    switch(myStatus) {
      case CalendarApp.GuestStatus.OWNER:
      case CalendarApp.GuestStatus.YES:
      case CalendarApp.GuestStatus.MAYBE:
        str += event.getStartTime().getTime() + '\t' +
               event.getStartTime() + '\t' +
               event.isAllDayEvent() + '\t' +
               event.getTitle() +'\n';
        break;
      default:
        break;
    }
  }
  return ContentService.createTextOutput(str);
}
```

## ESP script
Het ESP script zal uit een aantal onderdelen bestaan. Allereerst een functie waarmee we een HTTPS GET request naar een server kunnen doen en de reactie van de server terug krijgen. Deze functie zullen we gebruiken in een andere functie waarmee we de tijd van de eerstvolgende afspraak ophalen. Deze tijd zullen we vervolgens opslaan en gebruiken voor het weergeven van een aftel ring.

### HTTPS GET request

### Eerstvolgende afspraak ophalen
We hebben een prachtige URL gegenereerd voor het ophalen van de agenda afspraken via een google script. De enige hindernis die we hebben is dat als we de url benaderen van het google script deze een redirect zal teruggeven. Je krijgt bij het opvragen van de url dus niet meteen de data die je wilt hebben maar een nieuwe url. Bij die nieuwe url kun je vervolgens wel de data ophalen. We moeten in het script dus inbouwen dat we eerst de redirect url verkrijgen en daarna de data opvragen.

#### Redirect url ophalen

#### Tijd ophalen

### Ring animeren

### Volledig script
```arduino
#include <Arduino.h>

// We voegen de Wifi en de NTPclient libraries toe waarmee we met wifi kunnen verbinden en de tijd kunnen ophalen
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// We voegen de Neopixel library toe waarmee we de ledring kunnen aansturen
#include <Adafruit_NeoPixel.h>

// We stellen het wifi netwerk en wachtwoord in
const char* ssid     = "SSID";
const char* password = "PASSWORD";

const char* host = "script.google.com";
const char* redirectHost = "script.googleusercontent.com";
const char* url = "/macros/s/YOUR_APP_ID/exec";

// We maken een Wifi en NTPclient object aan
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// We definiëren aan welke pinnen we de ledring aangesloten hebben en we maken een ledstrip object aan
#define LED_PIN D4
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// We maken een variabele aan waarin we de tijd van de volgende afspraak aanmaken.
int nextAppointmentTime = 0;

/**
 * Functie om door middel van een HTTPS GET request van een host en url data op te vragen
 * @param host Het domein dat benaderd moet worden
 * @param url De url op het domein dat benaderd moet worden
 * @return Een string met de volledige response
 */
String httpsGet(String host, String url) {
  // We gebruiken de WiFiClientSecure klasse om een TCP verbinding op te zetten
  WiFiClientSecure client;

  // Dit is de magische regel waarmee we alle beveiliging negeren en waardoor alles werkt
  // Als je een echt veilige verbinding op wilt zetten zou je nu dingen met certificaten moeten doen
  // Dat is kei veel werk en voor een simpele agenda export laten we het achterwege
  client.setInsecure();

  // We maken verbinding met de server
  const int httpPort = 443; // 80 is voor HTTP / 443 is voor HTTPS
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return "";
  }

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // We sturen de GET request naar de server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  // We wachten totdat we een header ontvangen
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  // Als er daarna een bericht terug komt slaan we het op in een string
  String response = "";
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
    response.concat(c);
  }

  Serial.println();
  Serial.println("closing connection");

  // We geven de string met het bericht terug
  return response;
}

/**
 * Functie om de tijd in epoch van de volgende afspraak op te halen
 * @returns Een integer met de tijd in epoch van de volgende afspraak
 */
int getNextAppointmentTime() {
  Serial.print("connecting to ");
  Serial.println(host);
  
  // We halen de redirect url op van het google script
  String redirectMessage = httpsGet(host, url);

  Serial.println("Redirect message: ");
  Serial.println(redirectMessage);

  // Er zit wat HTML in het redirect bericht en we hebben alleen de url nodig
  // Daarom bepalen we hier waar deze precies staat
  int from = redirectMessage.indexOf("/macros");
  int to = redirectMessage.indexOf("\">here");

  // Vervolgens slaan we de url op
  String redirectUrl = redirectMessage.substring(from, to);

  // De & in een url wordt vervangen door &amp; in HTML dus die moeten we omzetten voordat we hem kunnen gebruiken
  redirectUrl.replace("&amp;", "&");
  
  Serial.print("Redirect url: ");
  Serial.println(redirectUrl);

  // We halen de kalender events op vanaf de redirect url
  String calenderItems = httpsGet(redirectHost, redirectUrl);

  // Aangezien we alleen de tijd van de eerstvolgende event nodig hebben bepalen we waar die staat
  int start = calenderItems.indexOf("\n");
  int end = calenderItems.indexOf("\t");

  // De tijd in epoch slaan we op als string, het script geeft de epoch in miliseconden maar wij 
  // gebruiken seconden dus de laatste 3 getallen laten we achterwege
  String epoch = calenderItems.substring(start+1, end-3);

  Serial.print("Next item epoch: ");
  Serial.println(epoch);

  // De string zetten we om in een integer en geven we terug
  return epoch.toInt();
}

void setup() {
  // We starten de ledstrip op en zetten hem aan
  strip.begin();

  // We maken de ledstrip rood om aan te geven dat we nog niet met wifi verbonden zijn
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.setBrightness(25);
  strip.show();

  // We starten seriële communciatie op voor debugging
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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

  // We starten de tijd client op. Aangezien het google script al de correctie voor 
  // tijdzone doet hoeven we geen offset in te stellen
  timeClient.begin();
  timeClient.setTimeOffset(0);

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // We maken de ledstrip leeg om aan te geven dat we succesvol opgestart zijn
  strip.clear();
  strip.show();
  delay(500);
}

void loop() {
  timeClient.update();

  // We halen de volgende afspraak op als we nog niet weten wanneer het eerstvolgende event is of elke 10 minuten
  if (nextAppointmentTime == 0 || timeClient.getMinutes() % 10 == 0) {
    Serial.println("Updating next appointment time");
    nextAppointmentTime = getNextAppointmentTime();
  }

  Serial.print("Next appointment time: ");
  Serial.println(nextAppointmentTime);
  Serial.print("Current time: ");
  Serial.println(timeClient.getEpochTime());

  // We berekenen hoe lang het duurt tot de volgende afspraak
  int minutesToAppointment = (nextAppointmentTime - timeClient.getEpochTime()) / 60;
  Serial.print("Minutes to appointment: ");
  Serial.println(minutesToAppointment);

  // We zetten het aantal pixels aan dat overeen komt met hoeveel minuten het nog duurt
  // mits de afspraak binnen minimaal 60 minuten is.
  for (int i = 0; i < strip.numPixels(); i++) {
    if (i < minutesToAppointment && minutesToAppointment < 60) {
      strip.setPixelColor(i, 0, 255, 0);
    } else {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }
  strip.show();

  // Als de afspraak nu is moeten we de volgende afspraak inladen
  if (minutesToAppointment <= 0) {
    Serial.println("Appointment is now, updating next appointment time");
    nextAppointmentTime = getNextAppointmentTime();
  }

  // We wachten 1 minuut
  delay(60000);
}
```

## Verbeter mogelijkheden
Een optie is om meerdere agenda's uit te lezen en de kleur van die agenda mee te sturen. Dan kun je de kleur van de ledring aanpassen zodat je weet voor welke agenda de afspraak is. Verder zou je ook de kleur van groen naar rood kunnen laten verlopen hoe dichter je bij de tijd van de afspraak ben. Een andere optie is om de agenda afspraken, optioneel in kleuren, over een klok heen te leggen. Zodat je in een oogopslag kunt zien wanneer je bepaalde afspraken hebt. Stel dat je je collegerooster inlaad, dan zou je met rode strepen op de klok je collegetijden aan kunnen geven. Dan weet je 's ochtends meteen wat je te wachten staat die dag.
