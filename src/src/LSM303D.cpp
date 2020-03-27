
#include "LSM303D.h"
#include "l3gd20h.h"
#include <Wire.h>
#include <math.h>

vector<int16_t> m_min = {-190, -850, +3460}, m_max = {+2100, +1280, +3800};
vector<float> a_bias = {0,0,0};
float origin_from_N = 0;
vector<float> angles= {0,0,0};


void writeReg(byte reg, byte value)
{
  Wire.beginTransmission(ACCEL_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void acc_mag_set_default()
{
  //Accelerometer
  //defaults
  writeReg(0x21, 0x00);

  // 0x57 = 0b01010111
  // AODR = 1000(400 Hz ODR); AZEN = AYEN = AXEN = 1 (all axes enabled)
  writeReg(0x20, 0x87);

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
   

  return_vec.x = (float)((xh << 8) + xl)*0.061/1000.-a_bias.x;
  return_vec.y = (float)((yh << 8) + yl)*0.061/1000.-a_bias.y;
  return_vec.z = (float)((zh << 8) + zl)*0.061/1000.; //bias not wanted because of gravity
  return return_vec;
}

float accel_get_avg_speed(float sec, float step)
{
  if(step >= sec)
    return -1.0;
  vector<float> speedXY = {0,0,0};
  int steps = (int)sec/step;
  vector<float> vals; 
  //double speed = 0;
  unsigned long time = millis();
  for(int i = 0; i < steps; i++)
  {
    vals = accel_get_values(); //values in g, g = 9.8 m/s**2
    //speed += sqrt(pow(vals.x*G*(step/1000),2)+pow(vals.y*G*(step/1000),2));
    speedXY.x +=  vals.x*G*(step/1000);
    speedXY.y += vals.y*G*(step/1000);
     /*speed in z axis is ignored hence it would be gravity :)*/
    //delay(90);
    while(millis()-time < step); //active waiting
    time = millis();
  }

  //speedXY.x /= steps;
  //speedXY.y /= steps;
  //return speedXY.x;
  double num = speedXY.x*speedXY.x + speedXY.y+speedXY.y;
  //return (float)num;
  double speed = sqrt(abs(num));
  return (float) speed;
}

vector<int16_t> mag_get_values()
{
  vector<int16_t> return_vec;

  Wire.beginTransmission(MAG_ADRESS);
  Wire.write(OUT_X_L_M | (1 << 7)); // horni bit 1 a pak 7-bit adresa registru 0x28
  Wire.endTransmission();

  Wire.requestFrom(MAG_ADRESS, 6);
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


void acc_get_bias()
{
  delay(50);
  vector<float> vals = {0,0,0};
  for(int i = 0; i < 25; i++)
  {
    vector<float> temp = accel_get_values();
    vals.x += temp.x;
    vals.y += temp.y;
    vals.z += temp.z;
    
    delay(5);
  }
  a_bias.x = vals.x/25.;
  a_bias.y = vals.y/25.;
}


void mag_get_default_vector()
{ 
  origin_from_N = heading(mag_get_values(), accel_get_values());
}

float get_origin()
{
  return origin_from_N;
}





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

/*Zjednoduseni funkce z navodu od Pololu values = z mag, a = z accel*/
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


vector<float> get_position()
{
  vector<float> ret = {angles.x, angles.y, angles.z};
  return ret;
}

void update_position_euler()
{
  static double q[4] = {0,0,0,1};
  static unsigned long last_called = millis();
  double dt = (millis()-last_called)/1000.;
  //Serial.println(dt);
  last_called = millis();
  vector<float> gyro_data = gyro_normalize(gyro_get_values());
  gyro_data.x *= (PI/180);
  gyro_data.y *= (PI/180);
  gyro_data.z *= (PI/180);

  q[0] += ((-q[1]*gyro_data.x - q[2]*gyro_data.y - q[3]*gyro_data.z)/2)*dt;
  q[1] += ((+q[0]*gyro_data.x + q[2]*gyro_data.z - q[3]*gyro_data.y)/2)*dt;
  q[2] += ((+q[0]*gyro_data.y - q[1]*gyro_data.z + q[3]*gyro_data.x)/2)*dt;
  q[3] += ((+q[0]*gyro_data.z + q[1]*gyro_data.y - q[2]*gyro_data.x)/2)*dt;

  /*for (int i = 0; i < 4; i++)
  {
    Serial.print(q[i]);
    Serial.print(" ");
  }
  Serial.println("");*/
  double norm = sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
  for (int i = 0; i < 4; i++)
  {
    q[i] /= norm;
  }
  double X = atan2(2*q[2]*q[3]+2*q[0]+q[1],pow(q[3],2)-pow(q[2],2)-pow(q[1],2)+pow(q[0],2));
  double Y = -asin(2*q[1]*q[3]-2*q[0]*q[2]);
  double Z = atan2(2*q[1]*q[2]+2*q[0]*q[3],pow(q[1],2)+pow(q[0],2)-pow(q[3],2)-pow(q[2],2));

  angles.x = X;
  angles.y = Y;
  angles.z = Z;
}




void update_position_simple()
{
  static unsigned long last_called = millis();
  static float last_vertical_position = 0.98; // +-= 1 g

  vector<float> gyro_data = gyro_normalize(gyro_get_values());
  vector<float> check = accel_get_values();
  double step = (millis()-last_called);
  last_called = millis();
  /* 
   * This prevents to integrate small values when robot is still but
   * gyro gives small err values - better to have something to reduce noise. 
   * 
   * Accelerometer vertical position is very still with error under 1 %, so the
   * differece between last vertical position and the current one is used to check if 
   * robot is actually moving or not. 
  */
  if(abs(check.z-last_vertical_position) > 2) 
  {
    last_vertical_position = check.z;
    angles.x += step/1000.*gyro_data.x;
    angles.y += step/1000.*gyro_data.y;
  }
  /*Z angle - yaw - computed from magnetometer = compass*/
  angles.z = heading(mag_get_values(), accel_get_values())-get_origin();

}