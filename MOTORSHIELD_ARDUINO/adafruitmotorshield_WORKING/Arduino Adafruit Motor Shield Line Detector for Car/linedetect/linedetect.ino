#include <AFMotor.h>

/*
This is a line following robot car using Adafruit motor shield and 4 line detecting sensors. Motor speed ranges between 0 to 255 rpm.

Sensors are set in the following format in the front of the car: rightBackgroundDetector | rightMiddleLineDetector | leftMiddleLineDetector | leftBackgroundDetector

This code will assume you are starting on a white background with black line; then moving into black background with white line; and when it reach to the end with all white strip it will stop.

You can set the following variables:

MAX_SPEED 107 //Maximum speed of motor
MIN_SPEED 0 //Minimum speed of motor
TURN_SPEED 97 //Turning speed of motor

THRESHOLD 500 //Threshold to detect the line sensor, greater than 500 means it detected black line.

bg_right A5 //Port for right background detector

ir_right A3 //port for middle right line detector
ir_left A2 //port for middle left line detector
bg_left A0 //port for left background detector

got questions? twitter @ranchmobile

*/

#include <AFMotor.h>

#define MAX_SPEED 107
#define MIN_SPEED 0

#define TURN_SPEED 97

#define THRESHOLD 500

#define bg_right A5
#define ir_right A3
#define ir_left A2
#define bg_left A0

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(4, MOTOR12_1KHZ); 

boolean leftFlag = false;
boolean rightFlag = false; 
boolean bgLeftFlag = false;
boolean bgRightFlag = false; 

int leftSpeed = 0;
int rightSpeed = 0;

boolean isInBlackBackground = false;

boolean isRobotStarted = false;
boolean isStop = false;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(ir_left, INPUT);
  pinMode(ir_right, INPUT);
  pinMode(bg_left, INPUT);
  pinMode(bg_right, INPUT);
  
  leftSpeed = TURN_SPEED;
  rightSpeed = TURN_SPEED;
  
}

void loop() {
	
	checkStatus();
	
	if(!isStop)
	{
		//Serial.println("Running ... ");
		
		if(isInBlackBackground)
		{
			followLineOnBlackBG();
		}
		else
		{
			followLineOnWhiteBG();
		}
	}
	else
	{
		halt();
	}
	
	delay(50);

}

void checkStatus()
{
	bgLeftFlag = isBackgroundLeftDetectorOnBlack();
  	bgRightFlag = isBackgroundRightDetectorOnBlack();
  	leftFlag = isMiddleLeftDetectorOnBlack();
  	rightFlag = isMiddleRightDetectorOnBlack();
  	
  	isInBlackBackground = isBlackBackground();
  		
  	if(!isRobotStarted)
  	{
  		isRobotStarted = isStartDetected();
  	}
  	
  	if(!isStop)
  	{
  		isStop = isStopDetected();
  	}  	
}

boolean isStartDetected()
{
	return true;
	/*
  	if(bgLeftFlag && bgRightFlag && leftFlag && rightFlag)
  	{
  		return true;
  	}
  	else
  	{
  		return false;
  	}
  	*/
}

boolean isStopDetected()
{
	if(!isInBlackBackground)
	{
		return false;
	}
	
  	if((!bgLeftFlag) && (!bgRightFlag) && (!leftFlag) && (!rightFlag))
  	{
  		return true;
  	}
  	else
  	{
  		return false;
  	}
	
}

boolean isBlackBackground(){
	if(!isInBlackBackground)
	{
	  	if(bgLeftFlag && bgRightFlag && ( (!leftFlag) || (!rightFlag)))
	  	{
	  		isInBlackBackground = true;
	  	}
	}
	
	return isInBlackBackground;
}

void speedSet(int left, int right)
{
	motor1.setSpeed(left);
    motor2.setSpeed(right);
}

//Follow on White background
void followLineOnWhiteBG()
{
	if(isSteepLeftTurnOnWhiteBG())
	{
		turnLeftSteep();
	}
	else if(isSteepRightTurnOnWhiteBG())
	{
		turnRightSteep();
	}
	else if (isLeftTurnOnWhiteBG())
	{
		turnLeft();
	}
	else if (isRightTurnOnWhiteBG())
	{
		turnRight();
	}
	else if (isSlightLeftTurnOnWhiteBG())
	{
		turnLeftSlight();
	}
	else if (isSlightRightTurnOnWhiteBG())
	{
		turnRightSlight();
	}
	else if (isStrightOnWhiteBG())
	{
		goSlow();//goStright();
	}
	else
	{
		goSlow();
	}
}

//Follow on Black background
void followLineOnBlackBG()
{
	if(isSteepLeftTurnOnBlackBG())
	{
		turnLeftSteep();
	}
	else if(isSteepRightTurnOnBlackBG())
	{
		turnRightSteep();
	}
	else if (isLeftTurnOnBlackBG())
	{
		turnLeft();
	}
	else if (isRightTurnOnBlackBG())
	{
		turnRight();
	}
	else if (isSlightLeftTurnOnBlackBG())
	{
		turnLeftSlight();
	}
	else if (isSlightRightTurnOnBlackBG())
	{
		turnRightSlight();
	}
	else if (isStrightOnBlackBG()) 
	{
		goSlow();
	}
	else
	{
		goSlow();
	}
}

