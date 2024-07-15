// Outdoor Arena UV Light Controller using Seeeduino Nano and Grove DMX512 adapter

// HARDWARE:
// https://wiki.seeedstudio.com/Seeeduino-Nano/
// https://wiki.seeedstudio.com/Grove-DMX512/
// https://wiki.seeedstudio.com/Grove_Shield_for_Arduino_Nano/
// https://www.amazon.com/Waterproof-Professional-Activated-Uplights-Christmas/dp/B0CL9KQQWZ?th=1

// DEPENDENCIES:
// https://github.com/PaulStoffregen/DmxSimple

// Dan Smith
// jET
// Janelia
// HHMI 

// VERSION 20240612 dks

#include <DmxSimple.h>        // library for interfacing with DMX512 devices
#define TRIGGER_PIN 3         // pins 2 or 3 can be used for interrupts on Seeeduino Nano
volatile bool state = true;   // state of light - for activating every other frame

void setup() {
  pinMode(TRIGGER_PIN, INPUT_PULLUP);                                         // interrupt occuring on each high pulse from camera
  attachInterrupt(digitalPinToInterrupt(TRIGGER_PIN), trigger, RISING);       // every high pulse should occur during each new exposure 
  DmxSimple.usePin(A5);                                                       // pin when using Grove connector on Seeeduino Nano
  interrupts();                                                               // enable interrupts

  DmxSimple.write(1, 255);    // enables dimming mode
  DmxSimple.write(8, 255);    // enables strobe mode
  DmxSimple.write(9, 51);     // sets to color output function
  DmxSimple.write(10, 160);   // selects UV mode
}

void trigger() {
  
  if (state) {
    DmxSimple.write(9, 51);
    state = false;
  }

  else {
    DmxSimple.write(9, 0);
    state = true;
  }
}

void loop() {
}
