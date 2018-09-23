#include "nrf24l01.h"

#include <ArduinoLog.h>
// Libraries required for communication with nrf24L01 radio
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#include "configuration.h"

Nrf24l01::Nrf24l01(void){};

// Setup.
bool Nrf24l01::Setup(void) {
    Log.trace(F("Nrf24l01::Setup\n"));

// Setup Mirf communication using nrf24L01
    Mirf.spi = &MirfHardwareSpi;
    Mirf.csnPin = 48; //(This is optional to change the chip select pin)
    Mirf.cePin = 53; //(This is optional to change the enable pin)
    Mirf.init();
    Mirf.setTADDR((byte *)"serv1");
    Mirf.payload = sizeof(Accel);
    Mirf.channel = 56;
    Mirf.config();

    return true;
}

void Nrf24l01::getInput(void) {
    Log.trace(F("GetMotion\n"));
 if (!Mirf.isSending() && Mirf.dataReady()){
    Mirf.getData((byte *) &accel);  // Read data from the sender
    Serial.print(accel.ax, DEC);
    Serial.print(", ");
    Serial.print(accel.ay, DEC);
    Serial.print(", ");
    Serial.print(accel.az, DEC);
    Serial.print(", ");
    Serial.print(accel.gx, DEC);
    Serial.print(", ");
    Serial.print(accel.gy, DEC);
    Serial.print(", ");
    Serial.print(accel.gz, DEC);
    Serial.println();
    }
}
void Nrf24l01::GetAccelMotion(int16_t * x_a, int16_t * y_a, int16_t * z_a) {
    Log.trace(F("GetMotion\n"));
 if (!Mirf.isSending() && Mirf.dataReady()){
    Mirf.getData((byte *) &accel);  // Read data from the sender
    *x_a=accel.ax;
    *y_a=accel.ay;
    *z_a=accel.az;

    Serial.print(accel.ax, DEC);
    Serial.print(", ");
    Serial.print(accel.ay, DEC);
    Serial.print(", ");
    Serial.print(accel.az, DEC);
    Serial.print(", ");
    Serial.print(accel.gx, DEC);
    Serial.print(", ");
    Serial.print(accel.gy, DEC);
    Serial.print(", ");
    Serial.print(accel.gz, DEC);
    Serial.print(", ");
    Serial.print(millis());
    Serial.println();
  }
}
