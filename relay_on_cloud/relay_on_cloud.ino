#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid     = "BOARD ROOM";
const char* password = "";

const int relay = 5;

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);

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
  // Normally Open configuration, send LOW signal to let current flow
  // (if you're usong Normally Closed configuration send HIGH signal)

  HTTPClient http1;
  WiFiClient client1;
  String payload;

  String URL1 = "http://122.252.239.17/arduino_basic/relay_drive.php";

  http1.begin(client1,URL1); // Works with HTTP
  
      int httpCode = http1.GET();
      if (httpCode > 0) {
          payload = http1.getString();
          Serial.println("Current status is");
          Serial.println(payload); // Print response
      }
      http1.end();
  if(payload == "1") {
    digitalWrite(relay, HIGH);
    Serial.println(payload);
    //delay(5000);
  } else {
  digitalWrite(relay, LOW);
  Serial.println(payload);
  // delay(5000); 
  }
  

 
  
}
