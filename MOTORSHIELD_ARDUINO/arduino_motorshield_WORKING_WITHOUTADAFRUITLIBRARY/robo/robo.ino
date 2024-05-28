//Robo India Line follower Tutorial
// This codes runs robo int the forward direction.

// Shield Pins Declaration 
int dataPin = 8;        
int latchPin = 12;
int clockPin = 4;
int en = 7;
void setup()
{
    pinMode(dataPin, OUTPUT);     // Setting up the motor shield. 
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(en, OUTPUT);    
    digitalWrite(en, LOW); 
 
 forward(); // This funtion for forward robot motion
 delay(1000);
 backward();
 delay(1000);
 halt();
 
  
 }

void loop()
{
  forward(); // This funtion for forward robot motion
 delay(1000);
 backward();
 delay(1000);
 halt();
}

void forward(void){
        digitalWrite(latchPin, LOW);            
        shiftOut(dataPin, clockPin, LSBFIRST, 3);
        digitalWrite(latchPin, HIGH);  

}

void backward(void){
        digitalWrite(latchPin, LOW);            
        shiftOut(dataPin, clockPin, LSBFIRST, 164);
        digitalWrite(latchPin, HIGH);  
}

void turn_left(void){
        digitalWrite(latchPin, LOW);            
        shiftOut(dataPin, clockPin, LSBFIRST, 161);
        digitalWrite(latchPin, HIGH);  
}

void turn_right(void){
        digitalWrite(latchPin, LOW);            
        shiftOut(dataPin, clockPin, LSBFIRST, 38);
        digitalWrite(latchPin, HIGH);  
}

void halt(void){
        digitalWrite(latchPin, LOW);            
        shiftOut(dataPin, clockPin, LSBFIRST, 32);
        digitalWrite(latchPin, HIGH);  
}

