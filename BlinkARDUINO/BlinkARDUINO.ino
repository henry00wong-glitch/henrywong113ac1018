/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

const int rLEDPin = 3;
const int gLEDPin = 4;
const int bLEDPin = 5;

void setup() {
  pinMode(rLEDPin, OUTPUT);
  pinMode(gLEDPin, OUTPUT);
  pinMode(bLEDPin, OUTPUT);
}

void loop() { 
  // red
  digitalWrite(rLEDPin, LOW);
  digitalWrite(gLEDPin, HIGH);
  digitalWrite(bLEDPin, LOW); 
  delay(1000);

  // turn off
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, HIGH);
  digitalWrite(bLEDPin, HIGH);
  delay(0);  

  // green
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, LOW);
  digitalWrite(bLEDPin, LOW); 
  delay(1000);

  // turn off
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, HIGH);
  digitalWrite(bLEDPin, HIGH);
  delay(0);

  // blue
  digitalWrite(rLEDPin, LOW);
  digitalWrite(gLEDPin, LOW);
  digitalWrite(bLEDPin, LOW); 
  delay(1000);

  // turn off
  digitalWrite(rLEDPin, HIGH);
  digitalWrite(gLEDPin, HIGH);
  digitalWrite(bLEDPin, HIGH);
  delay(0);
}
