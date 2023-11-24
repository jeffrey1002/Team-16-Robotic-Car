# Team 16 Robotic-Car

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
| Motor Control | GP10 - IN1 <br/> GP11 - IN2 <br/> GP3 - IN3 <br/> GP4 - IN4 |
| Motor PWM | GP9 - Left Motor <br/> GP8 - Right Motor |
| Speed Sensor | GP12 - Left <br/> GP7 - Right |
| Line Tracking Sensor | GP26 - Barcode <br/> GP27 - Line Right <br/> GP28 - Line Left |
| Ultrasonic Sensor | GP6 - Echo </br> GP5 - Trigger |
| Magnetometer | GP1 - SDA </br> GP0 - SLA |


##### Setting up environment 
There are various [methods](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) (see chapters 2 and 9) to setup the development environment for the pico in C using the Pico SDK, depending on what OS you are using on your PC/laptop. However, if you are using Windows OS, the easiest way is to download and install [this](https://github.com/raspberrypi/pico-setup-windows/releases/latest/download/pico-setup-windows-x64-standalone.exe) tool.

##### Flowchart
https://drive.google.com/file/d/1GpDOMLDx5xElrJfJiDJTu_KfLLIF3ubz/view?usp=sharing
![Robot_Car_Flowchart drawio](https://github.com/jeffrey1002/Team-16-Robotic-Car/assets/115239275/238cc755-a5c8-4a82-a0d7-a5bf6dba4140)

