#include "accelerometer.h"
#include "vectors.h"
#include "I2C.h"


vector<float> accel_bias = {0,0,0};

Accelerometer::Accelerometer(byte address)
{
    this->accel_address = address;
      //Accelerometer
  //defaults
  reg_write(address, 0x21, 0x00);

  // 0x57 = 0b01010111
  // AODR = 1000(400 Hz ODR); AZEN = AYEN = AXEN = 1 (all axes enabled)
  reg_write(address, 0x20, 0x87);

  this->set_bias();
}

void Accelerometer::set_bias()
{
  delay(10); //let things settle down a little bit...
  vector<int16_t> vals = {0,0,0};
  for(int i = 0; i < 25; i++)
  {
    vector<int16_t> temp = this->get_raw_data();
    vals.x += temp.x;
    vals.y += temp.y;
    vals.z += temp.z;
    
    delay(5);
  }
  accel_bias.x = vals.x/25;
  accel_bias.y = vals.y/25;
}

vector<int16_t> Accelerometer::get_raw_data()
{
   vector<int16_t> return_vec;

  Wire.beginTransmission(ACCEL_ADDRESS);
  Wire.write(OUT_X_L_A | (1 << 7)); // upper bit 1 & 7-bit address 0x28 to multibyte
  Wire.endTransmission();

  Wire.requestFrom(ACCEL_ADDRESS, 6);
  while(Wire.available() < 6);
  
  int8_t xl = Wire.read();
  int8_t xh = Wire.read();
  
  int8_t yl = Wire.read();
  int8_t yh = Wire.read();
  
  int8_t zl = Wire.read();
  int8_t zh = Wire.read();
   

  return_vec.x = (float)((xh << 8) + xl);
  return_vec.y = (float)((yh << 8) + yl);
  return_vec.z = (float)((zh << 8) + zl);
  return return_vec;
}

vector<float> Accelerometer::get_acceleration()
{
  vector<int16_t> raw_data = this->get_raw_data();
  vector<float> ret = {0,0,0};

  ret.x = (raw_data.x-accel_bias.x)*ACCEL_CONVERSION_RATE;
  ret.y = (raw_data.y-accel_bias.y)*ACCEL_CONVERSION_RATE;
  ret.z = (raw_data.z-accel_bias.z)*ACCEL_CONVERSION_RATE;

  return ret;
}