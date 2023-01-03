
int LDRPin = A0;
int val = 0 ;
int light = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(light,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(LDRPin);
  Serial.println(val);

  if(val > 0 && val < 99)
  {
    // full led
    digitalWrite(light,HIGH);
  }
 
  else if(val >99 && val < 299)
  {
    digitalWrite(light,HIGH);
    delayMicroseconds(500);
    digitalWrite(light,LOW);
    delayMicroseconds(500);
  }
  // dim led
  else
  {
    digitalWrite(light,LOW);
  }
  // off led

}
