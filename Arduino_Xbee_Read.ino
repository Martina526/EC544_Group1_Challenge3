#include <SoftwareSerial.h>
SoftwareSerial XBee(2,3);
int LED_B,LED_R,LED_G,LED_Y;
int n;
char buffer[10];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  XBee.begin(9600);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  //digitalWrite(6,HIGH);
  //digitalWrite(4,HIGH);
  //digitalWrite(5,HIGH);
  //digitalWrite(6,HIGH);
  LED_B = digitalRead(4);
  LED_R = digitalRead(5);
  LED_G = digitalRead(6);
  LED_Y = digitalRead(7);
  n=sprintf (buffer, "B%dR%dG%dY%d\n",LED_B,LED_R,LED_G,LED_Y);
  XBee.print(buffer);
}

void loop() {
  if (XBee.available()){
      int temp;
      char c;
      temp = XBee.read();
      if (((temp>32) && (temp < 127)) || (temp == 10)) 
      { char c= temp; 
        Serial.print(c); 
        switch (c) {
     case 'R':
       Setpin(5);
       SendStats();
       break;
     case 'G':
       Setpin(6);
       SendStats();
       break;
     case 'B':
       Setpin(4);
       SendStats();
       break;
     case 'Y':
       Setpin(7);
       SendStats();
       break;
     case 'T':
       SendOriginStats();
       break;
     default: 
     break;
   }
      } 
  

  }  

  delay(100);
}
void SendStats(){
    LED_B = digitalRead(4);
  LED_R = digitalRead(5);
  LED_G = digitalRead(6);
  LED_Y = digitalRead(7);
  n=sprintf (buffer, "0B%dR%dG%dY%d\n",LED_B,LED_R,LED_G,LED_Y);
  XBee.print(buffer);
}
void SendOriginStats(){
    LED_B = digitalRead(4);
  LED_R = digitalRead(5);
  LED_G = digitalRead(6);
  LED_Y = digitalRead(7);
  n=sprintf (buffer, "1B%dR%dG%dY%d\n",LED_B,LED_R,LED_G,LED_Y);
  XBee.print(buffer);
}
void Setpin(int i){
   
      int temp;
      char c;
      temp = XBee.read();
      if (((temp>32) && (temp < 127)) || (temp == 10)) 
      { char c= temp; 
        Serial.print(c); 
        if ( c=='1'){
      digitalWrite(i, HIGH);}
      else if ( c=='0'){digitalWrite(i,LOW);}
      } 
      
  
}


