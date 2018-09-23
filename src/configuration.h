#pragma once

// Pins
#define PIN_LED_DATA 26

// Number of LEDs in the strip.
#define NUM_LEDS 150

// Number of LEDs to turn on every second when playing.
#define NUM_LEDS_PER_SECOND 3

// LED animation speed.
#define FRAMES_PER_SECOND 250

// LED high brightness level.
#define HIGH_BRIGHTNESS 50

// LED low brightness level.
#define LOW_BRIGHTNESS 10

// 0, 1 or 2 to set the angle of the joystick
#define ACCELEROMETER_ORIENTATION 2

// duration of animation when game starts
#define MAX_START_PLAY_TRANSITION_MS 1000

// duration of game over animation
#define MAX_GAME_OVER_TRANSITION_MS 1000
