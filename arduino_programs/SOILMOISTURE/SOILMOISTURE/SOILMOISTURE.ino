int waterPin = A0;
int greenLED = 5;
int redLED = 4;
 
int threshold = 750; //adjust depending on the value you wish to check for
 
void setup()
{
  //set pins and enable serial
  pinMode(waterPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  Serial.begin(9600);
}
 
void loop() {
  // read the input on analog pin 0:
  int moistureValue = analogRead(waterPin);
  Serial.print(moistureValue);
  if(moistureValue < threshold)
  {
    Serial.println(" : No water required");
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
  else 
  {
    Serial.println(" : I'm thirsty");
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
  delay(1000); //adjust if the readings are too slow/fast
}
 
