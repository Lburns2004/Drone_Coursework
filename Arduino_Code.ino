/* 
--------------------------------------------  
-------- MECH1010 Coursework 2023 --------
-------- Name: Louie Burns  --------
-------- Username:  mn22lb --------
--------------------------------------------
*/
//**** SETUP LIBRARY ************** LEAVE THESE LINES UNMODIFIED! ******************
#include <Servo.h> //Include the Servo library (for communication with motor controllers)
Servo motor_Left;   //Setup Left Motor
Servo motor_Right;  //Setup Right Motor
//*********************************************************************************

//Define Global Variables

int Greenpin = 2;
int Yellowpin = 3;
int Redpin = 4;
int PotReading = 0;
bool timeStored = false;
unsigned long horizontalTime = 0;
static unsigned long StartTime = 0;

void setup() {
	//Print message that system has started
  Serial.begin(9600);
  Serial.println("0.System Started");

	//Setup LED Pins
	pinMode(Greenpin, OUTPUT);  //Green LED
	pinMode(Yellowpin, OUTPUT);  //Yellow LED
	pinMode(Redpin, OUTPUT);  //Red LED

	//**** SETUP MOTORS ************** LEAVE THESE LINES UNMODIFIED! ******************
	motor_Left.attach(10); //Atttach the left motor controller
	motor_Right.attach(9);
	delay(300);
  //Initialise motors
	motor_Left.writeMicroseconds(1000); 
	motor_Right.writeMicroseconds(1000);
  delay(2000); //wait 2s to initialise the controller

	//Intialise Motors with 0 signal
	motor_Left.write(0);
	motor_Right.write(0);

	//Green LED Alert on for 1 second
	digitalWrite(Greenpin, HIGH);
	delay(1000);
	digitalWrite(Greenpin, LOW);

	//Message system initialised
	Serial.println("1. System Initiated");

  //*********************************************************************************
	//Message controller starting
	Serial.println("2.Controller Starting");

	//Print the Headings for the data
	Serial.println("Time,Angle,Error,Control Signal,Motor L, Motor R");

	//Record the initial start time
	StartTime = millis();
}

void loop() {
	//Find the current time & find elapsed time
  float ControllerTime = millis();
  float ElapsedTime = (ControllerTime - StartTime) / 1000.0;

	//Read the potentiometer
  PotReading = readPot();

	//Calculate the angle from the reading & store as error
  float angle = map(PotReading, 371, 729, 22.00, -22.00);
  float error = angle;

	//Find the percent that each motor must be used
	float Lpercent = map(angle, 22.00, -22.00, 0, 100);
  float Rpercent = map(angle, -22.00, 22.00, 0, 100);

	//Conver the percent into a motor signal
	float Lpower = map(Lpercent, 0, 100, 45,  59);
  float Rpower = map(Rpercent, 0, 100, 45, 54);


  angle = abs(angle);

	//Control the motors
	setMotorPosition(Lpower, Rpower);

	//Print the values 
  Serial.print(ElapsedTime, 2);
  Serial.print(", " );
  Serial.print(angle, 2);
  Serial.print(", " );
  Serial.print(error, 2);
  Serial.print(", " );
  Serial.print(PotReading, DEC);
  Serial.print(", " );
  Serial.print(Lpercent, 2);
  Serial.print(", " );
  Serial.println(Rpercent, 2);
	delay(40);

  //Store current time as Horizontal Time if not scanning
  if (!timeStored) {
    horizontalTime = millis();
  }

//Check to see if current angle is between -5 and 5 
  if (angle >= -5 && angle <= 5 && !timeStored) {
    horizontalTime = millis();
    digitalWrite(Yellowpin, HIGH);
    Serial.println("3. Scanning Started");
    timeStored = true;
  }

//Check to see if you have been scanning for more than 5s
  if ((ControllerTime - horizontalTime )> 5000) { 
    digitalWrite(Yellowpin, LOW);
    digitalWrite(Redpin, HIGH);
    Serial.println("4. Shutdown");
    motor_Left.write(45); 
    motor_Right.write(45); 
    delay(1000);
    digitalWrite(Redpin, LOW); 
    while(1);
  }
}

//Read the potentiometer
int readPot() {
  int potReading = analogRead(A0);
  return potReading;
}

//Set the motors to their desired power
void setMotorPosition(int left_pos, int right_pos) {
	motor_Left.write(left_pos); 
	motor_Right.write(right_pos); 
}
