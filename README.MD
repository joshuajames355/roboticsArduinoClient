Command formats:
	[] indicates a variable. 
	i [pinNumber] //setmode of a digital pin to input
	o [pinNumber] //setmode of a digital pin to output
	h [pinNumber] //set a digit pin to high
	l [pinNumber] //set a digit pin to low
	a [power] //sets the power of the motor on channel A
	b [power] //sets the power of the motor on channel B

Pins in use:
	Pins in use by motor shield (channelA then channelB)
	Direction - D12 D13
	PWM - D3  D11
	Brake - D9  D8
	Current Sensing - A0  A1 

	Pins in use for i2c
	SDA - A4
	SCL - A5