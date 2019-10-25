#define LEFT -1
#define BOTH 0
#define RIGHT 1

#define DEG 0
#define CM 1

#define WHEEL_CIRCUIT 27.9

#define DIR_BACK 0 
#define DIR_FORW 1 

#define VEL_NONE 0
#define VEL_HALF 50
#define VEL_FULL 100
 
int A_old_left = 0;
int B_old_left = 0;
int A_new_left = 0;
int B_new_left = 0;
int counter_left = 0;

int A_old_right = 0;
int B_old_right = 0;
int A_new_right = 0;
int B_new_right = 0;
int counter_right = 0;

int motor_right = 7;
int motor_left = 6;

void set_counter(int dir)
{
  if(dir == RIGHT || dir == BOTH)
  {
    counter_right = 0;
  }
  if (dir == LEFT || dir == BOTH)
  {
    counter_left = 0; 
  }
}

bool is_equal(int a, int b)
{
  if(abs(a-b) < 20) 
    return true; 
  else
    return false ; //quite big tolerance
}
  
void wait_until_done(int motor, int steps)
{
 if(motor == RIGHT)
 {
  while(!is_equal(counter_right, steps))
  {
    A_new_right = digitalRead(50);
    B_new_right = digitalRead(52);
    if(A_new_right != A_old_right || B_new_right != B_old_right)
    {
      A_old_right = A_new_right;
      B_old_right = B_new_right;
      counter_right++;
    }
  }
 }
 else if (motor == LEFT)
 {
    while(counter_left != steps)
    {
      A_new_left = digitalRead(51);
      B_new_left = digitalRead(53);
      if(A_new_left != A_old_left || B_new_left != B_old_left)
      {
        A_old_left = A_new_left;
        B_old_left = B_new_left;
        counter_left++;
      }
    }
 }
 else if (motor == BOTH)
 {
  while(counter_right != steps || counter_right != steps)
  {
    A_new_right = digitalRead(50);
    B_new_right = digitalRead(52);
    A_new_left = digitalRead(51);
    B_new_left = digitalRead(53);
    if(A_new_right != A_old_right || B_new_right != B_old_right)
    {
      A_old_right = A_new_right;
      B_old_right = B_new_right;
      counter_right++;
    }
    if(A_new_left != A_old_left || B_new_left != B_old_left)
     {
       A_old_left = A_new_left;
       B_old_left = B_new_left;
       counter_left++;
     }
  }
 }
 return;
}


void execute_move(int motor, int steps, int velocity)
{
  Serial.print("***Function execute_move\n");
  switch(motor){
    case BOTH:
      set_counter(BOTH); 
      analogWrite(motor_right, velocity);
      analogWrite(motor_left, velocity);
      wait_until_done(BOTH, steps);
      analogWrite(motor_right, 145);
      analogWrite(motor_left, 145);
      set_counter(BOTH);
      break;
    case RIGHT:
      Serial.print("motor is set to RIGHT \n");
      set_counter(RIGHT);   
      analogWrite(motor_right, velocity);
      wait_until_done(RIGHT, steps);
      analogWrite(motor_right, 145);
      set_counter(RIGHT);
      break;
    case LEFT:
     Serial.print("motor is set to LEFT \n");
     set_counter(LEFT);
     analogWrite(motor_left, velocity);
     wait_until_done(LEFT, steps);
     analogWrite(motor_left, 145);
     set_counter(LEFT);
     break;
    default:
      break;
  }
  Serial.print("***Function execute_move - end\n");
  return;
}

/**
 * 
 */
int move(int wheel, int unit, int value, int dir, int velocity)
{
  Serial.print("***Function move.\n");
  int steps = 0;
  if(unit == CM)
  {
    Serial.print("Units: cm.\n");
    steps = (int) (value / WHEEL_CIRCUIT * 3072);    
  }
  else if(unit == DEG)
  {    
    Serial.print("Units: degrees.\n");
    steps = (int) ((40 * PI * value / 360) / WHEEL_CIRCUIT * 3072);
  }
  Serial.print("Steps are set to: ");
  Serial.print(steps);
  Serial.print("\n");
  int velocity_in_range = 127;
  if(dir == DIR_FORW)
  {
    velocity_in_range += (int) (velocity / 100. * 127);  //dot to force float division
  }
  else if (dir == DIR_BACK)
  {
    velocity_in_range -= (int)(velocity / 100. * 127);
  }
  Serial.print("Velocity in percent: ");
  Serial.print(velocity);
  Serial.print("%\n");
  Serial.print("Velocity in range <0,255>: ");
  Serial.print(velocity_in_range);
  Serial.print("\n");
  //TODO ochrana při malickych rychlostech
  execute_move(wheel, steps, velocity_in_range);
  Serial.print("***Function move - end.\n");
  return steps;
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(50, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(52, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);
  
  pinMode(motor_left, OUTPUT);
  pinMode(motor_right, OUTPUT);
  
}


void loop() {
  analogWrite(motor_right,145);
  analogWrite(motor_left,145);
   delay(2000);
   move(BOTH, CM, 20, DIR_FORW, 75); 
   move(LEFT, DEG, 90, DIR_FORW, VEL_HALF); 
    move(BOTH, CM, 20, DIR_FORW, 75); 
   move(LEFT, DEG, 90, DIR_FORW, VEL_HALF); 
    move(BOTH, CM, 20, DIR_FORW, 75); 
   move(LEFT, DEG, 90, DIR_FORW, VEL_HALF); 
    move(BOTH, CM, 20, DIR_FORW, 75); 
   move(LEFT, DEG, 90, DIR_FORW, VEL_HALF); 
   delay(5000);
}
