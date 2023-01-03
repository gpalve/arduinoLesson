int IRpin = 7;  // This is our input pin
int IRState = LOW;  // LOW MEANS NO OBSTACLE
void setup() 
{
  pinMode(IRpin, INPUT);
  Serial.begin(9600);
}
void loop() 
{
  IRState = digitalRead(IRpin);
  if (IRState == HIGH)
  {
    Serial.println("OBSTACLE!!,     OBSTACLE!!");
  }
  else
  {
    Serial.println("clear");
  }
  delay(500);
} 
