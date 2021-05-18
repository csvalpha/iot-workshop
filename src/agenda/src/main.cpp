#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid     = "ssid";
const char* password = "password";

const char* host = "script.google.com";
const char* redirectHost = "script.googleusercontent.com";
const char* url = "/macros/s/your-random-code/exec";

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

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);

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

  delay(50000);
}