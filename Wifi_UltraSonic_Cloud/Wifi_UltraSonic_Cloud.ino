
#include <SoftwareSerial.h>
#include <stdlib.h>
#define SSID "Prashant" //Replace your wifi SSID name 
#define PASS "12345678" // Replace your wifi psssword 
String RES_input;
String WIFI_input="";
int CNT = 7;
int i = 1;
int Start_chck = 0;
String apiKey = "AIQ5HNUOPZ8K5IBG"; // replace with your channel thingspeak Write API key
SoftwareSerial WiFi_Serial(3, 4); // RX, TX
int trigPin1 = 6;
int echoPin1 = 7;
void setup() 
{                
      Serial.begin(9600);
      WiFi_Serial.begin(9600);
      WiFi_Serial.println("AT+UART_DEF=9600,8,1,0,0");
      delay(2000);
      WiFi_Serial.begin(9600);
      WiFi_Serial.println("ATE1");
      delay(200);
      WiFi_Serial.println("AT+CWQAP");
      pinMode(trigPin1, OUTPUT);
      pinMode(echoPin1, INPUT);
}

void WIFI_Check()
  {
      WiFi_Serial.println("AT");
      delay(1500);
      if(WiFi_Serial.available())
        {
         if(WiFi_Serial.find("OK"))
           {
             Serial.println("WIFI PLUGGED ON TO THE BOARD..!");
             Serial.println();
             Serial.println();
             WiFi_Serial.println("AT+CWMODE=1");
             delay(500);
             Start_chck = 1;
             i = 1;
            }
         }
      else
      {
      Serial.println("WIFI NOT PLUGGED..!");
      Serial.println();
      Serial.println("PLUG IN YOUR WIFI CHIP");  
      Serial.println();
      Serial.println();
      }
  }

void connectWiFi()
 {
      WiFi_Serial.println("AT+CWJAP?");
      delay(5000);
      if(WiFi_Serial.available())
        {
          if(WiFi_Serial.find("No AP"))
            {
              Serial.println("NOT CONNECTED TO WIFI NETWORK");
              Serial.println();
              Serial.println();
              Serial.println("Trying to Connect to WiFi Network");
              String cmd = "AT+CWJAP=\"";
              cmd += SSID;
              cmd += "\",\"";
              cmd += PASS;
              cmd += "\"";
              WiFi_Serial.println(cmd);
              Serial.println(cmd);
              delay(6000);
              if(WiFi_Serial.available())
                {
                  String RES_input="";
                  while(WiFi_Serial.available()) // read the data into a variable as long as the 
                    {
                      RES_input+= (char)WiFi_Serial.read();
                    }
                      Serial.println(RES_input);
                      if(WiFi_Serial.find("WIFI CONNECTED"))
                        {
                          Serial.println("CONNECTED TO WIFI NETWORK..!");
                        }
                 }
              }
          else
            {
              Serial.println("CONNECTED TO WIFI NETWORK..!");
              Serial.println();
              Serial.println();
              post_data();
              i = 0;
            }
         }
    }
 
void post_data()
{  
  long duration1, distance1;
  digitalWrite(trigPin1,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin1, LOW);
  duration1=pulseIn(echoPin1, HIGH);
  distance1 =(duration1/2)/29.1;
  distance1 = 15;
  Serial.print(distance1);
  delay(10);
  // convert to string

  char buf[16];
  String strTemp1 = dtostrf(distance1, 4, 1, buf);
//  Serial.println(strTemp1);

//  Serial.println(strTemp2);
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  WiFi_Serial.println(cmd);

  if(WiFi_Serial.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(strTemp1);
//  getStr += "&field2=";
//  getStr += String(strTemp2);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  WiFi_Serial.println(cmd);
  Serial.println(cmd);

  if(WiFi_Serial.find(">"))
  {
    WiFi_Serial.print(getStr);
    Serial.println("Data Send Successfully On Thing speak");
  }
  else
  {
    WiFi_Serial.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }

  // thingspeak needs 15 sec delay between updates
  delay(10000);  
}
void loop()
{
  while (1)
  {
    if (CNT < 1) //CNT for Time Delay
    {
      if (Start_chck == 0)
      {
        WIFI_Check();
        if (i == 1)
        {
          connectWiFi();
        }
      }
      else
      {
        CNT = 7;
        Start_chck = 0;
      }
    }
   // Serial.println();
    CNT--;
  }
}