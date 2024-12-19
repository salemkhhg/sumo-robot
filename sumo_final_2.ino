/******************************************************  libraires ***************************************************/

#include<stdio.h>
#include<stdlib.h>
/************************************************  global declration and defination ***********************************************/

const int IN1 = 15;        // pin motor front left wheel
const int IN2 = 14;        //pin motor front left wheel
const int IN3 = 17;        //pin motor front right wheel
const int IN4 = 16;        //pin motor front right wheel

const int IN11 = 19;       //pin motor back left wheel
const int IN22 = 18;       //pin motor back left wheel
const int IN33 = 21;       //pin motor back right wheel
const int IN44 = 20;       //pin motor back right wheel

const int IR_FR = 4;       //pin for front right ir sensor
const int IR_FL = 3;       //pin for front left ir sensor
const int IR_BR = 2;       //pin for back right ir sensor
const int IR_BL = 1;       //pin for back left ir sensor

const int trig_F = 12 ;    //triger pin for front ultrasonic
const int echo_F = 11 ;    //echo pin for front ultrasonic
const int trig_B = 10 ;    //triger pin for back ultrasonic
const int echo_B = 9 ;     //echo pin for back ultrasonic
const int trig_R = 8;      //triger pin for right ultrasonic
const int echo_R = 7 ;     //echo pin for right ultrasonic
const int trig_L = 6 ;     //triger pin for left ultrasonic
const int echo_L = 5;      //echo pin for left ultrasonic

int WHITE = 0;             //varible for ir sensor that i read white
int BLACK = 1;             //varible for ir sensor that i read black

long dur;                  // the duration time that i get the wave from ultrasonic
int dis;                   // the distance i get from ultrasonic sensor
int dis_F;                 // the distance i get from front ultrasonic sensor
int dis_B;                 // the distance i get from back ultrasonic sensor
int dis_R;                 // the distance i get from right ultrasonic sensor
int dis_L;                 // the distance i get from left ultrasonic sensor

void go_Forward();         //function to make robot move forward
void go_Backword();        //function to make robot move backward
void stop_Ropot();         //function to make robot stop
void go_Right();           //function to make robot move right
void go_Left();            //function to make robot move left
void back_Right();         //function to make robot move backright
void back_Left();          //function to make robot move backleft
void find_Right();         //function to make robot move front right due to the right ultrasonic
void find_Left();          //function to make robot move front left due to the right ultrasonic
int Find(int x, int y);    //function to make robot find any other robot using ultrasonic
void Attack();             //function to make robot attack if any other robot in the region of ant ultrasonic
/******************************************************  intialization ***************************************************/

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN11, OUTPUT);
  pinMode(IN22, OUTPUT);
  pinMode(IN33, OUTPUT);
  pinMode(IN44, OUTPUT);

  pinMode(IR_FR, INPUT);
  pinMode(IR_BR, INPUT);
  pinMode(IR_FR, INPUT);
  pinMode(IR_BR, INPUT);

  pinMode(trig_F, OUTPUT);
  pinMode(echo_F, INPUT);
  pinMode(trig_B, OUTPUT);
  pinMode(echo_B, INPUT);
  pinMode(trig_R, OUTPUT);
  pinMode(echo_R, INPUT);
  pinMode(trig_L, OUTPUT);
  pinMode(echo_L, INPUT);
  Serial.begin(9600);
}

/******************************************************  main programe ***************************************************/

