
#include "LSM303D.h"
#include "l3gd20h.h"
#include <Wire.h>
#include <math.h>

vector<int16_t> mag_min = {-190, -850, +3460}, mag_max = {+2100, +1280, +3800};
vector<float> a_bias = {0,0,0};
float origin_from_N = 0;
vector<float> angles= {0,0,0};

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
    mag_min.x = min(mag_min.x, vals.x);
    mag_min.y = min(mag_min.y, vals.y);
    mag_min.z = min(mag_min.z, vals.z);

    mag_max.x = max(mag_max.x, vals.x);
    mag_max.y = max(mag_max.y, vals.y);
    mag_max.z = max(mag_max.z, vals.z);
    delay(20);
  }
  
}

/*Zjednoduseni funkce z navodu od Pololu values = z mag, a = z accel*/
float heading(vector<int16_t> mag_values, vector<float> acc_values)
{
  /*Udava, jaky smer je "predek" (osa X - prvni pozice). Jelikoz je pro lepsi pristup senzor "opacne", 
  je hodnota zaporna. */
  vector<int> heading = {-1,0,0};

  /*vector<int32_t> temp_m;
  temp_m.x = mag_values.x;
  temp_m.y = mag_values.y;
  temp_m.z = mag_values.z;*/

  // subtract offset (average of min and max) from magnetometer readings
  mag_values.x -= ((int32_t)mag_min.x + mag_max.x) / 2;
  mag_values.y -= ((int32_t)mag_min.y + mag_max.y) / 2;
  mag_values.z -= ((int32_t)mag_min.z + mag_max.z) / 2;

  // compute E and N
  vector<float> E;
  vector<float> N;
  vector_cross(&mag_values, &acc_values, &E);
  vector_normalize(&E);
  vector_cross(&acc_values, &E, &N);
  vector_normalize(&N);


  float angle = acos(vector_dot(&N, &heading)
                     /
                     (sqrt(vector_dot(&N, &N))*sqrt(vector_dot(&heading, &heading)))
                    )* 180 / PI;
  
  if(N.y < 0)
    angle = 360-angle;

  return angle;
}


vector<float> get_position()
{
  vector<float> ret = {angles.x, angles.y, angles.z};
  return ret;
}
void ahrs_init()
{
  roll = 0;
  pitch = 0;
  yaw = 0;
}
void update_position_euler()
{
  static double time = millis();
  float g_roll = 0, g_pitch = 0, g_yaw = 0;
  static float am_roll = 0 , am_pitch = 0 , am_yaw = 0;
  static float am_roll_old = 0 , am_pitch_old = 0 , am_yaw_old = 0;
  float err_roll = 0, err_pitch = 0, err_yaw = 0;
  static float q[4] = {-1,0,0,0};

  float dt = (millis()-time)/1000;

  vector<float> accel = accel_get_values();
  vector<int16_t> mag = mag_get_values();
  vector<float> gyro = gyro_normalize(gyro_get_values());

  am_roll_old = am_roll;
  am_pitch_old = am_pitch;
  am_yaw_old = am_yaw;
  am_roll = atan2(accel.y,-accel.z)*ALPHA + am_roll_old*(1-ALPHA);
  am_pitch = atan2(-accel.x,sqrt(accel.y*accel.y + accel.z * accel.z))*ALPHA + (1-ALPHA)*am_pitch_old;
  am_yaw = -atan2((mag.x*sin(am_roll)*sin(am_pitch) + mag.y*cos(am_roll) + mag.z*sin(am_pitch)*sin(am_roll)),(mag.x*cos(am_roll) - mag.z*sin(am_roll)))*ALPHA + (1-ALPHA)*am_yaw_old;
  am_yaw = am_yaw < 0 ? 2*PI + am_yaw : am_yaw;
  
  gyro.x = TO_RAD(gyro.x);
  gyro.y = TO_RAD(gyro.y);
  gyro.z = TO_RAD(gyro.z);
 
 q[0] += ((-q[1]*gyro.x - q[2]*gyro.y - q[3]*gyro.z)/2)*dt;
 q[1] += ((+q[0]*gyro.x + q[2]*gyro.z - q[3]*gyro.y)/2)*dt;
 q[2] += ((+q[0]*gyro.y - q[1]*gyro.z + q[3]*gyro.x)/2)*dt;
 q[3] += ((+q[0]*gyro.z + q[1]*gyro.y - q[2]*gyro.x)/2)*dt;

 g_roll = atan2(2*(q[0]*q[1] + q[2]*q[3]), 1- 2*(q[1]*q[1] + q[2]*q[2]));
 g_pitch = asin(2*(q[3]*q[1] + q[2]*q[0]));//-asin(2*q[1]*q[3]-2*q[0]*q[2]);//
 g_yaw = atan2(2*q[1]*q[2]+2*q[0]*q[3],pow(q[1],2)+pow(q[0],2)-pow(q[3],2)-pow(q[2],2));//atan2(2*(q[0]*q[3] + q[2]*q[1]), 1- 2*(q[2]*q[2] + q[3]*q[3]));*/

  
  err_roll = K*(am_roll-g_roll);
  err_pitch = K*(am_pitch-g_pitch);
  err_yaw = K*(am_yaw-g_yaw);

  roll = TO_DEG(err_roll) > 10 ? g_roll : g_roll + err_roll;
  pitch = TO_DEG(err_pitch) > 10 ? g_pitch : g_pitch + err_pitch;
  yaw = TO_DEG(err_yaw) > 10 ? g_yaw : g_yaw + err_yaw;

  time = millis();
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