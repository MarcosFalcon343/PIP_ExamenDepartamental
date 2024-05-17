#include <Servo.h>

Servo servoMotor;

#define Trigger 2
#define Echo 3

int servo = 0;
int distancia = 0;

long t = 0;
long d = 0;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(9);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  servoMotor.write(0);
}

void loop() {
  if(Serial.available() > 0){
    servo = Serial.readString().toInt();
     servoMotor.write(servo);
  }
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH);
  d = t / 59;
  Serial.println(d);
  delay(500);
}