void loop()
{
  if (digitalRead(IR_FR) == WHITE & digitalRead(IR_FL) == WHITE & digitalRead(IR_BR) == WHITE & digitalRead(IR_BL) == WHITE)
  {
    Attack();
  }
  
  else if (digitalRead(IR_FR) == WHITE & digitalRead(IR_FL) == WHITE & digitalRead(IR_BR) == WHITE & digitalRead(IR_BL) == BLACK)
  { 
    go_Right();
    delay(50);
  }
  
  else if (digitalRead(IR_FR) == WHITE & digitalRead(IR_FL) == WHITE & digitalRead(IR_BR) == BLACK & digitalRead(IR_BL) == WHITE)
  { 
    go_Left();
    delay(50);
  }
  
  else if (digitalRead(IR_FR) == WHITE & digitalRead(IR_FL) == WHITE & digitalRead(IR_BR) == BLACK & digitalRead(IR_BL) == BLACK)
  { 
    go_Forward();
    delay(50);
  }
  
  else if (digitalRead(IR_FR) == WHITE & digitalRead(IR_FL) == BLACK & digitalRead(IR_BR) == WHITE & digitalRead(IR_BL) == WHITE)
  { 
    back_Right();
    delay(50);
  }
  
  else if (digitalRead(IR_FR) == WHITE & digitalRead(IR_FL) == BLACK & digitalRead(IR_BR) == WHITE & digitalRead(IR_BL) == BLACK)
  { 
    go_Right();
    delay(50);
  }
  
  else if (digitalRead(IR_FR) == WHITE & digitalRead(IR_FL) == BLACK & digitalRead(IR_BR) == BLACK & digitalRead(IR_BL) == WHITE)
  {
    stop_Ropot();
  }
  
  else if (digitalRead(IR_FR) == WHITE & digitalRead(IR_FL) == BLACK & digitalRead(IR_BR) == BLACK & digitalRead(IR_BL) == BLACK)
  {
    stop_Ropot();
  }
    
  else if (digitalRead(IR_FR) == BLACK & digitalRead(IR_FL) == WHITE & digitalRead(IR_BR) == WHITE & digitalRead(IR_BL) == WHITE)
  { 
    back_Left();
    delay(50);
  }
  
  else if (digitalRead(IR_FR) == BLACK & digitalRead(IR_FL) == WHITE & digitalRead(IR_BR) == WHITE & digitalRead(IR_BL) == BLACK)
  {
    stop_Ropot();
  }
    
  else if (digitalRead(IR_FR) == BLACK & digitalRead(IR_FL) == WHITE & digitalRead(IR_BR) == BLACK & digitalRead(IR_BL) == WHITE)
  { 
    go_Left();
    delay(50);
  }
  
  else if (digitalRead(IR_FR) == BLACK & digitalRead(IR_FL) == WHITE & digitalRead(IR_BR) == BLACK & digitalRead(IR_BL) == BLACK)
    stop_Ropot();
  else if (digitalRead(IR_FR) == BLACK & digitalRead(IR_FL) == BLACK & digitalRead(IR_BR) == WHITE & digitalRead(IR_BL) == WHITE)
  { 
    go_Backword();
    delay(50);
  }
  
  else if (digitalRead(IR_FR) == BLACK & digitalRead(IR_FL) == BLACK & digitalRead(IR_BR) == WHITE & digitalRead(IR_BL) == BLACK)
   {
    stop_Ropot();
   }
    
  else if (digitalRead(IR_FR) == BLACK & digitalRead(IR_FL) == BLACK & digitalRead(IR_BR) == BLACK & digitalRead(IR_BL) == WHITE)
   {
    stop_Ropot();
   }
    
  else if (digitalRead(IR_FR) == BLACK & digitalRead(IR_FL) == BLACK & digitalRead(IR_BR) == BLACK & digitalRead(IR_BL) == BLACK)
   {
    stop_Ropot();
   }
}

/******************************************************  sub programe defination ***************************************************/

//......................
void go_Forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN11, HIGH);
  digitalWrite(IN22, LOW);
  digitalWrite(IN33, LOW);
  digitalWrite(IN44, HIGH);
}
//......................
void go_Backword()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN11, LOW);
  digitalWrite(IN22, HIGH);
  digitalWrite(IN33, HIGH);
  digitalWrite(IN44, LOW);
}
//......................
void stop_Ropot()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN11, LOW);
  digitalWrite(IN22, LOW);
  digitalWrite(IN33, LOW);
  digitalWrite(IN44, LOW);
}
//......................
void go_Right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN11, HIGH);
  digitalWrite(IN22, LOW);
  digitalWrite(IN33, LOW);
  digitalWrite(IN44, LOW);
}
//......................
void go_Left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN11, LOW);
  digitalWrite(IN22, LOW);
  digitalWrite(IN33, LOW);
  digitalWrite(IN44, HIGH);
}
//......................
void back_Right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN11, LOW);
  digitalWrite(IN22, HIGH);
  digitalWrite(IN33, LOW);
  digitalWrite(IN44, LOW);
}
//......................
void back_Left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN11, LOW);
  digitalWrite(IN22, LOW);
  digitalWrite(IN33, HIGH);
  digitalWrite(IN44, LOW);
}
//......................
void find_Right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN11, HIGH);
  digitalWrite(IN22, LOW);
  digitalWrite(IN33, HIGH);
  digitalWrite(IN44, LOW);
}
//......................
void find_Left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN11, LOW);
  digitalWrite(IN22, HIGH);
  digitalWrite(IN33, LOW);
  digitalWrite(IN44, HIGH);
}
//......................
int Find(int x, int y)
{
  digitalWrite(x, LOW);
  delayMicroseconds(2);
  digitalWrite(x, HIGH);
  delayMicroseconds(10);
  digitalWrite(x, LOW);
  long dur = pulseIn(y, HIGH);
  dis = dur * 0.034 / 2;
}
//.........................
void Attack()
{
  Find(trig_F, echo_F);
  dis_F = dis;
  Find(trig_B, echo_B);
  dis_B = dis;
  Find(trig_R, echo_R);
  dis_R = dis;
  Find(trig_L, echo_L);
  dis_L = dis;

  if (dis_F < 10)
    go_Forward();
  else if (dis_B < 10)
    go_Backword();
  else if (dis_R < 10)
    find_Right();
  else if (dis_L < 10)
    find_Left();
  else
    stop_Ropot();
}
