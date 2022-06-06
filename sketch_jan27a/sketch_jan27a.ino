#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

const int MPU = 0x68;
float AccX, AccY, AccZ;
float kalmanGain = 0.2;

// x coordinates
float previous_ax = 0.0;
float previous_vx = 0.0;
float previous_x = 0.0;
float current_ax, current_vx, current_x;


// y coordinates
float previous_ay = 0.0;
float previous_vy = 0.0;
float previous_y = 0.0;
float current_ay, current_vy, current_y;

// z coordinates
float current_az;
float previous_az =16384.0;

void setup() 
{
  Serial.begin(19200);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);    
  delay(20);


}

void loop() 
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  AccX = a.acceleration.x;
  AccY = a.acceleration.y;
  AccZ = a.acceleration.z;

  Serial.print(getDistanceX());
  Serial.print(" ");
  Serial.println(AccX);
  
}
int kalmanFilterAx(){
    current_ax = previous_ax + kalmanGain*(AccX-previous_ax);
    return current_ax;
}

int getDistanceX(){
    
  current_vx = previous_vx + kalmanFilterAx();
  current_x = previous_x + current_vx;
  return current_x;
}
int kalmanFilterAy(){
    current_ay = previous_ay + kalmanGain*(AccY-previous_ay);
    return current_ax;
}

int getDistanceY(){
    
  current_vy = previous_vy + kalmanFilterAy();
  current_y = previous_y + current_vy;
  return current_y;
}
