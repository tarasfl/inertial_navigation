#include <Wire.h>

const int MPU = 0x68;
float AccX, AccY, AccZ;
float kalmanGain = 0.2;
float current_az;
float previous_az =16384.0;

void setup() 
{
  Serial.begin(19200);
  Wire.begin();                    
  Wire.beginTransmission(MPU);   
  Wire.write(0x6B);               
  Wire.write(0x00);             
  Wire.endTransmission(true);    
  delay(20);

}

void loop() 
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0;
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0;
  AccZ = (Wire.read() << 8 | Wire.read()) ;
 
 // Serial.println(AccX);
  Serial.print(AccZ);
  Serial.print("   ");
  Serial.println(kalmanFilter());
}
int kalmanFilter(){
    current_az = previous_az + kalmanGain*(AccZ-previous_az);
    return current_az;
}
