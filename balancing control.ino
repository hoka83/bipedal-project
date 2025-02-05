/* Get all possible data from MPU6050
 * Accelerometer values are given as multiple of the gravity [1g = 9.81 m/s²]
 * Gyro values are given in deg/s
 * Angles are given in degrees
 * Note that X and Y are tilt angles and not pitch/roll.
 *
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);
#include <VarSpeedServo.h>

VarSpeedServo S1_R;
VarSpeedServo S2_R;
VarSpeedServo S4_R;
VarSpeedServo S22_R;
VarSpeedServo S44_R;
VarSpeedServo S9_R;

VarSpeedServo S1_L;
VarSpeedServo S2_L;
VarSpeedServo S4_L;
VarSpeedServo S22_L;
VarSpeedServo S44_L;
VarSpeedServo S9_L;

#define s1r 2
#define s2r 3
#define s4r 4
#define s22r 5
#define s44r 6
#define s9r 7

#define s1l 8
#define s2l 9
#define s4l 10
#define s22l 11
#define s44l 12
#define s9l 13


float  thS1_R = 115;
float  thS1_L = 100;
float  thS2_R = 100;
float  thS4_R = 115;
float  thS9_L = -18;
float  thS2_L = 80;
float  thS4_L = 180;
float  thS9_R = -18;

  
  float thetaM;
  float phiM;
  float thetaFold=0;
  float thetaFnew;
  float phiFold=0;
  float phiFnew;
  float thetaG=0;
  float phiG=0;
  float theta;
  float phi;
  float dt;
  unsigned long millisOld;

  float pitchTarget=5;
  float pitchError=0;
  float pitchErrorOld;
  float pitchErrorChange;
  float pitchErrorSlope=0;
  float pitchErrorArea=0;
  float pitchActual;
  
  float rollTarget=0;
  float rollError=0;
  float rollErrorOld;
  float rollErrorChange;
  float rollErrorSlope=0;
  float rollErrorArea=0;
  float rollActual;
   

  float k1=0.01;
  float k2=0.06;
  float k3=0.00000001;
  int milliOld1;
  int milliNew1;
  int dt1;
void setup() {
    S1_R.attach(s1r);
    S2_R.attach(s2r);
    S4_R.attach(s4r);
   S22_R.attach(s22r);
    S44_R.attach(s44r);
    S9_L.attach(s9r);

    S1_L.attach(s1l);
    S2_L.attach(s2l);
   S4_L.attach(s4l);
    S22_L.attach(s22l);
    S44_L.attach(s44l);
    S9_R.attach(s9l);
    //pinMode(44,OUTPUT);

 S1_R.write(thS1_R);//1480
  S2_R.write(75 + thS2_R - 90); //94+thS2_R-90);//-x  94   \78
  S4_R.write(120 + thS4_R - 180); //1+thS4_R-90);//86  1
  S22_R.write(95 - thS2_R + 90); //99-thS2_R+90);//+x      /98
  S44_R.write(90 - thS4_R + 180); //171-thS4_R+90);//81  171    (73)
  S9_L.write(90 - thS9_L); //115+x/2);//+x/2

  S1_L.write(thS1_L);//1390
  S2_L.write(95 - thS2_L + 90); //+x
  S4_L.write(130 - thS4_L + 180); //180-thS4_L+90);
  S22_L.write(76 + thS2_L - 90); //-x
  S44_L.write(60 + thS4_L - 180); //0+thS4_L-90);
  S9_R.write(100 + thS9_R); //76-x/2);//-x/2

  
  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(false,false); // gyro and accelero
  Serial.println("Done!\n");
  
  millisOld=millis();

  
}

void loop() {
  
    
    for(int i = 44 ; i < 45 ; i++){
    
    if(i==44){
      
    digitalWrite(i,LOW);
    // pitchActual = mpu2.getAccAngleX()-3.5;
    // rollActual = mpu2.getAccAngleY()-11.5;
          
    thetaM=mpu.getAccX()*100;
    phiM=mpu.getAccY()*100;

    phiFnew=0.96*phiFold+0.04*phiM;
    thetaFnew=0.96*thetaFold+0.04*thetaM;
   
    dt=(millis()-millisOld)/1000;
    millisOld=millis();
    pitchActual=(pitchActual+mpu.getGyroY()*100*dt)*.95+thetaM*.05+0.3005;
    rollActual=(rollActual-mpu.getGyroX()*100*dt)*.95+ phiM*.05;
    thetaG=thetaG+mpu.getGyroY()*100*dt;
    phiG=phiG-mpu.getGyroX()*100*dt;
    }
    for(int j = 44 ; j < 45 ; j++){
      if( i != j ){ 
      digitalWrite(j,HIGH);
  }     
  mpu.update();

    //Serial.print(rollActual);

    
    phiFold=phiFnew;
    thetaFold=thetaFnew;
    }


    milliOld1=milliNew1;
    milliNew1=millis();
    dt1=(milliNew1-milliOld1);


    rollErrorOld=rollError;
    rollError=rollTarget-rollActual;
    rollErrorChange=rollError-rollErrorOld;
    rollErrorSlope=rollErrorChange/dt1;
    rollErrorArea=rollErrorArea+rollError*dt1;
 
    pitchErrorOld=pitchError;
    pitchError=pitchTarget-pitchActual;
    pitchErrorChange=pitchError-pitchErrorOld;
    pitchErrorSlope=pitchErrorChange/dt1;
    pitchErrorArea=pitchErrorArea+pitchError*dt1;
   
    pitchError=pitchActual-pitchTarget;
    rollError=rollActual-rollTarget;

    thS9_L=(thS9_L+k1*pitchError+k2*pitchErrorSlope+k3*pitchErrorArea);
    thS9_R=(thS9_R+k1*pitchError+k2*pitchErrorSlope+k3*pitchErrorArea);
    Serial.print(pitchActual);
    //Serial.print(" ");
    //Serial.print(thS9_L);
    Serial.print(" ");
    Serial.println();
    S9_R.write(100+thS9_R);
    S9_L.write(90-thS9_L);
   
    }
}
