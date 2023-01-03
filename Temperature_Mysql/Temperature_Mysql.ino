#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
// #include <Ultrasonic.h>
// Instantiate trig and echo pin for ultrasonic sensor
//Ultrasonic ultrasonic(5, 4);
const char* ssid     = "BOARD ROOM";
const char* password = "";

 const int trigPin1 = 5;
 const int echoPin1 = 13;

const int trigPin2 = 4; //4
const int echoPin2 = 15; //15

const int trigPin3 = 12;
const int echoPin3 = 14;

#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration1,duration2,duration3;
float distanceCm1,distanceCm2,distanceCm3;
// const char* serverName = ;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input

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

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  
  // Calculate the distance
  distanceCm1 = duration1 * SOUND_VELOCITY/2;
  
  // Convert to inches
  // distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance1 (cm): ");
  Serial.println(distanceCm1);
//   // Serial.print("Distance (inch): ");
//   // Serial.println(distanceInch);
//   // Post data to dweet.io

// // ################################ for 2nd Sensor ################################
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  
  // Calculate the distance
  distanceCm2 = duration2 * SOUND_VELOCITY/2;
  
  // Convert to inches
  // distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance2 (cm): ");
  Serial.println(distanceCm2);


  // ################################ For 3rd Sensor #################################
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echoPin3, HIGH);
  
  // Calculate the distance
  distanceCm3 = duration3 * SOUND_VELOCITY/2;

  

  Serial.print("Distance3 (cm): ");
  Serial.println(distanceCm3);

  //########################################## Server code ##############################
  
HTTPClient http1,http2,http3;
WiFiClient client1,client2,client3;

 if (distanceCm1 < 10) {
    String URL1 = "http://122.252.239.17/arduino_basic/insert_temp.php?is_occupied="; // Works with HTTP
    URL1 += 1; // set to 1 means distance less than 10 cm and track occupied
    URL1 += "&id=1";
     http1.begin(client1,URL1); // Works with HTTP
  
      int httpCode = http1.GET();
      if (httpCode > 0) {
          String payload = http1.getString();
          Serial.println(payload); // Print response
      }
      Serial.println("Track occupied by Train");
      http1.end();

} else {

  String URL1 = "http://122.252.239.17/arduino_basic/insert_temp.php?is_occupied="; // Works with HTTP
    URL1 += 0; // set to 1 means distance less than 10 cm and track occupied
    URL1 += "&id=1";
     http1.begin(client1,URL1); // Works with HTTP
  
      int httpCode = http1.GET();
      if (httpCode > 0) {
          String payload = http1.getString();
          Serial.println(payload); // Print response
      }
      Serial.println("Track occupied by Train");
      http1.end();

} 

if(distanceCm2 < 10) {
   String URL2 = "http://122.252.239.17/arduino_basic/insert_temp.php?is_occupied="; // Works with HTTP
    URL2 += 1; // set to 1 means distance less than 10 cm and track occupied
    URL2 += "&id=2";
    Serial.println(URL2);
     http2.begin(client2,URL2); // Works with HTTP
  
      int httpCode = http2.GET();
      if (httpCode > 0) {
          String payload = http2.getString();
          Serial.println(payload); // Print response
      }
      Serial.println("Track occupied by Train");
      http2.end();

} else {

 String URL2 = "http://122.252.239.17/arduino_basic/insert_temp.php?is_occupied="; // Works with HTTP
    URL2 += 0; // set to 1 means distance less than 10 cm and track occupied
    URL2 += "&id=2";
     http2.begin(client2,URL2); // Works with HTTP
  
      int httpCode = http2.GET();
      if (httpCode > 0) {
          String payload = http2.getString();
          Serial.println(payload); // Print response
      }
      Serial.println("Track occupied by Train");
      http2.end();


}

if(distanceCm3 < 10) {
   String URL3 = "http://122.252.239.17/arduino_basic/insert_temp.php?is_occupied="; // Works with HTTP
    URL3 += 1; // set to 1 means distance less than 10 cm and track occupied
    URL3 += "&id=3";
     http3.begin(client3,URL3); // Works with HTTP
  
      int httpCode = http3.GET();
      if (httpCode > 0) {
          String payload = http3.getString();
          Serial.println(payload); // Print response
      }
      Serial.println("Track occupied by Train");
      http3.end();

} else {

   String URL3 = "http://122.252.239.17/arduino_basic/insert_temp.php?is_occupied="; // Works with HTTP
    URL3 += 0; // set to 1 means distance less than 10 cm and track occupied
    URL3 += "&id=3";
     http3.begin(client3,URL3); // Works with HTTP
  
      int httpCode = http3.GET();
      if (httpCode > 0) {
          String payload = http3.getString();
          Serial.println(payload); // Print response
      }
      Serial.println("Track occupied by Train");
      http3.end();

}
  
delay(1000);
}