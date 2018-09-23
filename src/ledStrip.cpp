#include "ledStrip.h"

#include <Arduino.h>
#include <ArduinoLog.h>
#include <FastLED.h>

#include "configuration.h"

LedStrip::LedStrip() : frame_count_(0), hue_(0), led_count_(NUM_LEDS) {}

// Setup LED strip.
void LedStrip::Setup(void) {

    FastLED.addLeds<WS2812B, PIN_LED_DATA, GRB>(leds_, static_cast<int>(led_count_));
    FastLED.setBrightness(LOW_BRIGHTNESS);
}

void LedStrip::Update(void) {
    Log.trace(F("LedStrip::Update\n"));

    // Slowly cycle the "base color" through the rainbow.
    EVERY_N_MILLISECONDS(20) { ++hue_; }

    FastLED.show();
}

void LedStrip::Off(void) {
    Log.trace(F("LedStrip::Off\n"));

    for (int i = 0; i < led_count_; ++i) {
        leds_[i] = CRGB::Black;

        // leds_[i].nscale8(230);
        delay(10);
        FastLED.show();
    }
}

void LedStrip::On(const int count, const int record) {
    Log.trace(F("LedStrip::On\n"));

    for (int i = 0; i < led_count_; ++i) {
        if (i <= led_count_ - count) {
            leds_[i] = CRGB::Black;
        } else {
            leds_[i] = CHSV(hue_, 255, 255);
        }

        if (i == led_count_ - record) {
            leds_[i] = CRGB::Red;
        }
    }
}

// Random colored speckles that blink in and fade smoothly.
void LedStrip::ConfettiPattern() {
    fadeToBlackBy(leds_, led_count_, 10);

    int pos = random16(led_count_);
    leds_[pos] += CHSV(hue_ + random8(64), 200, 255);
}

void LedStrip::bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int pos = 0; pos < NUM_LEDS; pos++) { //9948
    leds_[pos] = ColorFromPalette(palette, hue_+(pos*2), beat-hue_+(pos*10));
  }
}

// A colored dot sweeping back and forth, with fading trails.
void LedStrip::CylonPattern() {
    fadeToBlackBy(leds_, led_count_, 20);

    int pos = beatsin16(13, 0, led_count_);
    leds_[pos] += CHSV(hue_, 255, 192);
}

void LedStrip::ShowIdle() {
    Log.trace(F("LedStrip::ShowIdle\n"));

    //ConfettiPattern();
    bpm();
}

void LedStrip::ShowStartPlay() {
    Log.trace(F("LedStrip::ShowStartPlay()\n"));

    for (int i = 0; i < led_count_; ++i) {
        leds_[i] = CRGB::Green;
    }
}

void LedStrip::ShowWinner() {
    Log.trace(F("LedStrip::ShowWinner()\n"));

    frame_count_ += 1;

    if (frame_count_ % 4 == 1) {  // Slow down frame rate
        for (int i = 0; i < led_count_; ++i) {
            leds_[i] = CHSV(HUE_RED, 0, random8() < 60 ? random8() : random8(64));
        }
    }
}

void LedStrip::ShowGoingToSleep() {
    Log.trace(F("LedStrip::ShowGoingToSleep()\n"));

    for (int i = 0; i < led_count_; ++i) {
        leds_[i] = CRGB::Blue;
    }
}

void LedStrip::ShowPattern(const LedStrip::Pattern pattern) {
    Log.trace(F("LedStrip::ShowPattern\n"));

    switch (pattern) {
        case LedStrip::Pattern::kSpiritLevel: {
            Log.verbose(F("Pattern: SPIRIT_LEVEL\n"));

            CylonPattern();
        } break;

        case LedStrip::Pattern::kGameOver: {
            Log.verbose(F("Pattern: GAME_OVER\n"));

            for (int i = 0; i < led_count_; ++i) {
                leds_[i] = CRGB::Red;
            }
        } break;
    }

    FastLED.show();
    delay(1000 / FRAMES_PER_SECOND);
}
