#include <Ramp.h>
#include <Servo.h>

const int SERVO_MAX = 2400; // max servo PWM signal
const int SERVO_MIN = 550; // min servo PWM signal

const int POT_MAX = 1023; // max analog read from pot line
const int POT_MIN = 0; // min of same value

const int MOVE_MAX = 80; // max range that can be moved on one axis
const int MOVE_MIN = 0; // min range ""

const int wristPin = 4;
const int elbowPin = 3;
const int shoulderPin = 2;

const int xPotPin = 13;
const int yPotPin = 12;

const float armLen = 63.019; // in mm
const float clawLen = 41.40; // in mm

Servo wristServo;
Servo elbowServo;
Servo shoulderServo;

float xPotVal;
float yPotVal;
float x;
float y;

float alpha;
float beta;
float zeta;

int alphaPWM;
int betaPWM;
int zetaPWM;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  wristServo.attach(wristPin);
  elbowServo.attach(elbowPin);
  shoulderServo.attach(shoulderPin);

}

void loop() {
  // put your main code here, to run repeatedly:

  xPotVal = analogRead(xPotPin);
  yPotVal = analogRead(yPotPin);

  x = map(xPotVal, POT_MIN, POT_MAX, MOVE_MIN, MOVE_MAX);
  y = map(yPotVal, POT_MIN, POT_MAX, MOVE_MIN, MOVE_MAX);

  alpha = 180 - ((acos((powf(x, 2.0) + powf(y, 2.0)) / (2 * armLen * sqrtf(powf(x, 2.0) + powf(y, 2.0)))))*(180.0/PI)) - ((atan(y/x))*(180.0/PI));
  beta = 180 - ((acos(((2*(powf(armLen, 2.0))) - powf(x, 2.0) - powf(y, 2.0)) / (2 * pow(armLen, 2.0))))*(180.0/PI));
  zeta = 180 - beta - alpha + (2 * ((atan(y/x))*(180.0/PI)));  

  alphaPWM = map(alpha, 0, 180, SERVO_MAX, SERVO_MIN);  
  betaPWM = map(beta, 0, 180, SERVO_MIN, SERVO_MAX);
  zetaPWM = map(zeta, 0, 180, SERVO_MAX, SERVO_MIN); 

  shoulderServo.writeMicroseconds(alphaPWM);
  elbowServo.writeMicroseconds(betaPWM);
  wristServo.writeMicroseconds(zetaPWM);         
  
  // Serial.print(x);
  // Serial.print(",");
  // Serial.print(y);
  // Serial.print(",");  
  // Serial.print(alpha);
  // Serial.print(",");
  // Serial.print(beta);
  // Serial.print(",");
  // Serial.print(zeta);
  // Serial.print(",");
  // Serial.print(alphaPWM);
  // Serial.print(",");
  // Serial.print(betaPWM);
  // Serial.print(",");
  // Serial.println(zetaPWM);


}
