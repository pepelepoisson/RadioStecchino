#pragma once

// Libraries required for communication with nrf24L01 radio
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

class Nrf24l01 {
  public:
    Nrf24l01(void);

    struct Accel {
      int16_t ax;
      int16_t ay;
      int16_t az;
      int16_t gx;
      int16_t gy;
      int16_t gz;
    };
    Accel accel;

    bool Setup(void);
    void getInput(void);
    void GetAccelMotion(int16_t * x_a, int16_t * y_a, int16_t * z_a);

  private:
    //NRF24L01 nrf24l01_;
};
