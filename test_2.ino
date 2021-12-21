// This sketch is written by  MBcreates (www.YouTube.com/MBcreates)
// this sketch is in the public domain and free to use in any way you see fit 


#define DIR   12     // DRV8825 DIR pin is connected to Arduino pin 12 
#define STEP  11     // DRV8825 STEP pin is connected to Arduino pin 11   

#define P1    14    // push button 1 is connected to Arduino pin A0
#define P2    15    // push button 2 is connected to Arduino pin A1
#define P3    16    // push button 3 is connected to Arduino pin A2
#define P4    17    // push button 4 is connected to Arduino pin A3
#define P5    18    // push button 5 is connected to Arduino pin A4
#define P6    19    // push button 6 is connected to Arduino pin A5

int DELAY = 1500;     // delay between steps in microsenconds             
int DISTANCE = 0 ;    // Counter for steps

boolean GO = false;  // stepper ON or OFF

int DEST = 0;       // variable to store selected DESTINATION
int SOURCE =0;      // variable to store current POSITION
int DIFF = 0;       // variable to store the diffrence between POSISTION and DESTINATION
int DIFFplus=0;     // variable to store a value to check what the shortest direction to DESTINATION is
int DIFFmin=0;      // variable to store a value to check what the shortest direction to DESTINATION is

void setup() {

 pinMode(DIR,OUTPUT);       // pin 12 is set to OUTPUT
 pinMode(STEP,OUTPUT);      // pin 11 is set to OUTPUT

 pinMode(P1,INPUT_PULLUP);  // Arduino pin A0 is set to INPUT_PULLUP
 pinMode(P2,INPUT_PULLUP);  // Arduino pin A1 is set to INPUT_PULLUP
 pinMode(P3,INPUT_PULLUP);  // Arduino pin A2 is set to INPUT_PULLUP
 pinMode(P4,INPUT_PULLUP);  // Arduino pin A3 is set to INPUT_PULLUP
 pinMode(P5,INPUT_PULLUP);  // Arduino pin A4 is set to INPUT_PULLUP
 pinMode(P6,INPUT_PULLUP);  // Arduino pin A5 is set to INPUT_PULLUP



}

void loop() {


/////////////////////////////// Selecting DESTINTATION by PUSH BUTTON  
/*
The test setup in the video uses a 1.8 degree stepper motor. The Stepper driver is set to full step. This makes for 200 steps for a full rotation.
Six diffrent posistion make for 33,333 steps between posistions. I used vife times 33 steps and one time 35 steps to avoid decimal values 

*/

if(!digitalRead(P1))      // when button 1 is pushed, DESTINATION is set to 0
  {
    DEST=0;
  }
if(!digitalRead(P2))      // when button 2 is pushed, DESTINATION is set to 33
  {
    DEST=33;
  }
if(!digitalRead(P3))      // when button 3 is pushed, DESTINATION is set to 66
  {
    DEST=66;
  }
if(!digitalRead(P4))      // when button 4 is pushed, DESTINATION is set to 99
  {
    DEST=99;
  }
if(!digitalRead(P5))      // when button 5 is pushed, DESTINATION is set to 132
  {
    DEST=132;
  }
if(!digitalRead(P6))      // when button 6 is pushed, DESTINATION is set to 165
  {
    DEST=165;
  }
 
 
DIFF=100-abs(abs(SOURCE-DEST)-100);           // the diffrence between SOURCE and DESTINATION is callculated in a way the value is always positive

//  the two calculations below check the fastest way around a circle
//   learn more here: https://stackoverflow.com/questions/7428718/algorithm-or-formula-for-the-shortest-direction-of-travel-between-two-degrees-on

DIFFplus=100-abs(abs((SOURCE+1)-DEST)-100);   // the diffrence between SOURCE+1 and DESTINATION is callculated in a way the value is always positive
DIFFmin=100-abs(abs((SOURCE-1)-DEST)-100);    // the diffrence between SOURCE-1 and DESTINATION is callculated in a way the value is always positive

         
                                                                    
if(DIFFplus>=DIFFmin)                 // rotaion dirrection is set 
{
  digitalWrite(DIR,LOW);
 }
   
else
  {
  digitalWrite(DIR,HIGH);
  }




  
if(DEST!=SOURCE){               // if there is a diffrence between DEST and SOURCE, GO is set to true
  GO=true;

  while (GO)                  // while there is a diffrence between DEST and SOURCE the motor steps
 {
  digitalWrite(STEP,HIGH);
  delayMicroseconds(DELAY);                      
  digitalWrite(STEP,LOW); 
  delayMicroseconds(DELAY);
  
    DISTANCE++;         // DISTANCE increases with 1 after every step



if (DISTANCE==DIFF)   // when the DISTANCE is equal to DIFF, the 
  {
  GO=false;           // GO is set to false
  SOURCE=DEST;        // SOURCE is set to DEST (now both values are the same)
  DISTANCE=0;         // the DISTANCE counter is reset to zero
  }
 }

}
}
