#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

const int MPU = 0x68;
float AccX, AccY, AccZ;
float kalmanGain = 0.2;
float current_az, current_ax, current_vx, current_x;
float previous_ax = 0.0;
float previous_vx = 0.0;
float previous_x = 0.0;
float previous_az =16384.0;
float distance = 0;


void setup() 
{
  Serial.begin(19200);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
//  Wire.begin();                    
//  Wire.beginTransmission(MPU);   
//  Wire.write(0x6B);               
//  Wire.write(0x00);             
//  Wire.endTransmission(true);
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);    
  delay(20);


}

void loop() 
{
//  Wire.beginTransmission(MPU);
//  Wire.write(0x3B); 
//  Wire.endTransmission(false);
//  Wire.requestFrom(MPU, 6, true);
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  AccX = a.acceleration.x;
//  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0;
//  AccZ = (Wire.read() << 8 | Wire.read()) ;
 
 // Serial.println(AccX);
  current_vx = previous_vx + AccX;
  current_x = previous_x + current_vx;
  Serial.print(current_x);
  Serial.print(" ");
  Serial.println(AccX);
  
}
int kalmanFilter(){
    current_az = previous_az + kalmanGain*(AccZ-previous_az);
    return current_az;
}


int filterAx(){
    current_ax = previous_ax + kalmanGain*(AccX-previous_ax);
    return current_ax;  
}
