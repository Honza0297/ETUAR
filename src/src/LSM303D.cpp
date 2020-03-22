
#include "LSM303D.h"
#include <Wire.h>

void writeReg(byte reg, byte value)
{
  Wire.beginTransmission(ACCEL_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void set_default()
{
    writeReg(0x21, 0x00);

    // 0x57 = 0b01010111
    // AODR = 0101 (50 Hz ODR); AZEN = AYEN = AXEN = 1 (all axes enabled)
    writeReg(0x20, 0x57);

    // Magnetometer

    // 0x64 = 0b01100100
    // M_RES = 11 (high resolution mode); M_ODR = 001 (6.25 Hz ODR)
    writeReg(0x24, 0x64);

    // 0x20 = 0b00100000
    // MFS = 01 (+/- 4 gauss full scale)
    writeReg(0x25, 0x20);

    // 0x00 = 0b00000000
    // MLP = 0 (low power mode off); MD = 00 (continuous-conversion mode)
    writeReg(0x26, 0x00);
}

vector<float> accel_get_values()
{
  vector<float> return_vec;

  Wire.beginTransmission(ACCEL_ADDRESS);
  Wire.write(OUT_X_L_A | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru 0x28
  Wire.endTransmission();

  Wire.requestFrom(ACCEL_ADDRESS, (byte)6);
  while(Wire.available() < 6);
  
  int8_t xl = Wire.read();
  int8_t xh = Wire.read();
  
  int8_t yl = Wire.read();
  int8_t yh = Wire.read();
  
  int8_t zl = Wire.read();
  int8_t zh = Wire.read();
   

  return_vec.x = (float)((xh << 8) + xl)*0.061/1000.;
  return_vec.y = (float)((yh << 8) + yl)*0.061/1000.;
  return_vec.z = (float)((zh << 8) + zl)*0.061/1000.;
  return return_vec;
}

vector<int16_t> mag_get_values()
{
  vector<int16_t> return_vec;

  Wire.beginTransmission(MAG_ADRESS);
  Wire.write(OUT_X_L_M | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru 0x28
  Wire.endTransmission();

  Wire.requestFrom(MAG_ADRESS, (byte)6);
  while(Wire.available() < 6);
  
  int8_t xl = Wire.read();
  int8_t xh = Wire.read();
  
  int8_t yl = Wire.read();
  int8_t yh = Wire.read();
  
  int8_t zl = Wire.read();
  int8_t zh = Wire.read();
   

  return_vec.x = (int16_t)((xh << 8) + xl);
  return_vec.y = (int16_t)((yh << 8) + yl);
  return_vec.z = (int16_t)((zh << 8) + zl);
  return return_vec;
}

vector<int16_t> m_min = {-190, -850, +3460}, m_max = {+2100, +1280, +3800};

void mag_get_boundaries()
{
  // TODO az bude tlacitko, tak zacit po zmacknuti - pocita se s pohybem
  int cnt = 0;
  while(cnt > 50)
  {
    vector <int16_t> vals = mag_get_values();
    m_min.x = min(m_min.x, vals.x);
    m_min.y = min(m_min.y, vals.y);
    m_min.z = min(m_min.z, vals.z);

    m_max.x = max(m_max.x, vals.x);
    m_max.y = max(m_max.y, vals.y);
    m_max.z = max(m_max.z, vals.z);
    delay(20);
  }
  
}

/*Zjednoduseni funkce z navodu od Pololu*/
float heading(vector<int16_t> values, vector<float> a)
{
  vector<int> from = {-1,0,0};
    vector<int32_t> temp_m;
    temp_m.x = values.x;
    temp_m.y = values.y;
    temp_m.z = values.z;

    // subtract offset (average of min and max) from magnetometer readings
    temp_m.x -= ((int32_t)m_min.x + m_max.x) / 2;
    temp_m.y -= ((int32_t)m_min.y + m_max.y) / 2;
    temp_m.z -= ((int32_t)m_min.z + m_max.z) / 2;

    // compute E and N
    vector<float> E;
    vector<float> N;
    vector_cross(&temp_m, &a, &E);
    vector_normalize(&E);
    vector_cross(&a, &E, &N);
    vector_normalize(&N);

  
    float heading = acos(vector_dot(&N, &from)/(vector_dot(&N, &N)*vector_dot(&from, &from)))* 180 / PI;
    
    if(N.y < 0)
      heading = 360-heading; 

    return heading;
}

