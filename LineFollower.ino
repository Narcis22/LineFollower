#include <QTRSensors.h>
const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 5;
const int m22Pin = 4;
const int m1Enable = 11;
const int m2Enable = 10;

const int redLedPinLeft = 9;
const int greenLedPinLeft = 12;
const int blueLedPinLeft = 13;
const int redLedPinRight = 2;
const int greenLedPinRight = 3;
const int blueLedPinRight = 8;

const int blinkingTime = 300;
int blinkingState = LOW;
unsigned long lastBlink = 0;

int m1Speed = 0;
int m2Speed = 0;

float kp = 20;
float ki = 0;
float kd = 8;

int p = 1;
int i = 0;
int d = 1;

int error = 0;
int lastError = 0;

// speeds
const int maxSpeed = 255;
const int minSpeed = -255;
const int baseSpeed = 235;

QTRSensors qtr;
byte calibrationState = 0;

const int sensorCount = 6;
int sensorValues[sensorCount];
int sensorReads[sensorCount];
int sensors[sensorCount] = {0, 0, 0, 0, 0, 0};

void setup() {
  // pinMode setup
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);

  // led  setup
  pinMode(redLedPinLeft, OUTPUT);
  pinMode(greenLedPinLeft, OUTPUT);
  pinMode(blueLedPinLeft, OUTPUT);
  pinMode(redLedPinRight, OUTPUT);
  pinMode(greenLedPinRight, OUTPUT);
  pinMode(blueLedPinRight, OUTPUT);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorCount);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

  calibrateSensors();

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  qtr.read(sensorValues);

  pidControl(kp, ki, kd);
 
  m1Speed = constrain(m1Speed, minSpeed, maxSpeed);
  m2Speed = constrain(m2Speed, minSpeed, maxSpeed);

  setMotorSpeed(m1Speed, m2Speed);
}

void pidControl(float kp, float ki, float kd) {
  
  int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -30, 30); 

  controlLights(error);
  
  p = error;
  i = i + error;
  d = error - lastError;

  lastError = error;

  int motorSpeed = kp * p + ki * i + kd * d;

  m1Speed = baseSpeed;
  m2Speed = baseSpeed;

  if (error < 0) {
    m1Speed += motorSpeed;
  }
  else if (error > 0) {
    m2Speed -= motorSpeed;
  }

  if(error < -20) {
    m2Speed -= 40;
  }
  else if(error > 20) {
    m1Speed -= 40;
  }
}

void setMotorSpeed(int motor1Speed, int motor2Speed) {
  if (motor1Speed == 0) {
    digitalWrite(m11Pin, LOW);
    digitalWrite(m12Pin, LOW);
    analogWrite(m1Enable, motor1Speed);
  }  else {
    if (motor1Speed > 0) {
      digitalWrite(m11Pin, HIGH);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    }
    if (motor1Speed < 0) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, HIGH);
      analogWrite(m1Enable, -motor1Speed);
    }
  }
  if (motor2Speed == 0) {
    digitalWrite(m21Pin, LOW);
    digitalWrite(m22Pin, LOW);
    analogWrite(m2Enable, motor2Speed);
  }
  else {
    if (motor2Speed > 0) {
      digitalWrite(m21Pin, HIGH);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    }
    if (motor2Speed < 0) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, HIGH);
      analogWrite(m2Enable, -motor2Speed);
    } 
  }
}

void controlLights(int error) {
  if (error > 5)  {
    digitalWrite(redLedPinRight, HIGH);
    digitalWrite(greenLedPinRight, HIGH);
    digitalWrite(blueLedPinRight, HIGH);

    if (millis() - lastBlink > blinkingTime) {
      digitalWrite(redLedPinLeft, blinkingState);
      digitalWrite(greenLedPinLeft, blinkingState);
      digitalWrite(blueLedPinLeft, blinkingState);
      blinkingState = !blinkingState;
      lastBlink = millis();
    }
  } else if (error < -5)  {
    digitalWrite(redLedPinLeft, HIGH);
    digitalWrite(greenLedPinLeft, HIGH);
    digitalWrite(blueLedPinLeft, HIGH);

    if (millis() - lastBlink > blinkingTime) {
      digitalWrite(redLedPinRight, blinkingState);
      digitalWrite(greenLedPinRight, blinkingState);
      digitalWrite(blueLedPinRight, blinkingState);
      blinkingState = !blinkingState;
      lastBlink = millis();
    }
  } else {
    digitalWrite(redLedPinRight, HIGH);
    digitalWrite(greenLedPinRight, HIGH);
    digitalWrite(blueLedPinRight, HIGH);
    digitalWrite(redLedPinLeft, HIGH);
    digitalWrite(greenLedPinLeft, HIGH);
    digitalWrite(blueLedPinLeft, HIGH);
  }
}
 
void calibrateSensors() {
  int passes = 0;
  int calibrationSpeed = 200;

  while (passes < 7) {
    qtr.calibrate();
    qtr.read(sensorReads);

    if (calibrationState == 0) {
      if (sensorReads[0] < 500) {
        setMotorSpeed(calibrationSpeed, -calibrationSpeed);
      } else {
        calibrationState = 1;
      }
    } else {
      if (sensorReads[5] < 500) {
        setMotorSpeed(-calibrationSpeed, calibrationSpeed);
      } else {
        calibrationState = 0;
        passes ++;
      }
    }
  }
}
 
