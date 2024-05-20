
// CNC Shield Stepper  Control Demo
// Superb Tech
// www.youtube.com/superbtech
#include <stdlib.h>
#include <AccelStepper.h>
#include <time.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

const int StepX = 2;
const int DirX = 5;
const int StepY = 3;
const int DirY = 6;
const int StepZ = 4;
const int DirZ = 7;
const int rev = 200;

AccelStepper stepper1(1, StepX, DirX); //setup for first stepper
AccelStepper stepper2(1, StepY, DirY);
AccelStepper stepper3(1, StepZ, DirZ);

//setup pin for LCD
LiquidCrystal lcd_1(23,24,25,26,27,28);

// variable use to measuer the intervals inbetween impulses
int  i=0;
// Number of impulses detected
int impulsCount=0;
// Sum of all the  coins inseted
float total_amount=0;

//pos of motor
// int pos_1 = stepper1.currentPosition();
// int pos_2 = stepper2.currentPosition();
// int pos_3 = stepper3.currentPosition();


//sensor
// int sensor_1 = digitalRead(52);
// int sensor_2 = digitalRead(50);
// int sensor_3 = digitalRead(48);
//1st reel spin
void spin_1(){
  stepper1.move(50);
  stepper1.run();
}
//2nd reel spin
void spin_2(){
  stepper2.move(50);
  stepper2.run();
}
//3rd reel spin
void spin_3(){
  stepper3.move(50);
  stepper3.run();
}

//function for last spin for 1st reel
void Last_spin_1(){
  int end_value;
   
  randomSeed(analogRead(0));//seed for random value
  end_value = random(200); //random value
  // stepper1.stop();
  // delay(10);
  Serial.println(stepper1.currentPosition());//read the position when the function call
  //move to the end position depend on the random value then print out value
  stepper1.runToNewPosition(stepper1.currentPosition()+end_value);
  Serial.println(stepper1.currentPosition());

}
//function for last spin for 2nd reel
void Last_spin_2(){
  int end_value;
  
  randomSeed(analogRead(0));//seed for random value
  end_value = random(200); //random value
  // stepper1.stop();
  // delay(10);
  Serial.println(stepper2.currentPosition());//read the position when the function call
  //move to the end position depend on the random value then print out value
  stepper2.runToNewPosition(stepper2.currentPosition()+end_value);
  Serial.println(stepper2.currentPosition());
 
}
//function for last spin for 3rd reel
void Last_spin_3(){
  int end_value;
  
  randomSeed(analogRead(0));//seed for random value
  end_value = random(200); //random value
  // stepper1.stop();
  // delay(10);
  Serial.println(stepper3.currentPosition());//read the position when the function call
  //move to the end position depend on the random value then print out value
  stepper3.runToNewPosition(stepper3.currentPosition()+end_value);
  Serial.println(stepper3.currentPosition());

}

// //calibrate reel 1
// void calibrate_1()
// {
//   stepper1.setMaxSpeed(50);
//   stepper1.move(rev);
//   while(sensor_1 == HIGH){
//     stepper1.run();
//   }
//   stepper1.stop();
//   stepper1.setCurrentPosition(0);
//   stepper1.setMaxSpeed(1000);
  
// } 

// //calibrate reel 2
// void calibrate_2()
// {
//   stepper2.setMaxSpeed(50);
//   stepper2.move(rev);
//   while(sensor_2 == HIGH){
//     stepper2.run();
//   }
//   stepper2.stop();
//   stepper2.setCurrentPosition(0);
//   stepper2.setMaxSpeed(1000);

// } 

// //calibrate reel 3
// void calibrate_3()
// {
//   stepper3.setMaxSpeed(50);
//   stepper3.move(rev);
//   while(sensor_3 == HIGH){
//     stepper3.run();
//   }
//   stepper3.stop();
//   stepper3.setCurrentPosition(0);
//   stepper3.setMaxSpeed(1000);
  
