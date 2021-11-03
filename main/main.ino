/*
Executes main program for course navigation.

Program runs setup() once for board configuration, which calls search_and_rescue() that runs program loop.
*/

float SLOW_TURN_SPEED = 0.3*255;
float SLOW_SPEED = 0.1*255;
  
// Delay 100ms
float TIME_DELAY = 100;

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
    int ir_1_pin, ir_2_pin, ir_3_pin, ir_blue_pin;
  	int ir_1_status, ir_2_status, ir_3_status, ir_blue_status;
  
  // Constructor
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
    int ir_3_pin,
    int ir_blue_pin
    ){
      this->motor_a_forwards = motor_a_forwards;
      this->motor_a_backwards = motor_a_backwards;
      this->motor_a_speed = 0;
      pinMode(motor_a_forwards, OUTPUT);
      pinMode(motor_a_backwards, OUTPUT);
      pinMode(motor_a_speed, OUTPUT);
      
      this->motor_b_forwards = motor_b_forwards;
      this->motor_b_backwards = motor_b_backwards;
      this->motor_b_speed = 0;
      pinMode(motor_b_forwards, OUTPUT);
      pinMode(motor_b_backwards, OUTPUT);
      pinMode(motor_b_speed, OUTPUT);
      
      this->motor_c_forwards = motor_c_forwards;
      this->motor_c_backwards = motor_c_backwards;
      this->motor_c_speed = 0;
      pinMode(motor_c_forwards, OUTPUT);
      pinMode(motor_c_backwards, OUTPUT);
      pinMode(motor_c_speed, OUTPUT);
      
      this->motor_d_forwards = motor_d_forwards;
      this->motor_d_backwards = motor_d_backwards;
      this->motor_d_speed = 0;
      pinMode(motor_d_forwards, OUTPUT);
      pinMode(motor_d_backwards, OUTPUT);
      pinMode(motor_d_speed, OUTPUT);
      
      this->ir_1_pin = ir_1_pin;
      pinMode(ir_1_pin, INPUT);
      this->ir_2_pin = ir_2_pin;
      pinMode(ir_2_pin, INPUT);
      this->ir_3_pin = ir_3_pin;
      pinMode(ir_3_pin, INPUT);
    	this->ir_blue_pin = ir_blue_pin;
  }
  
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
  }
  
  void turn_motor_off(int motor_x_forwards, int motor_x_backwards, int motor_x_speed){
    digitalWrite(motor_x_forwards, LOW);
    digitalWrite(motor_x_backwards, LOW);
    analogWrite(motor_x_speed, 0);
  }
  
  void turn_off_all_motors(){
    turn_motor_off(motor_a_forwards, motor_a_backwards, motor_a_speed);
    turn_motor_off(motor_b_forwards, motor_b_backwards, motor_b_speed);
    turn_motor_off(motor_c_forwards, motor_c_backwards, motor_c_speed);
    turn_motor_off(motor_d_forwards, motor_d_backwards, motor_d_speed);
  }
  
  void read_sensors(){
    ir_1_status = bool(digitalRead(ir_1_pin));
    ir_2_status = bool(digitalRead(ir_2_pin));
    ir_3_status = bool(digitalRead(ir_3_pin));
    
    ir_blue_status = bool(digitalRead(ir_blue_pin));
  }

};

