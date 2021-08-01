#include <ros.h>
#include <std_msgs/Bool.h>
ros::NodeHandle nh;
std_msgs::Bool pushed_msg;
ros::Publisher pub_joy("pushed", &pushed_msg);
int motorPin = 9;

int joystick_x = A0;
int joystick_y = A1;


int joystick_xvalue = 0;
int joystick_yvalue = 0;

void setup() {
  nh.initNode();
  nh.advertise(pub_joy); 
  pinMode(motorPin, OUTPUT);
  pinMode(joystick_x, INPUT);
  pinMode(joystick_y, INPUT);

}

void loop() {

  joystick_xvalue = 0;
  joystick_yvalue = 0;
  
  joystick_xvalue = analogRead(joystick_x);
  joystick_xvalue = map (joystick_xvalue, 0, 1023, -90, 90);
  
  joystick_yvalue = analogRead(joystick_y);
  joystick_yvalue = map (joystick_yvalue, 0, 1023, -90, 90);

  if(joystick_xvalue < -5 || joystick_xvalue > 5 || joystick_yvalue < -5 || joystick_yvalue >5){
    digitalWrite(motorPin, HIGH);
    pushed_msg.data = true;
    pub_joy.publish(&pushed_msg);
  }
  else{
    digitalWrite(motorPin, LOW);
    pushed_msg.data = false;
    pub_joy.publish(&pushed_msg);
  }
  nh.spinOnce();
  delay(15);
}
