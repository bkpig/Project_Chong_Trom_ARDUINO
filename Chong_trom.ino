#include <SoftwareSerial.h>
#include <Servo.h>
Servo ser;

#define SENSOR_PIN 4
#define S_PIN 8
SoftwareSerial bluetooth(6,5);
#define BUZZ 7
#define C 523
#define C_sharp 554
#define D 587
#define D_sharp 622
#define E 659
#define F 698
#define F_sharp 740
#define G 784
#define G_sharp 831
#define A 880
#define A_sharp 932
#define B 988

void setup(){
pinMode(BUZZ,OUTPUT);
pinMode(SENSOR_PIN,INPUT);
ser.attach(S_PIN);
bluetooth.begin(9600);
}

void activated(){
tone(BUZZ,A*2,125);
  delay(150);
tone(BUZZ,A*2,125);
    delay(150);
  tone(BUZZ,A*4,250);
    delay(260);
  tone(BUZZ,E*4,250);
    delay(260);
}
void deactivated(){

  tone(7,D*4,150);
  delay(180);
  tone(7,E*4,150);
   delay(180);
  tone(7,G*4,150);
   delay(180);
  
  tone(7,E*4,400);
   delay(400);
  tone(7,B*4,400);
  delay(500);
  tone(7,B*4,400);
  delay(500);
  tone(7,A*4,600);
  delay(600);
}
int a=-1;//-1 is deactivated,1 is activated
void alarm(){
  int reading =digitalRead(SENSOR_PIN);
  if(a==1){
    if(reading==HIGH){
       tone(BUZZ,B*4,1000);
        bluetooth.write("\nMotion Detected!!\n");
       delay(1000);
    }
  }

}

int door=1;//door is on open state
void loop(){
if(bluetooth.available()){
  int s=bluetooth.read();
  if(s==(char)'A'){
      a=(-a);
      if(a==1){
        bluetooth.write("\nActivated!!\n");
        activated();
      } else{
         bluetooth.write("\nDeactivated!!\n");
        deactivated();
        
      } 
    }
   if(s==(char)'B'){
    door=(-door);
    if(door==1){
      ser.write(180-160);
       bluetooth.write("\nDoor Opened!!!\n");
      deactivated();
       a=-1;
    }else {
      ser.write(180-84);
      bluetooth.write("\nDoor Closed!!!\n");
       activated();
       a=1;
    }
  }
  }
  alarm();
}
