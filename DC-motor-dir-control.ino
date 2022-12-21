//*********************************************************************************//
//**********************DC MOTOR - DIRECTION CONTROL****************************************//

const int pb3 = A2; //CW
const int pb4 = A3; //CCW

//MOTOR1
int in1 = 11;
int in2 = 12;
int enA1 = 13;

//MOTOR2
int in3 = 8;
int in4 = 9;
int enA2 = 10;

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
  pinMode(enA1, OUTPUT);
  pinMode(enA2, OUTPUT);

  analogWrite(enA1, 100); // Send PWM signal to L298N Enable pin
  analogWrite(enA2, 100);
}

void loop() 
{
  ////////////////DC MOTOR LAUNCHER///////////////////////
  if (digitalRead(pb3) == HIGH)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
  }
  else if(digitalRead(pb4) == LOW)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
  }

  delay(500);
}
