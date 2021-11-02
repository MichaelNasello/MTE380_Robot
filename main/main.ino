/*
Executes main program for course navigation.

Program runs setup() once for board configuration, and continually runs loop() until exit conditions.
*/

class Robot{
  /*
  Motor Config
  
  Motor A: Front Left
  Motor B: Front Right
  Motor C: Back Left
  Motor D: Back Right
  
  Each motor is assigned two pins, (motor_x_forward, motor_x_backwards) and an analog speed motor_x_speed (0-255).
  */
  public:
    int motor_a_forwards, motor_a_backwards, motor_a_speed;
    int motor_b_forwards, motor_b_backwards, motor_b_speed;
    int motor_c_forwards, motor_c_backwards, motor_c_speed;
    int motor_d_forwards, motor_d_backwards, motor_d_speed;
  
  /* 
  IR sensor config
  
  When looking forwards from the perspective of the robot, IR sensors are labelled one through three from left to right.
  
  Each sensor is assigned a pin, ir_x_pin. The sensors return int(boolean) for colour detection. The tolerances for sensor
  output are physically tuned.
  
  */
  public:
    int ir_1_pin, ir_2_pin, ir_3_pin;
    int ir_vcc, ir_ground;
  
  // Constructor
  public:
    Robot(
      int motor_a_forward, 
      int motor_a_backwards, 
      int motor_b_forward, 
      int motor_b_backwards,
      int motor_c_forward, 
      int motor_c_backwards,
      int motor_d_forward, 
      int motor_d_backwards,
      int ir_1_pin,
      int ir_2_pin,
      int ir_3_pin
      ){
        motor_a_forwards = motor_a_forwards;
        motor_a_backwards = motor_a_backwards;
        motor_a_speed = 0;
        pinMode(motor_a_forwards, OUTPUT);
        pinMode(motor_a_backwards, OUTPUT);
        pinMode(motor_a_speed, OUTPUT);
        
        motor_b_forwards = motor_b_forwards;
        motor_b_backwards = motor_b_backwards;
        motor_b_speed = 0;
        pinMode(motor_b_forwards, OUTPUT);
        pinMode(motor_b_backwards, OUTPUT);
        pinMode(motor_b_speed, OUTPUT);
        
        motor_c_forwards = motor_c_forwards;
        motor_c_backwards = motor_c_backwards;
        motor_c_speed = 0;
        pinMode(motor_c_forwards, OUTPUT);
        pinMode(motor_c_backwards, OUTPUT);
        pinMode(motor_c_speed, OUTPUT);
        
        motor_d_forwards = motor_d_forwards;
        motor_d_backwards = motor_d_backwards;
        motor_d_speed = 0;
        pinMode(motor_d_forwards, OUTPUT);
        pinMode(motor_d_backwards, OUTPUT);
        pinMode(motor_d_speed, OUTPUT);
        
        ir_1_pin = ir_1_pin;
        pinMode(ir_1_pin, INPUT);
        ir_2_pin = ir_2_pin;
        pinMode(ir_2_pin, INPUT);
        ir_3_pin = ir_3_pin;
        pinMode(ir_3_pin, INPUT);
    };
  
  // Methods
  void set_motor_power(int motor_x_forwards, int motor_x_backwards, int motor_x_speed, int speed, bool forwards){
    if (forwards){
      digitalWrite(motor_x_forwards, HIGH);
      digitalWrite(motor_x_backwards, LOW);
      analogWrite(motor_x_speed, speed);
    }
    else{
      digitalWrite(motor_x_forwards, LOW);
      digitalWrite(motor_x_backwards, HIGH);
      analogWrite(motor_x_speed, speed);
    }
  };
  
  void turn_motor_off(int motor_x_forwards, int motor_x_backwards, int motor_x_speed){
    digitalWrite(motor_x_forwards, LOW);
    digitalWrite(motor_x_backwards, LOW);
    analogWrite(motor_x_speed, 0);
  };
  
  bool* read_sensors(int ir_1_pin, int ir_2_pin, int ir_3_pin){
    bool ir_status[3];
    
    /*bool ir_1_status = bool(digitalRead(ir_1_pin));
    bool ir_2_status = bool(digitalRead(ir_2_pin));
    bool ir_3_status = bool(digitalRead(ir_3_pin));*/
    
    ir_status[0] = bool(digitalRead(ir_1_pin));
    ir_status[1] = bool(digitalRead(ir_2_pin));
    ir_status[2] = bool(digitalRead(ir_3_pin));
    
    return ir_status;
  };

};

void setup() {
  // Set baud rate
  Serial.begin(9600);
  
  // Robot config parameters, adjust later
  int maf = 0;
  int mab = 0;
  int mbf = 0;
  int mbb = 0;
  int mcf = 0;
  int mcb = 0;
  int mdf = 0;
  int mdb = 0;
  
  int ir_1_pin = 0;
  int ir_2_pin = 0;
  int ir_3_pin = 0;
  
  // Create instance of Robot
  Robot robot(maf, mab, mbf, mbb, mcf, mcb, mdf, mdb, ir_1_pin, ir_2_pin, ir_3_pin);
}

void loop() {
  
}
