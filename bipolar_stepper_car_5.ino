

int stepPin = 5; //bluek
int dirPin = 6; //green
int M0Pin = 7;
int M1Pin = 12;
int stepDelay = 1400; //1000
int stepDelay2 = 1000; //1000

// variables from original program
int stepsPerCycle=1; //30

int StepNumber=0;
int ReverseSteps;
int StepsTierTwo; // needs value

// int Distance=0.2; // distance input (m)
int RevsPerMetre; //needs value (experimental)
// int StepsTierTwo=RevsPerMetre*Distance*StepsPerRev;
int StepsPerMetre=7615;
int StepsTierTwoTest=StepsPerMetre*0.5;
// END variables from original program

//Switch
int switchPin=3;
int SwitchState=1;
int ReverseDirection=0; // breakout condition

//Button
int buttonPin=2;
int ButtonState=1; // off
int RunProgram=0;



int LEDPinRed = 9;
int LEDPinGreen = 10;

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(M0Pin,OUTPUT);
  pinMode(M1Pin,OUTPUT);
  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  pinMode(LEDPinRed, OUTPUT);
  pinMode(LEDPinGreen, OUTPUT);
  
  // M0Pin,LOW & M1Pin,LOW  =  Full step
  // HIGH LOW  =  Half Step
  // LOW HIGH  =  Quarter Step
  // HIGH HIGH = Eighth Step
  digitalWrite(M0Pin, HIGH);
  digitalWrite(M1Pin, HIGH);
  Serial.begin(9600);
}


void loop() {


  



  while (ButtonState==1) {
    Serial.println("Button has not been pressed");
      ButtonState=digitalRead(buttonPin); // has to be within while loop since the program is stuck within the while loop and cannot read this outside of the loop, hence why this statement was written once then never again
    digitalWrite(LEDPinRed, HIGH);
  digitalWrite(LEDPinGreen, LOW);
  }
  digitalWrite(LEDPinRed, LOW);
  digitalWrite(LEDPinGreen, HIGH);
    delay(1500); //startup delay of 5 seconds
    //Serial.println(ReverseDirection);


    while (ReverseDirection==0) {
      //Serial.print("Switch has not been pressed yet. Steps taken: ");
      
      // increment step number by 1
      //Serial.println(StepNumber);
      // *********** MOTOR********
        digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
        for(int x = 0; x < stepsPerCycle; x++) {
          digitalWrite(stepPin,HIGH); 
          delayMicroseconds(stepDelay); // speed of motor
          //SwitchState = digitalRead(switchPin);
 /*         if (SwitchState == 0){ // switch has been pressed
        ReverseDirection=1; // Causes the program to break out of the while loop's iron grip
        delay(10);
      }*/
          digitalWrite(stepPin,LOW); 
          delayMicroseconds(stepDelay);
          StepNumber++; 
          SwitchState = digitalRead(switchPin);
          if (SwitchState == 0){ // switch has been pressed
        ReverseDirection=1; // Causes the program to break out of the while loop's iron grip
        delay(100);
      }
        
        
        
        }
      // ************MOTOR********
 /*     if (SwitchState == 0){ // switch has been pressed
        ReverseDirection=1; // Causes the program to break out of the while loop's iron grip
        delay(3000);
      }*/
    } // end of while loop that causes motor to go forward

    
    int RemainingSteps=StepNumber;
    //Serial.println("Switch has been pressed");
    while (RemainingSteps>=1 && ReverseDirection==1){
      //Serial.print("Remaining steps are ");
     // Serial.println(RemainingSteps);
      RemainingSteps=RemainingSteps-1;
      // ******MOTOR********
        digitalWrite(dirPin,HIGH); //Changes the rotations direction
        // Makes 400 pulses for making two full cycle rotation
        for(int x = 0; x < stepsPerCycle; x++) {
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(stepDelay2);
          digitalWrite(stepPin,LOW);
          delayMicroseconds(stepDelay2);
        }
      //******MOTOR*****

      }
      delay(7000); //delay for 7 secoonds before starting tier two
      
      //***** Second phase******
      for (int im = StepsTierTwoTest; im > 0; im--){
        digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
        // Makes 200 pulses for making one full cycle rotation
        for(int x = 0; x < stepsPerCycle; x++) {
          digitalWrite(stepPin,HIGH); 
          delayMicroseconds(800); // speed of motor
          digitalWrite(stepPin,LOW); 
          delayMicroseconds(800); 
        } 
      //***** Second phase******
      }
      ButtonState=1;
      ReverseDirection=0; // remove this line this if there is an error
      StepNumber=0;
  

}
