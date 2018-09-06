
/*
  SonarReflexRobot

  This code drives a simple robot using the HC-SR04 sensor.
  The implementation is very trivial and allows you to have a funny robot that are able to avoid obstacles. 
 */
#include <NewPing.h>
#include  <Servo.h>

//All the fixed values are declared as const integer
bool stopped=true;
bool stuck=false;

const uint16_t max_distance=500;
const uint8_t motor1_1= 5;
const uint8_t motor1_2= 6;
const uint8_t motor2_1= 11;
const uint8_t motor2_2= 10;
const uint8_t servo=9;
const uint8_t trigger=7;
const uint8_t echo=8;

const uint8_t left=0;
const uint8_t right=255;
const uint8_t center=90;

Servo sweep_motor;
NewPing sonar(trigger,echo,max_distance);

//stop motors
void motor_stop();
//moves servo motor from left to right and after that sets position to the center. this is useful to determine if the hcsr04 is mounted correctly 
void sweep_motor_check();
// moves hcsr04  to the left and measure distance
int look_left();
// moves hcsr04  to the left and measure distance
int look_right();
// start motors in forward direction 
void motor_forward(int velocity);
// start motors in backward direction 
void motor_backward();
// makes the robot turns right 
void motor_right();
// makes the robot turns left
void motor_left();

void setup() {

 //initialze all the pins needed
 pinMode(motor1_1,OUTPUT);
 pinMode(motor1_2,OUTPUT);
 pinMode(motor2_1,OUTPUT);
 pinMode(motor2_2,OUTPUT);
 
 //make sure that motors are stopped
 digitalWrite(motor1_1,LOW);
 digitalWrite(motor1_2,LOW);
 digitalWrite(motor2_1,LOW);
 digitalWrite(motor2_2,LOW);
 
 //initialize servo motor and perform check
 sweep_motor.attach(servo);
 sweep_motor_check();
 
  
}
 
void loop() {

 // measure distance
 int distance=sonar.ping_cm();

 // take action based on distance value
 if(distance<25 && distance!=0)
  {
    motor_stop();
    delay(1000);
    do{
      int left_distance=look_left();
      int right_distance=look_right();
      stuck=false;
      if(left_distance>20 || right_distance>20)
      {
          
          if(left_distance>right_distance)
            motor_left();
      
          else 
            motor_right();
      }
      else
      {
          motor_backward();
          delay(100);
          motor_stop();
          stuck=true;
      }
      }while(stuck);
      delay(1000);
  }
  
    if(stopped)
      motor_forward(80);
      
  

}

void motor_stop()
{
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,LOW);
  digitalWrite(motor2_2,LOW);
  stopped=true;
}

void sweep_motor_check()
{
   sweep_motor.write(left);
  delay(1000);
  sweep_motor.write(right);
  delay(1000);
  sweep_motor.write(center);
  delay(1000);
}
int look_left()
{ 
  int distance;
  sweep_motor.write(left);
  delay(1000);
  distance=sonar.ping_cm();
  sweep_motor.write(center);
  delay(1000);
  
  return distance;
}
int look_right()
{
  int distance;
  sweep_motor.write(right);
  delay(1000);
  distance=sonar.ping_cm();
  sweep_motor.write(center);
  delay(1000);
  
  return distance;
}

void motor_forward(int velocity)
{
  analogWrite(motor1_1,velocity);
  digitalWrite(motor1_2,LOW);
  analogWrite(motor2_1,velocity);
  digitalWrite(motor2_2,LOW);
  stopped=false;
}
void motor_backward()
{
  digitalWrite(motor1_2,HIGH);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor2_2,HIGH);
  digitalWrite(motor2_1,LOW);
  stopped=false;
}
void motor_right()
{
  digitalWrite(motor1_1,HIGH);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,LOW);
  digitalWrite(motor2_2,HIGH);
  delay(70);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor2_2,LOW);
}
void motor_left()
{
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,HIGH);
  digitalWrite(motor2_1,HIGH);
  digitalWrite(motor2_2,LOW);
  delay(70);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,LOW);
  
}





