#include "magnetometer.h"
#include "I2C.h"
#include "vectors.h"
Magnetometer::Magnetometer(Accelerometer *accel, byte address)
{
    this->mag_address = address;
    // 0x64 = 0b01100100
    // M_RES = 11 (high resolution mode); M_ODR = 001 (6.25 Hz ODR)
    reg_write(this->mag_address, 0x24, 0x64);

    // 0x20 = 0b00100000  
    // MFS = 01 (+/- 4 gauss full scale)
    reg_write(this->mag_address, 0x25, 0x20);

    // 0x00 = 0b00000000
    // MLP = 0 (low power mode off); MD = 00 (continuous-conversion mode)
    reg_write(this->mag_address, 0x26, 0x00);

    //TODO
    /*Az bude fungovat get boundaries, odkomentovat*/
    //this->set_limits();
    this->mag_min = {-190, -850, +3460};
    this->mag_max = {+2100, +1280, +3800};
    this->set_origin_angle(accel);
}
void Magnetometer::set_origin_angle(Accelerometer *accel)
{
  this->origin_from_N = heading(accel);
}


/*Zjednoduseni funkce z navodu od Pololu values = z mag, a = z accel*/

float Magnetometer::heading(Accelerometer *accel)
{
  /*Udava, jaky smer je "predek" (osa X - prvni pozice). Jelikoz je pro lepsi pristup senzor "opacne", 
  je hodnota zaporna. */
  vector<int> front = {-1,0,0};

  vector<int16_t> mag_values = this->get_intensity();
  vector<float> accel_values = accel->get_acceleration();

  // subtract offset (average of min and max) from magnetometer readings
  mag_values.x -= ((int32_t)mag_min.x + mag_max.x) / 2;
  mag_values.y -= ((int32_t)mag_min.y + mag_max.y) / 2;
  mag_values.z -= ((int32_t)mag_min.z + mag_max.z) / 2;

  // compute E and N
  vector<float> E;
  vector<float> N;
  vector_cross(&mag_values, &accel_values, &E);
  vector_normalize(&E);
  vector_cross(&accel_values, &E, &N);
  vector_normalize(&N);


  float angle = acos(vector_dot(&N, &front)
                     /
                     (sqrt(vector_dot(&N, &N))*sqrt(vector_dot(&front, &front)))
                    )* 180 / PI;
  
  if(N.y < 0)
    angle = 360-angle;

  return angle;

}


void Magnetometer::set_limits()
{
  // TODO az bude tlacitko, tak zacit po zmacknuti - pocita se s pohybem
  int cnt = 0;
  while(cnt > 50)
  {
    vector <int16_t> vals = this->get_intensity();
    mag_min.x = min(mag_min.x, vals.x);
    mag_min.y = min(mag_min.y, vals.y);
    mag_min.z = min(mag_min.z, vals.z);

    mag_max.x = max(mag_max.x, vals.x);
    mag_max.y = max(mag_max.y, vals.y);
    mag_max.z = max(mag_max.z, vals.z);
    delay(20);
  }
}

vector<int16_t> Magnetometer::get_intensity()
{
  vector<int16_t> return_vec;

  Wire.beginTransmission(MAG_ADDRESS);
  Wire.write(OUT_X_L_M | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru 0x28
  Wire.endTransmission();

  Wire.requestFrom(MAG_ADDRESS, 6);
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
