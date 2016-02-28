/* Blink without Delay

 Turns on and off a light emitting diode (LED) connected to a digital
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.

 The circuit:
 * LED attached from pin 13 to ground.
 * Note: on most Arduinos, there is already an LED on the board
 that's attached to pin 13, so no hardware is needed for this example.

 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 modified 11 Nov 2013
 by Scott Fitzgerald


 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */
#include "printf.h"
#include "pitches.h"

//https://www.youtube.com/watch?v=-ajcYc8P3ZM
// notes in the melody:
int melody[] = {
  NOTE_G2, NOTE_G2, NOTE_G2, NOTE_DS2, NOTE_AS2, NOTE_G2, NOTE_DS2, NOTE_AS2, NOTE_G2, 0, //10 sec
  NOTE_D2, NOTE_D2, NOTE_D2, NOTE_DS2, NOTE_AS2, NOTE_FS2, NOTE_DS2, NOTE_AS2, NOTE_G2, 0, // 18 sec
  NOTE_G3, NOTE_G2, NOTE_G2, NOTE_G3, NOTE_FS3, NOTE_F3, NOTE_E3, NOTE_DS3, NOTE_E3, 0, // 25 sec
  NOTE_GS2, NOTE_CS2, NOTE_C2, NOTE_B2, NOTE_AS2, NOTE_A2, NOTE_AS2, 0, // 31 sec
  NOTE_DS2, NOTE_FS2, NOTE_DS2, NOTE_FS2, NOTE_AS2, NOTE_G2, NOTE_AS2, NOTE_D2, 0, // 35 sec
  NOTE_G3, NOTE_G2, NOTE_G2, NOTE_G3, NOTE_FS3, NOTE_F3, NOTE_E3, NOTE_DS3, NOTE_E3, 0, //43 sec
  NOTE_GS2, NOTE_CS2, NOTE_C2, NOTE_B2, NOTE_AS2, NOTE_A2, NOTE_AS2, 0, // 49 sec
  NOTE_DS2, NOTE_FS2, NOTE_DS2, NOTE_AS2, NOTE_G2, NOTE_DS2, NOTE_AS2, NOTE_G2 // 52 sec

};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2, 2, 2, 4, 4, 2, 4, 4, 2, 4,
  2, 2, 2, 4, 4, 2, 4, 4, 2, 4,
  2, 4, 4, 2, 2, 4, 4, 4, 2, 4,
  4, 2, 2, 4, 4, 4, 2, 4,
  4, 2, 2, 4, 2, 2, 4, 2, 4,
  2, 4, 4, 2, 2, 4, 4, 4, 2, 4,
  4, 2, 2, 4, 4, 4, 4, 4,
  4, 2, 2, 4, 2, 2, 4, 1
};

void playMusic() {
	 // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 73; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    noteDuration *= 1;
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
// constants won't change. Used here to set a pin number :
const int ledPin =  4;      // the number of the LED pin
const int motionSensorPin = 2;
const int motionLedPin = 3;

// Variables will change :
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

int previousMotion = 0;

// constants won't change :
const long interval = 500;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(motionSensorPin, INPUT);
  pinMode(motionLedPin, OUTPUT);
  Serial.begin(57600);
  printf_begin();
  printf("\n\rStarted/\n\r");
  	digitalWrite(motionLedPin, 1);

}

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
  int motion = digitalRead(motionSensorPin);
  if(motion != previousMotion){
  	printf("\n\rMotion Changed: %d\n\r", motion);
  	previousMotion = motion;
  	digitalWrite(motionLedPin, !motion);
  	if(motion){
  		playMusic();
  	}
  }
}

