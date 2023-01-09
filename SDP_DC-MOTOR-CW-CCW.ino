
#define potentiometer  A0  //10k Variable Resistor
#define pb_CW A1 // Clockwise Button
#define pb_St A2 // Stop Button
#define pb_CCW A3 // Anticlockwise Button

#define M1_Ena 11 // Enable1 L298 for PWM
#define M1_in1 10 // In1  L298 for Clockwise
#define M1_in2 9  // In2  L298 for Anticlockwise

#define M2_Ena 6 // Enable1 L298 for PWM
#define M2_in1 8 // In1  L298 for Clockwise
#define M2_in2 7 // In2  L298 for Anticlockwise

int read_ADC =0;
int duty_cycle;
int set = 0;

void setup(){
Serial.begin(9600);// initialize serial communication at 9600 bits per second:

pinMode(potentiometer, INPUT);

pinMode(pb_CW, INPUT_PULLUP);
pinMode(pb_St, INPUT_PULLUP);
pinMode(pb_CCW, INPUT_PULLUP);

pinMode(M1_Ena, OUTPUT);
pinMode(M1_in1, OUTPUT);
pinMode(M1_in2, OUTPUT);

pinMode(M2_Ena, OUTPUT);
pinMode(M2_in1, OUTPUT);
pinMode(M2_in2, OUTPUT);

}

void loop(){ 
read_ADC = analogRead(potentiometer);
duty_cycle = map(read_ADC, 0, 1023, 0, 100);  
//duty_cycle_lcd = map(read_ADC, 0, 1023, 0, 100); 

analogWrite(M1_Ena, duty_cycle);
analogWrite(M2_Ena, duty_cycle);

if(digitalRead (pb_CW) == 0){set = 1;}
if(digitalRead (pb_St) == 0){set = 0;}
if(digitalRead (pb_CCW) == 0){set = 2;}

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
}
