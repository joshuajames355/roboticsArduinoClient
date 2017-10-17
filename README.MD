# Overview

This is a program that runs on an arduino uno and listens to serial commands sent over i2c. 
This was meant to be used with https://github.com/laserbeam897/roboticsPiLibrary.
It currently can set the power and mode of digital pins , send the power of all pins 
(0/1 for digital pins , 0-255 for analog pins) , and set the power/direction for the motor shield.

# Communicaton Protocol Details

## Command formats:
* [] indicates a variable. 
* i [pinNumber] //setmode of a digital pin to input
* o [pinNumber] //setmode of a digital pin to output
* h [pinNumber] //set a digit pin to high
* l [pinNumber] //set a digit pin to low
* a [power] //sets the power of the motor on channel A
* b [power] //sets the power of the motor on channel B
* p [pinNumber] - [power] //sets the power of the pwm pin
	
## Requesting pin power 
	
When sending a request, the command bit represents the pin number 
, where analog pins aremapped as 100 + the pin number.

# Pins in use:
## Pins in use by motor shield (channelA then channelB)
* Direction - D12 D13
* PWM - D3  D11
* Brake - D9  D8
* Current Sensing - A0  A1 

## Pins in use for i2c
* SDA - A4
* SCL - A5

# Connecting to the raspberry pi.

## Connect the pi to the arduino by connecting:
* pin 3 on the raspberry pi to an SDA pin (A4) on the arduino
* pin 5 on the raspberry pi to an SDL pin (A5) on the arduino
* pin 6 on the raspberry pi to a ground pin on the arduino

## The pins on the raspberry pi are numbered as follows:

![Raspberry PI pin diagram](https://user-images.githubusercontent.com/5314742/31580000-4c86b236-b13b-11e7-96f4-07cf46751c7b.png)

