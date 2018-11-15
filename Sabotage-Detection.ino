/*
  _____       .__  __         .__                
_/ ____\______|__|/  |________|__| ____    ____  
\   __\\_  __ \  \   __\___   /  |/    \  / ___\ 
 |  |   |  | \/  ||  |  /    /|  |   |  \/ /_/  >
 |__|   |__|  |__||__| /_____ \__|___|  /\___  / 
                             \/       \//_____/  
  
Example      Sabotage Detection
Autor        Stefan Hermann
Date         5.12.2011

*/

int myState=0;
int greenLedPin=11;
int redLedPin=7;
int blueLedPin=3;
int buttonPin=2;
int potPin=3;
int accZPin=0;
int accYPin=1;
int accXPin=2;

int startAccZ;
int startAccY;
int startAccX;

void setup(){
  pinMode(greenLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
  pinMode(blueLedPin,OUTPUT);
  pinMode(buttonPin,INPUT);
  startAccZ=analogRead(accZPin);
  startAccY=analogRead(accYPin);
  startAccX=analogRead(accXPin);
}

void alertBlinking(){
  digitalWrite(redLedPin,HIGH);
  delay(50);
  digitalWrite(redLedPin,LOW);
  delay(100);
  digitalWrite(blueLedPin,HIGH);
  delay(50);
  digitalWrite(blueLedPin,LOW); 
  delay(100);  
}

boolean senseAcceleration(int myPotVal){
  boolean myReturn=false;
  myPotVal=map(myPotVal,0,1023,0,10);
  if (analogRead(accXPin)>startAccX+myPotVal) myReturn=true;
  if (analogRead(accYPin)>startAccY+myPotVal) myReturn=true;
  if (analogRead(accZPin)>startAccZ+myPotVal) myReturn=true;
  return myReturn;
}

void loop(){
  //alertBlinking();
  switch (myState){
  case 0: //idle
    if (senseAcceleration(analogRead(potPin))==true) {
      digitalWrite(greenLedPin,LOW);
      myState=1;
    } else {
      digitalWrite(greenLedPin,HIGH);    
    };
    break;
  case 1: // alert
    alertBlinking();
    if (digitalRead(buttonPin)==HIGH){
      myState=0;
    }
    break;
  }
  delay(10);
}