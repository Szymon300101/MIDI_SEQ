#include <Arduino.h>

#include "MIDI.cpp"
#include "LED.cpp"


MIDI midi;
LED led;

bool led_on = false;
 
void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  midi.begin();
  led.begin();

  Serial.println("Start");

  delay( 200 );
  digitalWrite(5, HIGH);
  delay(1000);
  digitalWrite(5, LOW);
  
}

void loop()
{
  midi.read();

  led.set_playing(midi.notes, midi.notes_len);
  led.show();
  
}


