RadioStecchino is a fork of the Stecchino balance game intended for Ottawa maker faire 2018. Rather than being self contained into one object, the game is split between a Stecchino stick controlling a long led strip on top of the booth to increase visibility and add sound effects and telemetry. The Stecchino includes an accelerometer, an Arduino MCU and an nrf24l01 radio transmitter. The data is received by a base station (Arduino Mega) which displays game on a long led strip, plays sound effects and outputs accelerometer data to a telemetry viewer.
This project is built from:
- My previous Stecchino https://github.com/pepelepoisson/Stecchino
- A fork by jason peacock who greatly improved the original Stecchino code to bring it from a beginer-like C version to a more elegant C++ remake https://github.com/jasonpeacock/Stecchino
- My previous Balancuino game https://github.com/pepelepoisson/balancuino which was based heavily on Twang (including sound effect reused in this radioStecchino project) https://github.com/Critters/TWANG
More details, photos and videos will be published soon at http://www.chezpapietmamie.com/pcube/
***
This repo contains:
- Arduino nano sketch running on the sender Stecchino (Arduino IDE)
- Arduino Mega sketch running on the base (platformIO IDE)

***
![Inventor Dads logo](Logo_Papas_Inventeurs_25mm.png)
***

