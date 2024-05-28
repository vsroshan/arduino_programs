//EMG sensor robotic hand controller 
//This code is for controlling a robotic hand with
//an EMG sensor. 
//
//© Au Robots 8.4.2017


//Necessary for controlling the servos
#include<Servo.h> 
int servoPin=3;
const int x =250; ///// This is the reference value and it
//will depend on your setup. You have to find it out 
//yourself by looking at the serial monitor and finding
//a value between the maximum and minimum value.

//Naming the servos

Servo servo2;


void setup() 
{ 
//Starting the serial monitor
Serial.begin(9600); 

//Configuring servo pins
servo2.attach(3); // pinky

} 


void loop() 
{ 
//Printing the EMG data
Serial.println(analogRead(5)); 

//If the EMG data is greater than x the hand closes
  if(analogRead(5) > x) {
    servo2.write(180);
   
  }

//If the EMG data is lower than x the hand opens
  else if (analogRead(5) < x) {
    servo2.write(38);
   
  }

//A delay to slow down the process
  delay(100);
} 
