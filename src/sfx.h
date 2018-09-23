#pragma once

//#include <Arduino.h>

// 3rd party (platformIO)
#include <ArduinoLog.h>
#include <FastLED.h>

// 3rd party (local)
#include <toneAC.h>

// Config
#define MAX_VOLUME  10

class Sfx {
  public:
    static void SFXstart(); //jet take off
    static void SFXrecord(); //random glitches
    static void SFXgameOver(); //game over
    static void SFXtone(); //just a tone
    static void SFXcomplete();

  private:
    static long startStartTime_;
    static long gameOverStartTime_;
};
