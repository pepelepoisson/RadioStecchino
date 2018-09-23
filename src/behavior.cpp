#include "behavior.h"

volatile bool Behavior::interrupted_ = false;

Behavior::Behavior(LedStrip * led_strip)
    : state_(Stecchino::State::kUnknown), led_strip_(led_strip) {}

void Behavior::Setup(void) {
    SetState(Stecchino::State::kIdle);
}

void Behavior::Update(const float                  angle_to_horizon,
                      const Stecchino::AccelStatus accel_status,
                      const Stecchino::Orientation orientation) {
    Log.trace(F("Behavior::Update\n"));

    switch (state_) {

        case Stecchino::State::kIdle: {
            Idle(accel_status, orientation);
            //Log.warning(F("Idle\n"));
        } break;

        case Stecchino::State::kStartPlayTransition: {
            //Log.warning(F("BeforeStartPlayTransition\n"));
            StartPlayTransition();
            //Log.warning(F("AfterStartPlayTransition\n"));
        } break;

        case Stecchino::State::kPlay: {
            Play(accel_status);
            //Log.warning(F("Play\n"));
        } break;

        case Stecchino::State::kGameOverTransition: {
            GameOverTransition();
            //Log.warning(F("GameOverTransition\n"));
        } break;

        default: {
            // If we don't know what to do, move to idle mode.
            Log.error(F("Unknown state [%d], defaulting to Idle\n"), static_cast<int>(state_));
            SetState(Stecchino::State::kIdle);
        } break;
    }
}

void Behavior::SetState(const Stecchino::State state) {
    previous_state_ = state_;
    state_          = state;
    start_time_     = millis();
}

bool Behavior::IsNewState(void) const {
    return (state_ == previous_state_);
}

void Behavior::Idle(const Stecchino::AccelStatus accel_status, const Stecchino::Orientation orientation) {
    Log.trace(F("Behavior::Idle\n"));

    if (accel_status == Stecchino::AccelStatus::kStraight) {
        SetState(Stecchino::State::kStartPlayTransition);
        return;
    }

    led_strip_->ShowIdle();
    Sfx::SFXcomplete();
}

void Behavior::StartPlayTransition(void) {
    Log.trace(F("Behavior::StartPlayTransition\n"));

    if (millis() - start_time_ > MAX_START_PLAY_TRANSITION_MS) {
        previous_record_time_ = record_time_;
        previousLedOn=0;

        SetState(Stecchino::State::kPlay);
        return;
    }

    led_strip_->ShowStartPlay();
    Sfx::SFXstart();
}

void Behavior::Play(const Stecchino::AccelStatus accel_status) {
    Log.trace(F("Behavior::Play\n"));

    unsigned long elapsed_time = millis() - start_time_;
    int ledsOn=0;
    int recordLed=0;
    if (elapsed_time<60000){
      ledsOn=static_cast<int>(ledsOnTiming[static_cast<int>(elapsed_time / 1000.0)]*(elapsed_time/1000000.0));
      recordLed=static_cast<int>(ledsOnTiming[static_cast<int>(record_time_ / 1000.0)]*(record_time_ / 1000000.0));
    } else {ledsOn=150; recordLed=150;}

    if (accel_status == Stecchino::AccelStatus::kFallen) {
        SetState(Stecchino::State::kGameOverTransition);
        return;
    }

    if (elapsed_time > record_time_) {
        record_time_ = elapsed_time;
    }

    if ((elapsed_time > previous_record_time_ && elapsed_time <= previous_record_time_ + 1000 && previous_record_time_ > 0)||(elapsed_time>=60000)) {
        led_strip_->ShowWinner();
        Sfx::SFXrecord();
    } else {
        if (ledsOn>previousRecordLed){previousRecordLed=ledsOn;}
        led_strip_->On(max(ledsOn,previousLedOn),max(previousRecordLed,recordLed));
        previousLedOn=ledsOn;
        previousRecordLed=recordLed;
        /*led_strip_->On(
          static_cast<int>(0.00000000000024626*(elapsed_time*elapsed_time*elapsed_time)-0.00000005924*(elapsed_time*elapsed_time)+0.00515*elapsed_time+0.347),
          static_cast<int>(0.00000000000024626*(record_time_*record_time_*record_time_)-0.00000005924*(record_time_*record_time_)+0.00515*record_time_+0.347));
*/
        Sfx::SFXcomplete();
    }
/*
    if (ledsOn>=NUM_LEDS) {
        led_strip_->ShowWinner();
    }
*/

}

void Behavior::GameOverTransition(void) {
    Log.trace(F("Behavior::GameOverTransition\n"));

    //Sfx::SFXcomplete();

    if (millis() - start_time_ > MAX_GAME_OVER_TRANSITION_MS) {
        SetState(Stecchino::State::kIdle);
        return;
    }

    led_strip_->ShowPattern(LedStrip::Pattern::kGameOver);
    Sfx::SFXgameOver();
}
