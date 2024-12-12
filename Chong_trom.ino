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
  tone(BUZZ,E*4,250);
    delay(260);
    tone(BUZZ,E*4,125);
    delay(150);
    tone(BUZZ,E*4,250);
    delay(260);
    tone(BUZZ,E*4,250);
    delay(260);
    tone(BUZZ,E*4,250);
    delay(260);
  
    tone(BUZZ,D*4,250);
    delay(260);
    tone(BUZZ,D*4,250);
    delay(260);
}
int a=-1;//-1 is deactivated,1 is activated
void alarm(){
  int reading =digitalRead(SENSOR_PIN);
  if(a==1){
    if(reading==HIGH){
       tone(BUZZ,B*4,1000);
       delay(1000);
    }
  }

}

int door=1;
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
    }else if(s==(char)'B'){
    door=(-door);
    if(door==1){
      ser.write(180-160);
       bluetooth.write("\nDoor Opened!!!\n");
    }else {
      ser.write(180-84);
      bluetooth.write("\nDoor Closed!!!\n");
    }
  }
  }
  alarm();
}