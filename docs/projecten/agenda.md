# Agenda


## Google script

### Volledig script
```javascript
function doGet(e) {
  var cal = CalendarApp.getCalendarById('your.email@gmail.com');
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

### Volledig script
```arduino
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>

const char* ssid     = "SSID";
const char* password = "PASSWORD";

const char* host = "script.google.com";
const char* redirectHost = "script.googleusercontent.com";
const char* url = "/macros/s/YOUR_APP_ID/exec";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

#define LED_PIN D4
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int nextAppointmentTime = 0;

String httpsGet(String host, String url) {
  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;
  client.setInsecure(); // this is the magical line that makes everything work

  const int httpPort = 443; // 80 is for HTTP / 443 is for HTTPS
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return "";
  }

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  // if there are incoming bytes available
  // from the server, read them and print them:
  String response = "";
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
    response.concat(c);
  }

  Serial.println();
  Serial.println("closing connection");

  return response;
}

int getNextAppointmentTime() {
  Serial.print("connecting to ");
  Serial.println(host);
  
  String redirectMessage = httpsGet(host, url);

  Serial.println("Redirect message: ");
  Serial.println(redirectMessage);

  int from = redirectMessage.indexOf("/macros");
  int to = redirectMessage.indexOf("\">here");

  String redirectUrl = redirectMessage.substring(from, to);
  redirectUrl.replace("&amp;", "&");
  Serial.print("Redirect url: ");
  Serial.println(redirectUrl);

  String calenderItems = httpsGet(redirectHost, redirectUrl);
  int start = calenderItems.indexOf("\n");
  int end = calenderItems.indexOf("\t");
  String epoch = calenderItems.substring(start+1, end-3);
  Serial.print("Next item epoch: ");
  Serial.println(epoch);

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

  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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
  if (nextAppointmentTime == 0 || timeClient.getMinutes() % 10 == 0) {
    Serial.println("Updating next appointment time");
    nextAppointmentTime = getNextAppointmentTime();
  }

  Serial.print("Next appointment time: ");
  Serial.println(nextAppointmentTime);
  Serial.print("Current time: ");
  Serial.println(timeClient.getEpochTime());

  int minutesToAppointment = (nextAppointmentTime - timeClient.getEpochTime()) / 60;
  Serial.print("Minutes to appointment: ");
  Serial.println(minutesToAppointment);

  for (int i = 0; i < strip.numPixels(); i++) {
    if (i < minutesToAppointment && minutesToAppointment < 60) {
      strip.setPixelColor(i, 0, 255, 0);
    } else {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }
  strip.show();

  if (minutesToAppointment <= 0) {
    Serial.println("Appointment is now, updating next appointment time");
    nextAppointmentTime = getNextAppointmentTime();
  }

  delay(60000);
}
```

## Verbeter mogelijkheden
Een optie is om meerdere agenda's uit te lezen en de kleur van die agenda mee te sturen. Dan kun je de kleur van de ledring aanpassen zodat je weet voor welke agenda de afspraak is. Verder zou je ook de kleur van groen naar rood kunnen laten verlopen hoe dichter je bij de tijd van de afspraak ben. Een andere optie is om de agenda afspraken, optioneel in kleuren, over een klok heen te leggen. Zodat je in een oogopslag kunt zien wanneer je bepaalde afspraken hebt. Stel dat je je collegerooster inlaad, dan zou je met rode strepen op de klok je collegetijden aan kunnen geven. Dan weet je 's ochtends meteen wat je te wachten staat die dag.
