//******************INPUT: PUSH BUTTONS**********************//
//#define startPB     //ALL SWITCHED ON

#define readyPB 25    //+ Blocker 2 open
#define potentiometer A0
#define cwPB A1
#define ccwPB A2
#define stopdirPB A3
#define blocker1PB 27

//#define stopPB      //TOTAL SHUT DOWN

//*********************MOTORS**************************//
//DC MOTOR 1
#define M1_EnA 13
#define M1_in1 12
#define M1_in2 11

//DC MOTOR 2
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

int read_ADC =0;
int duty_cycle;
int set = 0;

int state = 0;

void setup() 
{
  //Declare pins as input
  pinMode(potentiometer, INPUT);
  pinMode(blocker1PB, INPUT_PULLUP);
  pinMode(readyPB, INPUT_PULLUP);
  pinMode(cwPB, INPUT_PULLUP);  
  pinMode(ccwPB, INPUT_PULLUP);
  pinMode(stopdirPB, INPUT_PULLUP);

  pinMode(echoPin, INPUT); 

  //Declare pins as output
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

  Serial.begin(9600);

  Serial.begin(38400);
  
}

void loop() 
{
  //***********************MOTORS*************************//
  
  read_ADC = analogRead(potentiometer);
  duty_cycle = map(read_ADC, 0, 1023, 0, 100);

  analogWrite(M1_EnA, duty_cycle);
  analogWrite(M2_EnA, duty_cycle);

  if(digitalRead (cwPB) == 0){set = 1;}
  if(digitalRead (stopdirPB) == 0){set = 0;}
  if(digitalRead (ccwPB) == 0){set = 2;}

  if(set==0)
  {
    digitalWrite(M1_in1, LOW);  
    digitalWrite(M1_in2, LOW);
    digitalWrite(M2_in1, LOW);  
    digitalWrite(M2_in2, LOW);
  }
  
  if(set==1)
  {
    digitalWrite(M1_in1, HIGH);  
    digitalWrite(M1_in2, LOW);
    digitalWrite(M2_in1, HIGH);  
    digitalWrite(M2_in2, LOW);
  }
  
  if(set==2)
  { 
    digitalWrite(M1_in1, LOW);  
    digitalWrite(M1_in2, HIGH);
    digitalWrite(M2_in1, LOW);  
    digitalWrite(M2_in2, HIGH);
  }
  
  delay(50);

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

  else if (digitalRead(readyPB) == LOW)
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

    delay(2000);

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
  
  if (safetyDistance <= 80){ //Enter the Distance 
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
  }
  else{
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);
  }
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

//**********************BLUETOOTH********************//

  if(Serial.available() > 0) // Checks whether data is comming from the serial port
  { 
    state = Serial.read(); // Reads the data from the serial port
  }
  
  if (state == '0') 
  {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
  }
  
  else if (state == '1') 
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED: ON");;
    state = 0;
  }
//*********************************************************//
}
