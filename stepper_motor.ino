#include <AccelStepper.h>
#define PI 3.1415926535897932384626433832795
#define MOTOR_DIAMETER 18.46 //in mm, inner diameter where the belt rests.
AccelStepper stepper(1,2,4); //stepper(steppermotortype,stepPin,DirPin);
const int switch_one = 5; //pin for limit switch
long initial_homing=-1;  // Used to Home Stepper at startup
int stepper_direction = 0; //use -1 for ccw or 1 for cw

void setup(){
  Serial.begin(9600);
  stepper.setMaxSpeed(40);
  stepper.setSpeed(20);
  pinMode(switch_one,INPUT);
  Serial.print("Stepper is Homing....");
  while(digitalRead(switch_two)==LOW){
    stepper.moveTo(initial_homing);
    initial_homing++;
    stepper.run();
  }
  stepper.setCurrentPosition(0);  // Set the current position as zero for now
  initial_homing=-2;

  while (digitalRead(switch_two)==HIGH) { // Make the Stepper move CCW until the switch is deactivated
    stepper.moveTo(initial_homing);  
    stepper.run();
    initial_homing--;
  }
  Serial.print("Switch is:     ");Serial.println(digitalRead(switch_two));

  stepper.setCurrentPosition(0); //max distance is 1462 steps.

  Serial.print("Homing Complete, Position is: ");Serial.println(stepper.currentPosition());
  Serial.println(" ");
  // Print out Instructions on the Serial Monitor at Start
  Serial.println("Enter Travel distance (Positive for CW / Negative for CCW and Zero for back to Home): ");
}

void loop(){
  For the control of the positions using a limit switch input.
  while(true){
     if(digitalRead(switch_one)==HIGH){
        counter++;
        stepper.moveTo(counter*interval_step*stepper_direction);
        Serial.print("Counter Value is: ");Serial.println(counter);
     }
     while(stepper.distanceToGo()!=0){
          stepper.run();
          Serial.print("Current Position is: ");Serial.println(stepper.currentPosition());
     }
  }
}
