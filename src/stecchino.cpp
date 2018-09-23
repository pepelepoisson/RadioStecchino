// Uncomment to compile out all logging code, will significantly reduce the code size,
// must come before the `ArduinoLog.h` include.
//#define DISABLE_LOGGING

// System
#include <Arduino.h>

// Third-party
#include <ArduinoLog.h>
#include <Wire.h>

// Local
#include "behavior.h"
#include "configuration.h"
#include "ledStrip.h"
#include "nrf24l01.h"
#include "position.h"
#include "stecchino.h"
#include "sfx.h"

Behavior *behavior;
LedStrip *led_strip;
Position *position;
Nrf24l01 *nrf24l01;

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        // Wait for the Serial port to be ready.
        delay(100);
    }

    Log.begin(LOG_LEVEL_WARNING, &Serial, true);
    Log.trace(F("setup(): start\n"));

    led_strip = new LedStrip();
    led_strip->Setup();

    nrf24l01 = new Nrf24l01();
    nrf24l01->Setup();

    position = new Position(nrf24l01);
    position->Setup();

    behavior = new Behavior(led_strip);
    behavior->Setup();

    Log.trace(F("setup(): end\n"));
}

Stecchino::State state;
Stecchino::State previous_state;

void loop() {
    //Log.trace(F("loop(): start\n"));

    position->Update();

    float                  angle_to_horizon = position->GetAngleToHorizon();
    //Serial.println(angle_to_horizon);
    Stecchino::AccelStatus accel_status     = position->GetAccelStatus();
    Stecchino::Orientation orientation      = position->GetOrientation();

    behavior->Update(angle_to_horizon, accel_status, orientation);

    led_strip->Update();


    //Log.trace(F("loop(): end\n"));
}
