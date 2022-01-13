/*******************************************************************
  SoftServo sketch for Adafruit Trinket.  Turn the potentiometer knob
  to set the corresponding position on the servo 
  (0 = zero degrees, full = 180 degrees)
 
  Required library is the Adafruit_SoftServo library
  available at https://github.com/adafruit/Adafruit_SoftServo
  The standard Arduino IDE servo library will not work with 8 bit
  AVR microcontrollers like Trinket and Gemma due to differences
  in available timer hardware and programming. We simply refresh
  by piggy-backing on the timer0 millis() counter
 
  Required hardware includes an Adafruit Trinket microcontroller
  a servo motor or two, and a potentiometer (nominally 1Kohm to 100Kohm
 
  As written, this is specifically for the Trinket although it should
  be Gemma or other boards (Arduino Uno, etc.) with proper pin mappings
 
  Trinket:        USB+   Gnd   Pin #0  Pin #1  Pin #2 A1
  Connection:     Servo+  -   Servo1 Servo2   Potentiometer wiper
 
 *******************************************************************/
#include <Servo.h>

Servo myservo;
uint32_t next;
int pos = 0;
const int servoPin = 6;

const int buttonPin = 2;

const int openled = 4;

// variables will change:
int buttonState = 0;
bool state = false;
   
void setup() {
  Serial.begin(9600);
//  TIMSK0=0;
  myservo.attach(servoPin);
//  myservo.write(90);
  delay(50000);                    // Wait 15ms for the servo to reach the position
//  next = millis() + 500;
  
  // initialize the LED pin as an output:
  pinMode(openled, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);


}

void loop()  {
  Serial.println(buttonState == HIGH);
  if (buttonState == HIGH && state == false) {
    Serial.println("set state to true");
    state = true;
    delay(200);
  } else if (buttonState == LOW && state == true) {
    Serial.println("set state to false");
    state = false;
    delay(200);
  }

  if (state == true) {
//    buttonState = digitalRead(buttonPin);
    Serial.println("on");
    // turn open LED on and closed LED off:
    digitalWrite(openled, HIGH);
    myservo.write(180); // tell servo to go to position
    Serial.println(myservo.read());
    delay(200);
  } else {
    // turn open LED off and closed LED on
    digitalWrite(openled, LOW);    
    myservo.write(0);
    Serial.println("off");
    delay(200); 
  }
}

// We'll take advantage of the built in millis() timer that goes off
// to keep track of time, and refresh the servo every 20 milliseconds
//volatile uint8_t counter = 0;
//SIGNAL(TIMER0_COMPA_vect) {
//  // this gets called every 2 milliseconds
//  counter += 2;
//  // every 20 milliseconds, refresh the servos!
//  if (counter >= 20) {
//    counter = 0;
//    myservo.refresh();
//  }
//}
