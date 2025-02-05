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
  int i;
  float thS1_R=-30;
  float thS1_L=0;
  float thS2_R=80;
  float thS4_R=140;
  float thS9_L=-40;
  float thS2_L=45;
  float thS4_L=200;
  float thS9_R=-5;
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
  
  S1_R.write(100+thS1_R);//1480
  S2_R.write(85+thS2_R-90);//94+thS2_R-90);//-x  94   \78
  S4_R.write(110+thS4_R-180);//1+thS4_R-90);//86  1
  S22_R.write(98-thS2_R+70);//99-thS2_R+90);//+x      /98
  S44_R.write(75-thS4_R+205);//171-thS4_R+90);//81  171    (73)
  S9_L.write(110-thS9_L);//115+x/2);//+x/2

  S1_L.write(100+thS1_L);//1390
  S2_L.write(100-thS2_L+80);//+x
  S4_L.write(79-thS4_L+195);//180-thS4_L+90);
  S22_L.write(76+thS2_L-10);//-x
  S44_L.write(96+thS4_L-180);//0+thS4_L-90);
  S9_R.write(77+thS9_R);//76-x/2);//-x/2
  delay(5000);

}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(i== 0){
   thS1_R=-30;
   thS1_L=0;
   thS2_R=80;
   thS4_R=140;
   thS9_L=-40;
   thS2_L=45;
   thS4_L=200;
   thS9_R=-5;

S1_R.write(100+thS1_R,10);//1480
  S2_R.write(85+thS2_R-90,10);//94+thS2_R-90);//-x  94   \78
  S4_R.write(110+thS4_R-180,10);//1+thS4_R-90);//86  1
  S22_R.write(98-thS2_R+70,10);//99-thS2_R+90);//+x      /98
  S44_R.write(75-thS4_R+205,10);//171-thS4_R+90);//81  171    (73)
  S9_L.write(110-thS9_L,13);//115+x/2);//+x/2

  S1_L.write(100+thS1_L,10);//1390
  S2_L.write(100-thS2_L+80,10);//+x
  S4_L.write(79-thS4_L+195,10);//180-thS4_L+90);
  S22_L.write(76+thS2_L-10,10);//-x
  S44_L.write(96+thS4_L-180,10);//0+thS4_L-90);
  S9_R.write(77+thS9_R,13);//76-x/2);//-x/2
  
  delay(3000);
  i=1;
  }
   if(i== 1){
   thS1_R=-30;
   thS1_L=0;
   thS2_R=60;
   thS4_R=160;
   thS9_L=-67;
  thS2_L=65;
  thS4_L=180;
   thS9_R=-32;
     S1_R.write(100+thS1_R,10);//1480
  S2_R.write(85+thS2_R-90,10);//94+thS2_R-90);//-x  94   \78
  S4_R.write(110+thS4_R-180,10);//1+thS4_R-90);//86  1
  S22_R.write(98-thS2_R+70,10);//99-thS2_R+90);//+x      /98
  S44_R.write(75-thS4_R+205,10);//171-thS4_R+90);//81  171    (73)
  S9_L.write(110-thS9_L,12);//115+x/2);//+x/2

  S1_L.write(100+thS1_L,10);//1390
  S2_L.write(100-thS2_L+80,10);//+x
  S4_L.write(79-thS4_L+195,10);//180-thS4_L+90);
  S22_L.write(76+thS2_L-10,10);//-x
  S44_L.write(96+thS4_L-180,10);//0+thS4_L-90);
  S9_R.write(77+thS9_R,12);//76-x/2);//-x/2
  delay(3000);
  i=0;
}
}
