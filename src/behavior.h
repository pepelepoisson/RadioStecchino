#pragma once

#include "ledStrip.h"
#include "sfx.h"
#include "stecchino.h"
#include <ArduinoLog.h>
#include "configuration.h"

class Behavior {
  public:
    Behavior(LedStrip * led_strip);

    // The array below is used to set the number of LEDs turned on during each second of the game. It starts at 5000 (5 LEDs per second) and ends
    // at about 1 per second at the end of the 150 LEDs strip. It takes 60 seconds to fill the 150 LEDs strip entirely.
    int ledsOnTiming[60]={5000,5000,5000,5000,5000,5000,4857,4750,4667,4600,4545,4500,4462,4429,4400,4313,4235,4167,4105,4050,4000,3955,3913,3875,3840,3808,
      3778,3714,3655,3600,3548,3500,3455,3412,3371,3333,3297,3263,3231,3200,3171,3143,3093,3045,3000,2957,2915,2875,2837,2800,2765,2731,2698,2667,2636,2607,
      2579,2552,2525,2500};
    int previousLedOn=0;
    int previousRecordLed=0;

    void Setup(void);

    void Update(const float                  angle_to_horizon,
                const Stecchino::AccelStatus accel_status,
                const Stecchino::Orientation orientation);

    Stecchino::State GetState() const { return state_; };

  private:
    Stecchino::State previous_state_;
    Stecchino::State state_;

    volatile static bool interrupted_;

    LedStrip *led_strip_;

    // Track when the current state was entered so we can tell when it's time to
    // expire the state and transition to a new state.
    unsigned long start_time_ = 0;

    unsigned long record_time_          = 0;
    unsigned long previous_record_time_ = 0;
    bool          ready_for_change_     = false;

    void SetState(const Stecchino::State state);

    bool IsNewState(void) const;

    void Idle(const Stecchino::AccelStatus accel_status, const Stecchino::Orientation orientation);

    void StartPlayTransition(void);

    void Play(const Stecchino::AccelStatus accel_status);

    void GameOverTransition(void);
};
