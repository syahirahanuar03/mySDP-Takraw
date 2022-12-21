#include <Stepper.h>

//*********************************************************************************//
//**********************DC MOTOR - LAUNCHER****************************************//

int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
int enA = 5;
int enB = 4;


void setup() 
{
  // initialize the serial port:
  Serial.begin(9600);
  
  // Set the output pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

    
}

void loop() 
{
  ////////////////DC MOTOR LAUNCHER///////////////////////
  int potValue = analogRead(A0); //Read potentiometer value
  int pwmOutput = map(potValue, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
  analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
  analogWrite(enB, pwmOutput); // Send PWM signal to L298N Enable pin

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);    
}
