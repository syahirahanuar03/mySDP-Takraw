//*********************************************************************************//
//**********************DC MOTOR - DIRECTION CONTROL****************************************//


//MOTOR1
int IN1 = 7; // IN1 L298 ==> pin 7 
int IN2 = 8; // IN2 ==> Pin8
int ENA = 5; // Enable A ==> Pin9 PWM

//MOTOR2
int IN3 = 9; // IN1 L298 ==> pin 7 
int IN4 = 10; // IN2 ==> Pin8
int ENB = 6; // Enable A ==> Pin9 PWM

//PUSH BUTTON
int Pb1 = 11; // Push button 1 ==> Pin 11 
int Pb2 = 12; // Push button 2 ==> pin 12
int Pb3 = 13; // Push button 3 ==> pin 13 (STOP) (imaginary) 

void setup() 
{
  //MOTOR 1
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  //MOTOR 1
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Set the INPUT pins
  pinMode(Pb1, INPUT_PULLUP);  // Default = HIGH  
  pinMode(Pb2, INPUT_PULLUP);
  pinMode(Pb3, INPUT_PULLUP);	//Default = LOW
  
  analogWrite(ENA, 0); 
  analogWrite(ENB, 0);
}

void loop() 
{
   while ((digitalRead(Pb1) == HIGH) && (digitalRead(Pb2) == HIGH) && (digitalRead(Pb3) == LOW))
  {
    MotorSpeed = 0;
  }
  
  boolean Pb1P = digitalRead(Pb1); // PB1P = Push button 1 Pressed
  boolean Pb2P = digitalRead(Pb2);
  boolean Pb3P = digitalRead(Pb3); 
  
  ////////////////DC MOTOR LAUNCHER///////////////////////
 if( Pb1P == LOW)
 {
   // Forward 
   digitalWrite(IN1, HIGH);
   digitalWrite(IN2, LOW);
   digitalWrite(IN3, HIGH);
   digitalWrite(IN4, LOW);
   
   if( MotorSpeed < 200)
   
   {
     MotorSpeed +=5;
     analogWrite(ENA,MotorSpeed);
     analogWrite(ENB,MotorSpeed);
     delay(100);
   }
   else 
   
   {
     MotorSpeed = 100;
     analogWrite(ENA, MotorSpeed);
     analogWrite(ENB, MotorSpeed);
   }
 }
 
 
 else if( Pb2P == LOW)
 {
    // Reverse 
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, HIGH);
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, HIGH);   
   
   if( MotorSpeed < 200)
   
   {
     MotorSpeed +=5;
     analogWrite(ENA,MotorSpeed);
     analogWrite(ENB,MotorSpeed);
     delay(100);
   }
   else 
   {
     MotorSpeed = 100;
     analogWrite(ENA, MotorSpeed);
     analogWrite(ENB, MotorSpeed);
   }
 }
 
 else if( Pb3P == HIGH)
 {
 
   MotorSpeed = 0;
   analogWrite(ENA, MotorSpeed);
   analogWrite(ENB, MotorSpeed);
   
 }

}
}
