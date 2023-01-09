//******************INPUT: PUSH BUTTONS**********************//
#define startPB     //ALL SWITCHED ON

#define readyPB 25    //+ Blocker 2 open
#define potentiometer A0
#define cwPB A1
#define ccwPB A2
#define stopdirPB A3
#define blocker1PB 27

#define stopPB      //TOTAL SHUT DOWN

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

//STEPS
#define stepsPerRevolution 50   //90 degree

int read_ADC =0;
int duty_cycle;
int set = 0;

void setup() 
{
  //Declare pins as input
  pinMode(potentiometer, INPUT);
  pinMode(blocker1PB, INPUT_PULLUP);
  pinMode(readyPB, INPUT_PULLUP);
  pinMode(cwPB, INPUT_PULLUP);
  pinMode(ccwPB, INPUT_PULLUP);
  pinMode(stopdirPB, INPUT_PULLUP);

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
  
}

void loop() 
{
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
}
