

int max_speed =50;
int half_speed = 25;
// MOTOR DRIVER ( MD_ )
#define MD_ENA 5     // MOTOR 1 - MD_ENABLE
#define MD_ENB 6     // MOTOR 2 - MD_ENABLE

#define MD_IN1 7     // MOTOR 1 - PIN 1
#define MD_IN2 8     // MOTOR 1 - PIN 2
#define MD_IN3 9     // MOTOR 2 - PIN 1
#define MD_IN4 11    // MOTOR 2 - PIN 2
 
// ULTRASONIC ( US_ )
int US_trig_pin = A5;    //Trig 
int US_echo_pin = A4;    //Echo 

void initialize_motor_controls()
{
  pinMode(MD_IN1, OUTPUT);   
  pinMode(MD_IN2, OUTPUT);   
  pinMode(MD_IN3, OUTPUT);   
  pinMode(MD_IN4, OUTPUT);   
  pinMode(MD_ENA, OUTPUT);   
  pinMode(MD_ENB, OUTPUT);   
  digitalWrite(MD_ENA, HIGH);  
  digitalWrite(MD_ENB, HIGH); 
}

void initialize_ultrasonic()
{
  pinMode(US_trig_pin, OUTPUT);
  pinMode(US_echo_pin, INPUT);
}

long get_distance()
{
  long duration, cm=0;
  digitalWrite(US_trig_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(US_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_trig_pin, LOW);
  pinMode(US_echo_pin, INPUT);
  duration = pulseIn(US_echo_pin, HIGH);
  cm = (duration/2) / 29.1;
  return cm;
}

void robo_move_forward(int robo_speed)
{
    digitalWrite(MD_IN1, HIGH);
    digitalWrite(MD_IN2, LOW);

    digitalWrite(MD_IN3, LOW);
    digitalWrite(MD_IN4, HIGH);
    
    int ms1 = ((float)(robo_speed /100) * 255);
    analogWrite(MD_ENA, ms1);
    analogWrite(MD_ENB, ms1);
}


void robo_move_backward(int robo_speed)
{

    digitalWrite(MD_IN1, LOW);
    digitalWrite(MD_IN2, HIGH);

    digitalWrite(MD_IN3, HIGH);
    digitalWrite(MD_IN4, LOW);
    
    int ms1 = ((float)(robo_speed /100) * 255);
    analogWrite(MD_ENA, ms1);
    analogWrite(MD_ENB, ms1);
}

void robo_stop()
{
  digitalWrite(MD_IN1, LOW);
  digitalWrite(MD_IN2, LOW);
  
  digitalWrite(MD_IN3, LOW);
  digitalWrite(MD_IN4, LOW);
  analogWrite(MD_ENA, 0);
  analogWrite(MD_ENB, 0);
}
 
void setup() 
{
  initialize_motor_controls();
  initialize_ultrasonic();
  Serial.begin(9600);
  robo_move_forward(max_speed);
} 
 
void loop()
{
  long duration, cm=0;
  digitalWrite(US_trig_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(US_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_trig_pin, LOW);
  pinMode(US_echo_pin, INPUT);
  duration = pulseIn(US_echo_pin, HIGH);
  cm = (duration/2) / 29.1;
  Serial.print("distance ");
  Serial.println(cm);
  if(cm >= 400 || cm <= 2){
    Serial.println("NOT ACTION TAKEN AS IT IS OUT OF RANGE");
  }
  else if(cm > 50)
  {
    Serial.println("MOVES FORWARD AT 100 % SPEED");
    robo_move_forward(max_speed);
  }
  else if( 20 < cm < 50 )
  {
    Serial.print("MOVES FORWARD AT 50 % SPEED");
    robo_move_forward(half_speed);
  }
  
  else
  {
    Serial.println("STOPS");
    robo_stop();
  }
  delay(250);
}
