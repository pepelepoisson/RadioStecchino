#include "sfx.h"

long Sfx::startStartTime_ = millis();
long Sfx::gameOverStartTime_ = millis();

void Sfx::SFXrecord(){  //random glitches
    int freq = map(sin(millis()/2.0)*1000.0, -1000, 1000, 500, 600);
    if(random8(5)== 0){
      freq *= 3;
    }
    toneAC(freq, MAX_VOLUME);
}
void Sfx::SFXgameOver(){  //game over
    int freq = max(1000 - (millis() - Sfx::gameOverStartTime_), 10);
    freq += random8(200);
    int vol = max(10 - (millis()- Sfx::gameOverStartTime_) / 200, 0);
    toneAC(freq, MAX_VOLUME);
}
void Sfx::SFXtone(){ //just a tone
    toneAC(2000, MAX_VOLUME, 1000, true);
}
void Sfx::SFXstart () {  //jet take off
    int freq = (millis() - Sfx::startStartTime_)/1.0;
    freq += map(sin(millis()/20.0)*1000.0, -1000, 1000, 0, 20);
    int vol = max(10 - (millis()- Sfx::startStartTime_) / 100.0, 0);
    toneAC(freq, vol);
    Sfx::gameOverStartTime_ = millis();
}

void Sfx::SFXcomplete(){
    noToneAC();
    Sfx::startStartTime_ = millis();
    Sfx::gameOverStartTime_ = millis();
}
