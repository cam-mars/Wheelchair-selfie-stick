#include <Wire.h>
#include "SparkFun_Qwiic_Joystick_Arduino_Library.h"
#include <Servo.h>

// Create joystick and servo objects
JOYSTICK joystick;
Servo servoX;
Servo servoY;
int servoXpin = 10, servoYpin = 9;
int servoXpos = 90, servoYpos = 90;
int xLimit = 180, yLimit = 30;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the joystick
  if (joystick.begin() == false) {
    Serial.println("Joystick not detected. Check wiring.");
    while (1);
  }
  Serial.println("Joystick detected!");

  // Attach servos to pins
  servoX.attach(servoXpin);
  servoY.attach(servoYpin);
  servoX.write(servoXpos);
  servoY.write(servoYpos);
}

void loop() {
  //servoXpos = 90, servoYpos = 90;
  // Read joystick position
  int xPosition = joystick.getHorizontal();
  int yPosition = joystick.getVertical();

  if(xPosition == 1023  && servoXpos < xLimit){
    servoXpos+=10;
    servoX.write(servoXpos);  
  }
  if(xPosition == 0 && servoXpos > 0){
    servoXpos-=10;
    servoX.write(servoXpos);
  }
  if(yPosition == 0  && servoYpos < yLimit){ //positions on joystick switch
    servoYpos+=10;
    servoY.write(servoYpos);  
  }
  if(yPosition == 1023 && servoYpos > 0){
    servoYpos-=10;
    servoY.write(servoYpos);
  }
  if(servoXpos >= xLimit){
    servoX.write(xLimit);
  }
  if(servoYpos >= yLimit){
    servoY.write(yLimit);
  }
  // Print the positions for debugging
  Serial.print("\nX: ");
  Serial.print(xPosition);

  Serial.print("\nY: ");
  Serial.print(yPosition);

  // Small delay to avoid overwhelming the serial monitor
  delay(100);
}
