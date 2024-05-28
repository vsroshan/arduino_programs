void setup() {
  pinMode(2, INPUT); //Pin 2 as INPUT
  pinMode(3, OUTPUT); //PIN 3 as OUTPUT
  digitalWrite(2, LOW);
  
}

void loop() {
  if (digitalRead(2) == HIGH)
  {
  digitalWrite(3, HIGH);   // turn the LED/Buzz ON
  delay(100);                       // wait for 100 msecond 
  digitalWrite(3, LOW);   // turn the LED/Buzz OFF
  delay(1000);                       // wait for 100 msecond 
  }
}
