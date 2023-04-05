#include "Wire.h"
#include "Tetris.h"

int mypins[4] = {9,10,11,12}; //UP, DOWN, RIGHT, LEFT
byte myreadings[4];
String mode;//options: MENU, GAME
String actions[4] = {"UP", "DOWN", "RIGHT", "LEFT"};
String action; //UP, DOWN, RIGHT, LEFT

void setup(){
  for (int i=0;i<4;i++){
    pinMode(mypins[i], INPUT);
  }
  mode = "MENU";
  Serial.begin(9600);
  Wire.begin();
}

void loop(){
  for (int i=0; i<4; i++){
    myreadings[i] = digitalRead(mypins[i]);

    if (myreadings[i] == LOW){//it is a pull up button
      action = actions[i];
    }
    Serial.println(action);
  }
  
  Wire.beginTransmission(4);
  ProcessState();
  Wire.endTransmission(4);
}

void ProcessState(){
  //process states
}
