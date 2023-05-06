#include<Servo.h>  // define the servo for arduino
#include "RTClib.h" // import RTC library7
#include "SdFat.h"

RTC_DS1307 rtc;
#define CS_PIN 10

File file;
Servo myservo; //call servo object

//define variables and constants
int position=A0;  // synchronizing the poteniometer with connected channel A0
int val;
int angle;
int i;
int mappingArray[91];
int mappingArray1[91];
String time = "" ;


void setup() {
  File file;
 
  Serial.begin(115200);  // establishing relationship between arduino and RTC while specifying the data transfer rate/bandwidth

 

// setting up RTC
if(! rtc.begin()){  //setting up rtc 
  Serial.println("could not find RTC");
  Serial.begin(115200);
  abort();
}

myservo.attach(9);  // synch gate 9 to transfer input to servo

}

void loop() {

  val= analogRead(position);
  val = map(val, 0,1023 , 180 , 0); //mapping from 2^10 to angle of 180 degrees
  myservo.write(val);
  delay(0);

  //setup date and time
  DateTime now =rtc.now();


   Serial.print("Angle: ");
angle= analogRead(position)/5.68888888889; // do calculate the angle 

for (i=0; i<=90; i++){     //loops to fill up the mapping array 0 and 1
 mappingArray[i]= i;
}
for (i=0; i<=90; i++){
  mappingArray1[i]= -(i+1);
}


if (analogRead(position)>= 512){     // doing the correct mapping for mapingArray 0 and 1
angle= mappingArray[angle-89];
}

if(analogRead(position)<512){
  angle= mappingArray1[89-angle];
}

  time = "[" + String(now.year() ,DEC) +"/" + String(now.month(),DEC) + "/" + String(now.day() , DEC)
   + " " + String(now.hour() , DEC) + ":" + String(now.minute() ,DEC) +":" +String(now.second() ,DEC) +
   "] Angle: " + String(angle) + " degrees." ;
//Serial.println(time);

  file.println(time);
  Serial.println(time);

  delay(3000);








}