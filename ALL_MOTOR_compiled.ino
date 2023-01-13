
//******************INPUT: PUSH BUTTONS**********************//
//#define DCMOTOR_ON 48     //DC MOTOR LAUNCHER ON
#define startPB 47 //Blocker 1 open
#define readyPB 48   //+ Blocker 2 open
#define cwPB A1
#define ccwPB A2
#define stopdirPB A3


//#define stopPB      //TOTAL SHUT DOWN

//*********************MOTORS**************************//

//DC MOTOR 1
#define DC1_In1 3
#define DC1_In2 2
#define DC1_EnA 14

//DC MOTOR 2
#define DC2_In1 1
#define DC2_In2 0
#define DC2_EnB 15


//DC MOTOR WORM 1
#define M1_EnA 13
#define M1_in1 12
#define M1_in2 11

//DC MOTOR WORM 2
#define M2_EnA 10
#define M2_in1 9
#define M2_in2 8

//STEPPER MOTOR 1
#define M1_dirPin 7 //CW+
#define M1_stepPin 6  //CLK+

//STEPPER MOTOR 2
#define M2_dirPin 5  //CW+
#define M2_stepPin 4 //CLK+

//*******************************************************//

//HC-06 BLUETOOTH
char incoming_value = 0;
#define LED_Pin 30

//ULTRASONIC SENSOR
#define trigPin 41
#define echoPin 42
#define buzzer 43
#define relay 44

// DEFINE VARIABLES
long duration;
int distance;
int safetyDistance;

//STEPS
#define stepsPerRevolution 50   //90 degree

int set = 0;

void setup() 
{
  //Declare pins as input
  pinMode(StartPB, INPUT_PULLUP);  //Blocker 1 open
  pinMode(readyPB, INPUT_PULLUP); //Blocker 2 open
  
  pinMode(cwPB, INPUT_PULLUP);  
  pinMode(ccwPB, INPUT_PULLUP);
  pinMode(stopdirPB, INPUT_PULLUP);

  pinMode(echoPin, INPUT); 

  //Declare pins as output

  pinMode(DC1_In1, OUTPUT);
  pinMode(DC1_In2, OUTPUT);
  pinMode(DC1_EnA, OUTPUT);

  pinMode(DC2_In1, OUTPUT);
  pinMode(DC2_In2, OUTPUT);
  pinMode(DC2_EnB, OUTPUT);
  
  pinMode(M1_EnA, OUTPUT);
  pinMode(M1_in1, OUTPUT);
  pinMode(M1_in2, OUTPUT);
  
  pinMode(M2_EnA, OUTPUT);
  pinMode(M2_in1, OUTPUT);
  pinMode(M2_in2, OUTPUT);

  pinMode(M1_dirPin, OUTPUT);
  pinMode(M1_stepPin, OUTPUT);
  pinMode(M2_dirPin, OUTPUT);
  pinMode(M2_stepPin, OUTPUT);

  pinMode(trigPin, OUTPUT); 
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);

  pinMode(LED_Pin, OUTPUT);

  Serial.begin(9600);
  //Serial.begin(38400);
}

void loop() 
{
  if(Serial.available())
  { 
    //ROTATION CONTROL MOTOR
    if(digitalRead (cwPB) == 0){set = 1;}
    if(digitalRead (stopdirPB) == 0){set = 0;}
    if(digitalRead (ccwPB) == 0){set = 2;}

    ////////////////DC MOTOR LAUNCHER HEREEEEEEEEEEEEEEE///////////////////////
    
    String Direction = Serial.readString();
    if(Direction == "UP") //MOTOR CONTROL CW
    {
      if(set==1)  //CW
      {
        digitalWrite(M1_in1, HIGH);  
        digitalWrite(M1_in2, LOW);
        digitalWrite(M2_in1, HIGH);  
        digitalWrite(M2_in2, LOW);
      }
      
    }
    
    if(Direction == "DOWN") //MOTOR CONTROL CCW
    {
      if(set==2)  //CCW
      { 
        digitalWrite(M1_in1, LOW);  
        digitalWrite(M1_in2, HIGH);
        digitalWrite(M2_in1, LOW);  
        digitalWrite(M2_in2, HIGH);
      }
    }
    if(Direction == "STOP") //MOTOR CONTROL CCW
    {
      if(set==0)  //STOP
      {
        digitalWrite(M1_in1, LOW);  
        digitalWrite(M1_in2, LOW);
        digitalWrite(M2_in1, LOW);  
        digitalWrite(M2_in2, LOW);
      }
    }

    if(Direction == "BALL IN") //STEPPER BLOCKER 1
    {
      if (digitalRead(blocker1PB) == LOW)
      {
        // Set the spinning direction clockwise:
        digitalWrite(M1_dirPin, HIGH);
        
        // Spin the stepper motor 1 revolution slowly:
        for (int i = 0; i < stepsPerRevolution; i++) 
        {
          // These four lines result in 1 step:
          digitalWrite(M1_stepPin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(M1_stepPin, LOW);
          delayMicroseconds(1000);
        }
    
        delay(1000);
    
        // Set the spinning direction counterclockwise:
        digitalWrite(M1_dirPin, LOW);
    
        // Spin the stepper motor 1 revolution quickly:
        for (int i = 0; i < stepsPerRevolution; i++) 
        {
          // These four lines result in 1 step:
          digitalWrite(M1_stepPin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(M1_stepPin, LOW);
          delayMicroseconds(1000);
        }
      }
    }
    if(Direction == "READY") //STEPPER BLOCKER 2 READY
    {
      if (digitalRead(readyPB) == LOW)
      {
        // Set the spinning direction clockwise:
        digitalWrite(M2_dirPin, HIGH);
        
        // Spin the stepper motor 1 revolution slowly:
        for (int i = 0; i < stepsPerRevolution; i++) 
        {
          // These four lines result in 1 step:
          digitalWrite(M2_stepPin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(M2_stepPin, LOW);
          delayMicroseconds(1000);
        }
    
        delay(1000);
    
        // Set the spinning direction counterclockwise:
        digitalWrite(M2_dirPin, LOW);
    
        // Spin the stepper motor 1 revolution quickly:
        for (int i = 0; i < stepsPerRevolution; i++) 
        {
          // These four lines result in 1 step:
          digitalWrite(M2_stepPin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(M2_stepPin, LOW);
          delayMicroseconds(1000);
        }
    
        delay(500);
      }
      
      delay(1000);
    }
  
  
  delay(50);

//****************************ULTRASONIC SENSOR******************//
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculating the distance
    distance= duration*0.034/2;
    
    safetyDistance = distance;
    
    if (safetyDistance <= 80)
    { //Enter the Distance 
      digitalWrite(buzzer, HIGH);
      digitalWrite(relay, HIGH);
    }
    else
    {
      digitalWrite(buzzer, LOW);
      digitalWrite(relay, LOW);
    }
    
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
  }

}
