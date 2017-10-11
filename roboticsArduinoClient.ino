#include <Wire.h>  // Library which contains functions to have I2C Communication

#define SLAVE_ADDRESS 0x40 // Define the I2C address to Communicate to Uno

//Pins not in use: 
int avaliableDigitalPins[8] = {0,1,2,4,5,6,7,10};
int avaliableAnaloguePins[2] = {2,3};

void setup() 
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS); // this will begin I2C Connection with 0x40 address
  Wire.onReceive(runCommand); // sendData is funtion called when Pi requests data

  pinMode(8,OUTPUT);       //Channel A Brake Pin Initialize
  pinMode(9,OUTPUT);       //Channel B Brake Pin Initialize 
  pinMode(12,OUTPUT);      //Channel A Direction Pin Initialize
  pinMode(13,OUTPUT);      //Channel B Direction Pin Initialize
  pinMode(3,OUTPUT);      //Channel A Power Pin Initialize
  pinMode(11,OUTPUT);      //Channel B Power Pin Initialize
  
  
}

//Negative for reverse. Value from 0-255 to indicate power.
void setMotorPower(int numBytes, int motorNumber)
{
  int power = readNumber(numBytes);
  if (motorNumber == 0) //Channel A
  {
    //Sets direction
    if (power < 0) digitalWrite(12, LOW);
    else digitalWrite(12, HIGH);
    
    analogWrite(3, abs(power));
  }
  else //Channel B
  {
    //Sets direction
    if (power < 0) digitalWrite(13, LOW);
    else digitalWrite(13, HIGH);
    
    analogWrite(11, abs(power));
  }
}

void setPinModeCommand(int numBytes, int mode)
{
  pinMode(readNumber(numBytes), mode);
}

void setDigitalPinCommand(int numBytes, int mode)
{
  digitalWrite(readNumber(numBytes), mode);
}


int readNumber(int numBytes)
{
  int pinNumber;
  for (int x = numBytes - 1; x >= 0; x--)
  {
    pinNumber += (Wire.read() - '0') * pow(10,x);

  }
  return pinNumber;
}

void runCommand(int numBytes)
{
  char commandType = Wire.read();
  switch (commandType)
  {
    case 'i':
      setPinModeCommand(numBytes - 1, INPUT);
      break;
    case 'o':
      setPinModeCommand(numBytes - 1, OUTPUT);
      break;
    case 'h':
      setDigitalPinCommand(numBytes - 1, HIGH);
      break;
    case 'l':
      setDigitalPinCommand(numBytes - 1, LOW);
      break;
    case 'a':
      setMotorPower(numBytes - 1, 0);
      break;
    case 'b':
      setMotorPower(numBytes - 1, 1);
      break;
  }
}

void loop() 
{
  delay(1000);
}

