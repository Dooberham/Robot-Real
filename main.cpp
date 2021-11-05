#include <Servo.h>
Servo leftservo;  
Servo rightservo;  
const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
long distance;
long duration;
void setup() {
  leftservo.attach(9);  
  rightservo.attach(10);
   //set up the Serial
  Serial.begin(9600);
  //setupt the pin modes  
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  leftservo.write(90);
  rightservo.write(90);
 
}

void CheckDistance(){
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  //send the 10 microsecond trigger
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
}
void FollowWall() {
    CheckDistance();
    if (distance < 30) {
      //If its super close, turn to the right for 200ms
      //then go forward for 200ms
      leftservo.write(180);
      rightservo.write(180);
      delay(600);
      leftservo.write(180);
      rightservo.write(0);
      delay(600);
      leftservo.write(0);
      rightservo.write(0);
      delay(600);
    } else if (distance > 45) {
        //If its farther than 110cm, turn to the left for 200ms
        //then go forward for 200ms
        leftservo.write(0);
        rightservo.write(0);
        delay(600);
        leftservo.write(180);
        rightservo.write(0);
        delay(600);
        leftservo.write(180);
        rightservo.write(180);
        delay(600);
    } else {
        //if the distance = 110cm, go forward 200ms
        leftservo.write(180);
        rightservo.write(0);
        delay(200);
    }
  }
void loop() {
  //clear the ping pin
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  //send the 10 microsecond trigger
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  while (distance < 100)
  {
    FollowWall();
    CheckDistance();
    Serial.println(distance);
    if (distance > 100){
      break;
    }
  }
  while (distance > 100){
    while (true){
    leftservo.write(180);
    rightservo.write(180);
    delay(2500);
    CheckDistance();
    Serial.println(distance);
     if (distance < 37){  
        break;
      } 
       //90 deg turn back 
    leftservo.write(0);
    rightservo.write(0);
    delay(2500);
    Serial.println("debug");
    //go towards the wall
    leftservo.write(180);
    rightservo.write(0);
    delay(700);
    }
  }
  while (distance < 100) {
    Serial.println("second loop");
    FollowWall();
  }
  Serial.println("after second loop");
  while (distance > 100) {
    
    leftservo.write(90);
    rightservo.write(90);
    delay(10000);
  }
}