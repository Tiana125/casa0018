/*
  Accelerometer_DataCollection.ino

  This code reads data from the Arduino Nano 33 BLE Sense's built-in 
  accelerometer and outputs it to Arduino's serial monitor. It cycles 
  through reading and displaying data for slightly less than 3 seconds,
  and delaying for exactly three seconds. It begins each new cycle of
  readings with spacing and the following characters "-,-,-" to 
  distinguish between the data points. This is the same format that
  the training code takes the data, so the output of the serial monitor
  can be copied directly into plaintext files to be read into the code 
  that trains the model.

  Much of this code, including the general stucture was taken from the 
  following source: 
  Nano33BLESensorExample_accelerometer.ino
  Copyright (c) 2020 Dale Giancono. All rights reserved..

  Other portions of this code were taken from Daniel Hertz from the 
  following article:
  https://maker.pro/arduino/tutorial/how-to-use-the-arduino-nano-33-bles
  -built-in-imu
*/

/*Include Header Files*/
#include "Arduino.h"
#include "Nano33BLEAccelerometer.h"
#include <Arduino_LSM9DS1.h>


/*Global Variables*/
//a counter to limit the number of cycles where values are displayed
int counter = 0; 


/*Setup Function*/
void setup()
{
    // Serial monitor setup
    Serial.begin(115200);
    while(!Serial);

    // Accelerometer setup
    Accelerometer.begin();
    Serial.println("-,-,-");    
}


/*Main loop*/
void loop()
{          
  // Initialize Variables
  float x, y, z = 0.05;

  // Check if the accelerometer is ready and if the loop has only
  //   been run less than 200 times (=~3 seconds displayed) 
  if (IMU.accelerationAvailable() and counter < 200)
  {
    // Read the accelerometer
    IMU.readAcceleration(x, y, z);
    // Scale up the values to better distinguish movements
    x = (int) (x*100);
    y = (int) (y*100);
    z = (int) (z*100);

    // Print the values to the Serial Monitor
    Serial.printf("%.1f,%.1f,%.1f\r\n", x, y, z);
    
  // When the loop has run 200 times, reset the counter and delay
  //   3 seconds, then print empty lines and the new datapoint sequence
  } else if (counter >= 200) {
    counter = 0;
    delay(3000);
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n-,-,-");
  }
  // Increment the counter and delay .01 seconds
  counter += 1;
  delay(10);
}