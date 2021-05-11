# Datum en tijd

Om de huidige datum en tijd te gebruiken binnen je applicatie kun je gebruik maken van de NTPClient library. Om deze te installeren ga je naar **Sketch > Library > Manage Libraries** en zoek je naar NTPClient. Deze library verbint via Wifi met een server die de huidige datum en tijd kan vertellen. Een voorbeeld van een zogenaamde NTP server is pool.ntp.org.

## Functies
De library heeft de volgende functies.
- `getDay()` geeft een nummer dat overeenkomt met de dagen van de week waarbij 0 zondag is.
- `getHours()` geeft een nummber met het huidige uur in 24 uurs formaat.
- `getMinutes()` geeft een nummer met de huidige minuut.
- `getSeconds()` geeft een nummer met de huidige seconde.
- `getEpochTime()` geeft een unsigned long met de huidige epoch tijd in seconden. Dat is het aantal seconden sinds middernacht 1 januari 1970 in GMT.
- `getFormattedTime()` geeft een String met de tijd in HH:MM:SS format.

Er is geen functie om de datum te berekenen maar dit is wel af te leiden uit de epoch.

## Voorbeeld
In het onderstaande voorbeeld worden alle functionaliteiten van de NTPclient library gedemonstreerd.
```c++
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char *ssid     = "REPLACE_WITH_YOUR_SSID";
const char *password = "REPLACE_WITH_YOUR_PASSWORD";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(0);
}

void loop() {
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);  

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute); 
   
  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond);  

  String weekDay = weekDays[timeClient.getDay()];
  Serial.print("Week Day: ");
  Serial.println(weekDay);    

  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  String currentMonthName = months[currentMonth-1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

  int currentYear = ptm->tm_year+1900;
  Serial.print("Year: ");
  Serial.println(currentYear);

  //Print complete date:
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  Serial.print("Current date: ");
  Serial.println(currentDate);

  Serial.println("");

  delay(2000);
}
```

## Werking
Allereerst moeten de benodigde libraries toegevoegd worden.

```c++
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
```

Vervolgens maken we twee variabelen aan waarin we de naam van het wifi netwerk en het wachtwoord in opslaan.
```c++
const char *ssid     = "NETWERKNAAM";
const char *password = "WACHTWOORD";
```

Daarna maken we een NTP client aan om de datum en tijd mee op te halen.
```c++
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
```

### setup()
In de `setup()` maken we verbinding met het internet. Voor het gemak printen we de status hiervan naar de serialmonitor, dit zo je kunnen weglaten.
```c++
Serial.begin(9600);

Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
```

Hierna initializeren we de NTP client.
```c++
timeClient.begin();
```

#### Tijdszone
Je kunt de huidige tijdszone instellen met de `setTimeOffset()` methode. Hier geef je het aantal seconden verschil met GMT, Nederlandse wintertijd is 3600 en zomertijd is 7200.
```c++
timeClient.setTimeOffset(3600);
```

### loop()
In de `loop()` roepen we de `update()` functie aan om de huidige datum en tijd op te halen van de NTP server.
```c++
timeClient.update();
```

#### Tijd ophalen
Als we de huidige epoch tijd willen printen dan kan dat als volgt.
```c++
unsigned long epochTime = timeClient.getEpochTime();
Serial.print("Epoch Time: ");
Serial.println(epochTime);
```

De `getFormattedTime()` functie kan de tijd in een geformatte string weergeven.
```c++
String formattedTime = timeClient.getFormattedTime();
Serial.print("Formatted Time: ");
Serial.println(formattedTime);  
```

Om de uren, minuten of seconden te bepalen kun je gebruik maken van de `getHours()`, `getMinutes()` en de `getSeconds()` functies.
```c++
int currentHour = timeClient.getHours();
Serial.print("Hour: ");
Serial.println(currentHour);  

int currentMinute = timeClient.getMinutes();
Serial.print("Minutes: ");
Serial.println(currentMinute); 
   
int currentSecond = timeClient.getSeconds();
Serial.print("Seconds: ");
Serial.println(currentSecond);  
```

#### Datum ophalen
De `getDay()` functie geeft alleen een nummer tussen de 0 en 6, waarbij zondag 0 is, om de dag aan te geven. Als je graag de naam van de dag wilt printen dan kun je deze uit een lijst halen als volgt.
```c++
String weekDays[7]={"Zondag", "Maandag", "Dinsdag", "Woensdag", "Donderdag", "Vrijdag", "Zaterdag"};

String weekDay = weekDays[timeClient.getDay()];
Serial.print("Week Day: ");
Serial.println(weekDay);  
```

Er is geen standaard functie om de huidige datum op te halen. Het is wel mogelijk dit te bepalen door middel van een time structure. Meer informatie hierover vind je in de [c++ referentie](http://www.cplusplus.com/reference/ctime/tm/) of kijk in het voorbeeld.
