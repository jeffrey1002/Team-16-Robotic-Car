# Robotic-Car

##### Hardware
* Raspberry Pico
* 1x L298N Motor Driver
* 2x DC Motor
* 2x Speed Sensor / Encoder
* 3x Line Tracking Sensor (Infrared Sensor)
* 1x Ultrasonic Sensor
* 1x Breadboard
* 4x AA Batteries

##### Pin Layout
| Hardware | GPIO # |
|---|---|
| Motor Control | ? - IN1 <br/> ? - IN2 <br/> ? - IN3 <br/> ? - IN4|
| Motor PWM | ? - Left Motor <br/> ? - Right Motor |
| Speed Sensor | ? - Digital IN |
| Line Tracking Sensor | ? - Digital IN |
| Ultrasonic Sensor | ? - Digital IN |


##### Setting up environment 
There are various [methods](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) (see chapters 2 and 9) to setup the development environment for the pico in C using the Pico SDK, depending on what OS you are using on your PC/laptop. However, if you are using Windows OS, the easiest way is to download and install [this](https://github.com/raspberrypi/pico-setup-windows/releases/latest/download/pico-setup-windows-x64-standalone.exe) tool.
