#include <Wire.h>  // Library which contains functions to have I2C Communication

#define SLAVE_ADDRESS 0x40 // Define the I2C address to Communicate to Uno

//Pins not in use: 
int avaliableDigitalPins[8] = {0,1,2,4,5,6,7,10};
int avaliableAnaloguePins[2] = {2,3};

void setup() 
{
  Serial.begin(9600);
  Serial.println("Started");
  
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
void setMotorPower(int motorNumber, String command)
{
  int power = command.toInt();
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

void setPinModeCommand(int mode, String command)
{
  pinMode(command.toInt(), mode);
}

void setDigitalPinCommand(int mode, String command)
{
  digitalWrite(command.toInt(), mode);
}

void runCommand(int numBytes)
{
  Serial.println("Receive Message");
  String command = readCommand(numBytes);

  //The command string without the first character. Passed to the seperate functions to handle
  //Any required additional information for each commmand.
  String commandEnd = command.substring(1);
  switch (command[0])
  {
    case 'i':
      setPinModeCommand(INPUT, commandEnd);
      break;
    case 'o':
      setPinModeCommand(OUTPUT, commandEnd);
      break;
    case 'h':
      setDigitalPinCommand(HIGH, commandEnd);
      break;
    case 'l':
      setDigitalPinCommand(LOW, commandEnd);
      break;
    case 'a':
      setMotorPower(0, commandEnd);
      break;
    case 'b':
      setMotorPower(1, commandEnd);
      break;
  }
}

String readCommand(int numBytes)
{
  String message = "";
  for(int x = 0; x < numBytes; x++)
  {
    message += (char)Wire.read();
  }
  Serial.println(message);
  return message;
}
 
void loop() 
{
  delay(1000);
}

