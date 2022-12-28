//*********************************************************************************//
//**********************DC MOTOR - DIRECTION CONTROL****************************************//

const int pb3 = A2; //CW
const int pb4 = A3; //CCW

//MOTOR1
int in1 = 8;
int in2 = 9;
int in3 = 10;
int in4 = 11;
int enA = 12;
int enB = 13;

void setup() 
{
  // initialize the serial port:
  Serial.begin(9600);

  pinMode(pb3, INPUT);
  pinMode(pb4, INPUT);
  
  // Set the output pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop() 
{
  analogWrite(enA, 50); // Send PWM signal to L298N Enable pin
  
  ////////////////DC MOTOR LAUNCHER///////////////////////
  if (digitalRead(pb3) == HIGH)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(digitalRead(pb4) == HIGH)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  delay(500);
}