void search_and_rescue(Robot robot){
	float counter = 0.0;
  bool rescued = false;
  
  while(true){
    // Set course correction counter to 0
    counter = 0;
    
    // Get sensor readings
    robot.read_sensors();
    
    // Case for when blue detected and !rescued
    if (robot.ir_blue_status and !rescued){
      // slow speed
      robot.set_motor_power(robot.motor_a_forwards, robot.motor_a_backwards, robot.motor_a_speed, SLOW_SPEED, true);
      robot.set_motor_power(robot.motor_b_forwards, robot.motor_b_backwards, robot.motor_b_speed, SLOW_SPEED, true);
      robot.set_motor_power(robot.motor_c_forwards, robot.motor_c_backwards, robot.motor_c_speed, SLOW_SPEED, true);
      robot.set_motor_power(robot.motor_d_forwards, robot.motor_d_backwards, robot.motor_d_speed, SLOW_SPEED, true);

      // Loop while blue seen
      while(robot.ir_blue_status){
      	robot.read_sensors();
      }

      // Loop while blue not seen
      while(not robot.ir_blue_status){
      	robot.read_sensors();
      }
      
      // move in reverse
      robot.set_motor_power(robot.motor_a_forwards, robot.motor_a_backwards, robot.motor_a_speed, SLOW_SPEED, false);
      robot.set_motor_power(robot.motor_b_forwards, robot.motor_b_backwards, robot.motor_b_speed, SLOW_SPEED, false);
      robot.set_motor_power(robot.motor_c_forwards, robot.motor_c_backwards, robot.motor_c_speed, SLOW_SPEED, false);
      robot.set_motor_power(robot.motor_d_forwards, robot.motor_d_backwards, robot.motor_d_speed, SLOW_SPEED, false);

      // Loop while blue seen
      while(robot.ir_blue_status){
      	robot.read_sensors();
      }

      // Loop while blue not seen
      while(not robot.ir_blue_status){
      	robot.read_sensors();
      }
      
      delay(TIME_DELAY);
      
      // turn robot around
      robot.set_motor_power(robot.motor_a_forwards, robot.motor_a_backwards, robot.motor_a_speed, SLOW_SPEED, true);
      robot.set_motor_power(robot.motor_b_forwards, robot.motor_b_backwards, robot.motor_b_speed, SLOW_SPEED, true);
      robot.set_motor_power(robot.motor_c_forwards, robot.motor_c_backwards, robot.motor_c_speed, SLOW_SPEED, false);
      robot.set_motor_power(robot.motor_d_forwards, robot.motor_d_backwards, robot.motor_d_speed, SLOW_SPEED, false);
      
      // Loop while red seen
      while(robot.ir_2_status){
        robot.read_sensors();
      }
    	
      // Loop while red not seen
      while(not robot.ir_2_status){
        robot.read_sensors();
      }
      
      rescued = true;
    }
    else{
      // All sensors red, exit condition
      if (robot.ir_1_status and robot.ir_2_status and robot.ir_3_status){
        robot.turn_off_all_motors();
        break;
      }
      
      // Right sensor red
      if (robot.ir_3_status){
        counter += 255;
      }
      
      // Left sensor red
      if (robot.ir_1_status){
        counter -= 255;
      }
      
      // Middle sensor red
      if (robot.ir_2_status){
        counter /= 2;
      }
      
      if (counter == 0){
        // Drive straight
        robot.set_motor_power(robot.motor_a_forwards, robot.motor_a_backwards, robot.motor_a_speed, counter, true);
        robot.set_motor_power(robot.motor_b_forwards, robot.motor_b_backwards, robot.motor_b_speed, counter, true);
        robot.set_motor_power(robot.motor_c_forwards, robot.motor_c_backwards, robot.motor_c_speed, counter, true);
        robot.set_motor_power(robot.motor_d_forwards, robot.motor_d_backwards, robot.motor_d_speed, counter, true);
      }
      else if (counter < 0){
        // Turn left
        robot.set_motor_power(robot.motor_a_forwards, robot.motor_a_backwards, robot.motor_a_speed, SLOW_TURN_SPEED, true);
        robot.set_motor_power(robot.motor_b_forwards, robot.motor_b_backwards, robot.motor_b_speed, counter, true);
        robot.set_motor_power(robot.motor_c_forwards, robot.motor_c_backwards, robot.motor_c_speed, SLOW_TURN_SPEED, true);
        robot.set_motor_power(robot.motor_d_forwards, robot.motor_d_backwards, robot.motor_d_speed, counter, true);
      }
      else if (counter > 0){
      	// Turn right
        robot.set_motor_power(robot.motor_a_forwards, robot.motor_a_backwards, robot.motor_a_speed, counter, true);
        robot.set_motor_power(robot.motor_b_forwards, robot.motor_b_backwards, robot.motor_b_speed, SLOW_TURN_SPEED, true);
        robot.set_motor_power(robot.motor_c_forwards, robot.motor_c_backwards, robot.motor_c_speed, counter, true);
        robot.set_motor_power(robot.motor_d_forwards, robot.motor_d_backwards, robot.motor_d_speed, SLOW_TURN_SPEED, true);
      }
      
      delay(TIME_DELAY);
    }
  }
}

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
  int ir_blue_pin = 0;
  
  // Create instance of Robot
  Robot robot(maf, mab, mbf, mbb, mcf, mcb, mdf, mdb, ir_1_pin, ir_2_pin, ir_3_pin, ir_blue_pin);
  
  search_and_rescue(robot);
}

void loop() {
  exit(0);
}
