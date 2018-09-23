// Code for sending device, in the balancing base

// Libraries required for MPU
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "RunningMedian.h"

// Libraries required for communication with nrf24L01 radio
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

// MPU
MPU6050 accelgyro;

struct Accel {
  int16_t ax;
  int16_t ay;
  int16_t az;
  int16_t gx;
  int16_t gy;
  int16_t gz;
};

Accel accel;

struct RunningMedians {
  RunningMedian ax = RunningMedian(5);
  RunningMedian ay = RunningMedian(5);
  RunningMedian az = RunningMedian(5);
  RunningMedian gx = RunningMedian(5);
  RunningMedian gy = RunningMedian(5);
  RunningMedian gz = RunningMedian(5);
};
RunningMedians runningMedians;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);

  // MPU
  Wire.begin();
  accelgyro.initialize();
  
  // Setup Mirf communication using nrf24L01
  Mirf.spi = &MirfHardwareSpi;
  Mirf.csnPin = 7; //(This is optional to change the chip select pin)
  Mirf.cePin = 8; //(This is optional to change the enable pin)
  Mirf.init();
  Mirf.setTADDR((byte *)"serv1");
  Mirf.payload = sizeof(Accel);
  Mirf.channel = 56;
  //Mirf.channel = 46;
  Mirf.config();
}

void loop() {
  //Serial.println("New loop");
  //delay(25);
  
  getInput();
  
  /*
  Serial.print(accel.ax, DEC);
  Serial.print(", ");
  Serial.print(accel.ay, DEC);
  Serial.print(", ");
  Serial.print(accel.az, DEC);
  Serial.print(", ");
  Serial.print(accel.gx, HEX);
  Serial.print(", ");
  Serial.print(accel.gy, HEX);
  Serial.print(", ");
  Serial.print(accel.gz, HEX);
  Serial.println();
  */

  // Send message using nrf24L01 and Mirf librairy
  if (!Mirf.isSending()) {
    Mirf.send((byte *) &accel);
  }
}


// ---------------------------------
// ----------- JOYSTICK ------------
// ---------------------------------
void getInput() {
  accelgyro.getMotion6(&accel.ax, &accel.ay, &accel.az, &accel.gx, &accel.gy, &accel.gz);

  runningMedians.ax.add(accel.ax);
  runningMedians.ay.add(accel.ay);
  runningMedians.az.add(accel.az);
  runningMedians.gx.add(accel.gx);
  runningMedians.gy.add(accel.gy);
  runningMedians.gz.add(accel.gz);

  accel.ax = runningMedians.ax.getMedian();
  accel.ay = runningMedians.ay.getMedian();
  accel.az = runningMedians.az.getMedian();
  accel.gx = runningMedians.gx.getMedian();
  accel.gy = runningMedians.gy.getMedian();
  accel.gz = runningMedians.gz.getMedian();
}