boolean isSteepLeftTurnOnWhiteBG()
{
	boolean steepTurn = false;
	
	if((!bgRightFlag) && (!rightFlag) && (leftFlag && bgLeftFlag))
	{
		steepTurn = true;
	}
	else if((!bgRightFlag) && (!rightFlag) && (!leftFlag) && bgLeftFlag)
	{
		steepTurn = true;
	}
	return steepTurn;
}

boolean isLeftTurnOnWhiteBG()
{
	return ((!bgRightFlag) && (rightFlag && leftFlag && bgLeftFlag));
}

boolean isSteepRightTurnOnWhiteBG()
{
	boolean steepTurn = false;
	if((!bgLeftFlag) && (!leftFlag) && (rightFlag && bgRightFlag))
	{
		steepTurn = true;
	}
	else if((!bgLeftFlag) && (!leftFlag) && (!rightFlag) && bgRightFlag)
	{
		steepTurn = true;
	}
	return steepTurn;
}

boolean isRightTurnOnWhiteBG()
{
	return ((!bgLeftFlag) && (rightFlag && leftFlag && bgRightFlag ));
}

boolean isSlightLeftTurnOnWhiteBG()
{
	return ((!bgLeftFlag) && (!leftFlag) && rightFlag && (!bgRightFlag));
}

boolean isSlightRightTurnOnWhiteBG()
{
	return ((!bgLeftFlag) && leftFlag && (!rightFlag) && (!bgRightFlag));
}

boolean isStrightOnWhiteBG()
{
	return (leftFlag && rightFlag);
}

boolean isSteepLeftTurnOnBlackBG()
{
	boolean steepTurn = false;
	if((bgRightFlag) && (rightFlag) && (!leftFlag && !bgLeftFlag))
	{
		steepTurn = true;
	}
	else if((bgRightFlag) && (rightFlag) && (leftFlag) && !bgLeftFlag)
	{
		steepTurn = true;
	}
	return steepTurn;
}

boolean isLeftTurnOnBlackBG()
{
	return ((bgRightFlag) && (!rightFlag && !leftFlag && !bgLeftFlag));
}
		
boolean isSteepRightTurnOnBlackBG()
{
	boolean steepTurn = false;
	if((bgLeftFlag) && (leftFlag) && (!rightFlag && !bgRightFlag))
	{
		steepTurn = true;
	}
	else if((bgLeftFlag) && (leftFlag) && (rightFlag) && !bgRightFlag)
	{
		steepTurn = true;
	}
	return steepTurn;
}

boolean isRightTurnOnBlackBG()
{
	return ((bgLeftFlag) && (!rightFlag && !leftFlag && !bgRightFlag ));
}

boolean isSlightLeftTurnOnBlackBG()
{
	return ((bgLeftFlag) && (leftFlag) && !rightFlag && (bgRightFlag));
}

boolean isSlightRightTurnOnBlackBG()
{
	return ((bgLeftFlag) && !leftFlag && (rightFlag) && (bgRightFlag));
}

boolean isStrightOnBlackBG()
{
	return (!leftFlag && !rightFlag);
}


boolean isMiddleLeftDetectorOnBlack(){

  int sensorValue = analogRead(ir_left);
  if (sensorValue > THRESHOLD){
    return true;    //return true for black
  } else{
    return false;
  }

}

boolean isMiddleRightDetectorOnBlack(){
	
  int sensorValue = analogRead(ir_right);
  
  if (sensorValue > THRESHOLD){
    return true;    //return true for black
  } else{
    return false;
  }

}


boolean isBackgroundLeftDetectorOnBlack(){

  int sensorValue = analogRead(bg_left);
  
  if (sensorValue > THRESHOLD){
    return true;    //return true for black
  } else{
    return false;
  }

}

boolean isBackgroundRightDetectorOnBlack(){
  int sensorValue = analogRead(bg_right);

  if (sensorValue > THRESHOLD){
    return true;    //return true for black
  } else{
    return false;
  }

}

void goStright(){

  Serial.println("go straight ");
  speedSet(MAX_SPEED,MAX_SPEED);
  motor1.run(FORWARD);     
  motor2.run(FORWARD); 
  delay(250);
}

void goSlow(){

  Serial.println("go slow ");
  speedSet(TURN_SPEED,TURN_SPEED);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);    
}

void turnLeft(){
  
  Serial.println("turn left ");
  speedSet(MIN_SPEED,TURN_SPEED);
  motor2.run(FORWARD);
  delay(250);
}

void turnRight(){
  
  Serial.println("turn right ");
  speedSet(TURN_SPEED,MIN_SPEED);
  motor1.run(FORWARD); 
    delay(250);
}

void turnLeftSlight(){
  
  Serial.println("turn left slight");
  speedSet(MIN_SPEED,TURN_SPEED);
  motor2.run(FORWARD);    
}

void turnRightSlight(){
  
  Serial.println("turn right slight");
  speedSet(TURN_SPEED,MIN_SPEED);
  motor1.run(FORWARD);  
}

void turnLeftSteep(){
  
  Serial.println("turn left steep");
  speedSet(MIN_SPEED,MAX_SPEED);
  motor2.run(FORWARD);   
  delay(500);
}

void turnRightSteep(){
  
  Serial.println("turn right steep");
  speedSet(MAX_SPEED,MIN_SPEED);
  motor1.run(FORWARD); 
  delay(500);
}

void reverse(){
  
  Serial.println("reverse "); 
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD); 
}

void halt(){
  
  Serial.println("STOP");
  motor1.run(RELEASE);     
  motor2.run(RELEASE);  
}
