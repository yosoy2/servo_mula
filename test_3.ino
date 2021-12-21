
// Define stepper motor connections:
#define dirPin 2
#define stepPin 3

#define stepsPerRevolution 1600

// Hall encoder left, motor B
volatile unsigned int temp_left, counter_left = 0;

void ai2() {
if(digitalRead(9)==LOW){
counter_left++;
}else{
counter_left--;
}
}

void ai3() {
if(digitalRead(8)==LOW){
counter_left--;
}else{
counter_left++;
}
}

void leftEncoder_read() {
  if( counter_left != temp_left ){
  SerialUSB.print ("counter_left: ");
  SerialUSB.println (counter_left);
  //digitalWrite(LED_BUILTIN, HIGH);
  temp_left = counter_left;
  }
  //digitalWrite(LED_BUILTIN, LOW);
}

void setup() {

      // Declarar la velocidad del puerto serial
  SerialUSB.begin(9600);

  // LEFT ENCODER
  // Declarar las resistencias internas de los pines 2 y 3
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
 // Interruptores
 attachInterrupt(8, ai2, RISING);
 attachInterrupt(9, ai3, RISING);
  
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  // Set the spinning direction CW/CCW:
  //digitalWrite(dirPin, HIGH);

}

void loop() {
  // Set the spinning direction clockwise:
    leftEncoder_read();
  delay(10);
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
      leftEncoder_read();
  delay(10);

  }
  delay(1000);
  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);
  // Spin the stepper motor 1 revolution quickly:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
      leftEncoder_read();
  delay(10);
  }
  delay(1000);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
      leftEncoder_read();
  delay(10);
  }
  delay(1000);
  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
      leftEncoder_read();
  delay(10);
  }
  delay(1000);
}