// } 
// //check current pos 1 
// void poscheck_1()
// {
//   pos_1=0;
// }


//next 2 function is for coin acceptor
void incomingImpuls()
{
  impulsCount=impulsCount+1;
  i=0;
}

int coin_acceptor(int coin_state)
{
 i++;
  // Serial.print("i=");
  // Serial.print(i);
  // Serial.print(" Impulses:");
  // Serial.print(impulsCount);
  // Serial.print(" Total:");
  // Serial.println(total_amount);
if (i>=30  and impulsCount==1){
    total_amount=total_amount+1;
    impulsCount=0;
  }
   if (i>=30 and impulsCount==2){
    total_amount=total_amount+5;
    impulsCount=0;
  }
   if (i>=30 and impulsCount==3){
    total_amount=total_amount+10;
    impulsCount=0;
  }
   if (i>=30 and  impulsCount==4){
    total_amount=total_amount+25;
    impulsCount=0;
  }
   if (i>=30 and impulsCount>=5){
    total_amount=total_amount+100;
    impulsCount=0;
  };

if (total_amount>=1){
  coin_state++;
};
return coin_state;
}

//setup stuff
void setup() {
  //stepper 1 x v a
 stepper1.setMaxSpeed(1000);
 stepper1.setAcceleration(1000);
 stepper1.setCurrentPosition(0);
  //stepper 2 x v a
 stepper2.setMaxSpeed(1000);
 stepper2.setAcceleration(1000);
 stepper2.setCurrentPosition(0);
  //stepper 3 x v a
 stepper3.setMaxSpeed(1000);
 stepper3.setAcceleration(1000);
 stepper3.setCurrentPosition(0);

Serial.begin(9600);
pinMode(22, INPUT);

pinMode(18, INPUT_PULLUP);
 // Interrupt connected  to PIN D2 executing IncomingImpuls function when signal goes from HIGH to LOW
  attachInterrupt(digitalPinToInterrupt(18),incomingImpuls, FALLING);

lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.

//pin for sensor
// pinMode(52, INPUT);
// pinMode(50,INPUT);
// pinMode(48, INPUT);
//set interupt to sensor pin to check constantly
// attachInterrupt(digitalPinToInterrupt(19),poscheck_1, LOW);

//calibrate
// calibrate_2();
// delay(250);
// calibrate_3();
}


//main game
void loop() {

int button_state = digitalRead(22);
static int game_state = 0;
//first state of the game (game_state = 0)

// //calibrate
// if(game_state==-1){
//   // calibrate_1();
  
//   delay(250);
  
//   if(pos_3==0){
//     game_state++;
//   }
// }


//wait for coin insert
if(game_state==0){
  lcd_1.clear();
  lcd_1.setCursor(2, 0);
  lcd_1.print("INSERT COIN");
  Serial.println("Game state is 0");
  game_state = coin_acceptor(game_state);
};


//game initialize and reel start turning
switch(game_state){
  case 1://1st reel spin
  spin_1();
  Serial.println("Game is 1");
  case 2://2nd reel spin
  spin_2();
  case 3://3rd reel spin
  spin_3();
  lcd_1.clear();
  lcd_1.setCursor(3, 0);
  lcd_1.print("GOOD LUCK");
 break;
}

//when button is press (fix coin shit)
//add && coin_state == true
if(button_state==HIGH){
  game_state++;
  switch(game_state){
    case 2:
    Last_spin_1();
    Serial.print("game state is "); Serial.println(game_state);
    break;
    case 3:
    Last_spin_2();
    Serial.print("game state is "); Serial.println(game_state);
    break;
    case 4:
    Last_spin_3();
    Serial.print("game state is "); Serial.println(game_state);
    break;
  }
  
}
if (game_state>=4){
  lcd_1.clear();
  lcd_1.setCursor(3, 0);
  lcd_1.print("GAME OVER");
}
}
