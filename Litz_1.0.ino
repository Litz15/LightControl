
#include <SparkFunTSL2561.h>
#include <Wire.h>

SFE_TSL2561 light; // Create an SFE_TSL2561 object, here called "light":

// Global variables:

boolean gain;       // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;    // Integration ("shutter") time in milliseconds
double lux;         // Resulting lux value
boolean good;       // True if neither sensor is saturated
const int nivel1=4; //Nivel 1 
const int nivel2=5; //Nivel 2
const int nivel3=6; //Nivel 3
const int nivel4=7; //Nivel 4
const int nivel5=8; //Nivel 5

void setup()
{
  Serial.begin(9600); // Initialize the Serial port:
  pinMode(nivel1,OUTPUT); //Set output for Nivel 1
  pinMode(nivel2,OUTPUT); //Set output for Nivel 2
  pinMode(nivel3,OUTPUT); //Set output for Nivel 3
  pinMode(nivel4,OUTPUT); //Set output for Nivel 4
  pinMode(nivel5,OUTPUT); //Set output for Nivel 5
 
  light.begin();  // Initialize the SFE_TSL2561 library

  gain = 0;   // If gain = false (0), device is set to low gain (1X)
 
  unsigned char time = 2; // If time = 2, integration will be 402ms
 
  light.setTiming(gain,time,ms);
  
  light.setPowerUp(); // To start taking measurements, power up the sensor:

}

void loop()
{
 
  delay(500);
 
  // Retrieve the data from the device:

  unsigned int data0, data1;
  
  if (light.getData(data0,data1))
  {
    good = light.getLux(gain,ms,data0,data1,lux); // Perform lux calculation:
  }
  else
  {
    byte error = light.getError(); // getData() returned false because of an I2C error, inform the user.
    printError(error);
  }

  
    if(lux<300){
    digitalWrite(nivel1,HIGH);
    digitalWrite(nivel2,LOW);
    digitalWrite(nivel3,LOW);
    digitalWrite(nivel4,LOW);
    digitalWrite(nivel5,LOW);
    }
    if(lux>300&&lux<390){
    digitalWrite(nivel1,LOW);
    digitalWrite(nivel2,HIGH);
    digitalWrite(nivel3,LOW);
    digitalWrite(nivel4,LOW);
    digitalWrite(nivel5,LOW);
    }
    if(lux>390&&lux<480){
    digitalWrite(nivel1,LOW);
    digitalWrite(nivel2,LOW);
    digitalWrite(nivel3,HIGH);
    digitalWrite(nivel4,LOW);
    digitalWrite(nivel5,LOW);
    }
    if(lux>570&&lux<660){
    digitalWrite(nivel1,LOW);
    digitalWrite(nivel2,LOW);
    digitalWrite(nivel3,LOW);
    digitalWrite(nivel4,HIGH);
    digitalWrite(nivel5,LOW);
    }
    if(lux>660&&lux<750){
    digitalWrite(nivel1,LOW);
    digitalWrite(nivel2,LOW);
    digitalWrite(nivel3,LOW);
    digitalWrite(nivel4,LOW);
    digitalWrite(nivel5,HIGH);
    }
  if(lux>750){
    digitalWrite(nivel1,LOW);
    digitalWrite(nivel2,LOW);
    digitalWrite(nivel3,LOW);
    digitalWrite(nivel4,LOW);
    digitalWrite(nivel5,LOW);
    }
  
}








void printError(byte error)
  // If there's an I2C error, this function will
  // print out an explanation.
{
  Serial.print("I2C error: ");
  Serial.print(error,DEC);
  Serial.print(", ");
  
  switch(error)
  {
    case 0:
      Serial.println("success");
      break;
    case 1:
      Serial.println("data too long for transmit buffer");
      break;
    case 2:
      Serial.println("received NACK on address (disconnected?)");
      break;
    case 3:
      Serial.println("received NACK on data");
      break;
    case 4:
      Serial.println("other error");
      break;
    default:
      Serial.println("unknown error");
  }
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
