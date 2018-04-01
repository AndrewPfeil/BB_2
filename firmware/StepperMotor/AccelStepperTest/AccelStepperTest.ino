
#include <Wire.h>
#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS; 


#include "PITimer.h"

const int LED = 13;
const double sPeriod = .1; 
double Time = 0;
double othertime = 0;
bool Flag = 0;

void callback();
int pos;
bool forward = true;
PITimer1.period(sPeriod);     // initialize timer1
PITimer1.start(callback);           // attaches callback() as a timer overflow interrupt

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *myStepper = AFMS.getStepper(200, 1);
Adafruit_DCMotor *myMotor = AFMS.getMotor(3);


// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep() 
{  
  myStepper->onestep(FORWARD, SINGLE);
}
void backwardstep() 
{  
  myStepper->onestep(BACKWARD, SINGLE);
}


// Now we'll wrap the 3 steppers in an AccelStepper object
AccelStepper stepper(forwardstep, backwardstep);

void setup()
{  
  AFMS.begin(); 
  Serial.begin(9600);
  delay(1000);
  PITimer1.period(sPeriod); // initialize timer1
  PITimer1.start(callback); // attaches callback() as a timer overflow interrupt
  stepper.setMaxSpeed(400);
  stepper.setSpeed(100);
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  myMotor->run(RELEASE);
  pos = 0;
  
}


void loop()
{
  while (Flag)
  {
    Flag = false;
    Serial.print("timerone: "); Serial.println(Time);
  }
}

void callback()
{
  digitalWrite(LED, digitalRead(13) ^ 1);
  Time = Time + sPeriod;
  Flag = true;
}



//
//void loop()
//{
//
//  pos = stepper.currentPosition();
//  Serial.println(pos);
//  if (pos < 100 && forward)
//  {
//    //myMotor->run(FORWARD);
//    stepper.setSpeed(50);
//    stepper.runSpeed();
//  }
//  else
//  {
//    //myMotor->run(BACKWARD);
//    stepper.setSpeed(-50);
//    forward = false;
//    stepper.runSpeed();
//    if (pos == 0)
//    {
//      forward = true;
//    }
// 
//    
//  }
//  stepper.run();
//}


