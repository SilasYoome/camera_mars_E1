#include <Arduino.h>
#include "HUSKYLENS.h"
#include <Wire.h>

byte maxMotorSpeed = 80;        // 馬達最大值
int motorOffset = 25;
int objectWidth = 70;           // 追隨物體方框面積
int turnGain = 1;               // 旋轉速度增益變數
int offCentre = 70;             // 左右輪速度偏轉變數
int disGain = 3;                // 旋轉速度增益變數

int leftLimit = 160-offCentre;  // 左馬達極限值
int rightLimit = 160+offCentre; // 右馬達極限值

int leftSp = 0;                 // 左馬達速度保存變數
int rightSp = 0;                // 右馬達速度保存變數
bool isTurning = false;         // 是否正在旋轉的flag
bool isTurningLeft = true;      // 是否在左轉的flag

HUSKYLENS husklens;
int ID1 = 1;


// put function declarations here:
void moveForward();
void stopMove();
void printResult(HUSKYLENSResult result);
void setMotorSpeed(int leftTempSp, int rightTempSp);

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(115200);
  Wire.begin();
  while (!husklens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  husklens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);
  setMotorSpeed(0,0);
  moveForward();
}

void loop() {
  // put your main code here, to run repeatedly:
  int32_t error;
  if(!husklens.request()){
    Serial.println(F("Fail to request objects from HUSKYLENS!"));
    stopMove();
  }
  else if(!husklens.isLearned()){
    Serial.println(F("Object not learned!")); 
    stopMove();
  }
  else if(!husklens.available()){
    Serial.println(F("Object disappeared!"));
    stopMove();
  }
  else{
    HUSKYLENSResult result = husklens.read();
    if(result.xCenter < leftLimit){
      leftSp = -turnGain*(leftLimit-result.xCenter);
      rightSp = turnGain*(leftLimit-result.xCenter);
    }
    else if(result.xCenter > rightLimit){
      leftSp = turnGain*(result.xCenter-rightLimit);
      rightSp = -turnGain*(result.xCenter-rightLimit);
    }
    if(result.width < objectWidth){
      leftSp = leftSp+(disGain*(objectWidth-result.width));
      rightSp = rightSp+(disGain*(objectWidth-result.width));
    }
    if(leftSp > maxMotorSpeed)
      leftSp = maxMotorSpeed;
    else if(leftSp < 0)
      leftSp = 0;
    if(rightSp > maxMotorSpeed)
      rightSp = maxMotorSpeed;
    else if(rightSp < 0)
      rightSp = 0;
    Serial.println(String()+F("leftSp: ")+leftSp+F("  rightSp:")+rightSp);
    setMotorSpeed(leftSp,rightSp);
    leftSp = 0;
    rightSp = 0;
    //printResult(result);
  }
}

// put function definitions here:
void moveForward() {
  digitalWrite(7,LOW);
  digitalWrite(4,HIGH);
}

void stopMove() {
  analogWrite(5,0);
  analogWrite(6,0);
}

void setMotorSpeed(int leftTempSp, int rightTempSp){
  analogWrite(5,leftTempSp);
  analogWrite(6,rightTempSp);
}

void printResult(HUSKYLENSResult result)                        //Display the results on the serial monitor，串行顯示追蹤結果
{
    if (result.command == COMMAND_RETURN_BLOCK)
    {
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW)
    {
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else
    {
        Serial.println("Object unknown!");
    }
}
