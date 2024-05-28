#include <IRremote.h>
int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;
int red = 6;
int green = 5;
void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  irrecv.enableIRIn();
}
void loop() {
 
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    delay(100);
    Serial.println(results.value);
    if(results.value==4294967295)
     {
         digitalWrite(red, HIGH); 
         delay(1000);       
     }
     else if(results.value==13033)
     {
        
        digitalWrite(green,HIGH);
        delay(1000); 
     }  
      else if(results.value==2704)
     {
        
        digitalWrite(green,LOW);
        digitalWrite(red, LOW);   
        delay(1000);      
     }  
     
irrecv.resume();
}
}
