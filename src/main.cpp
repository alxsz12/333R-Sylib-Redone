#include "main.h"

//Start all of the tasks when we first start the program
DisplayControl def::display = DisplayControl(); 
pros::Task display_task(display_task_func);
pros::Task sm_dt_task(DrivetrainStateMachine::run);
pros::Task sm_fw_task(FlywheelStateMachine::run);
pros::Task sm_intake_task(IntakeStateMachine::run);
pros::Task sm_endgame_task(EndGameStateMachine::run);

/*\
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
\*/
void initialize()
{
	sylib::initialize(); // Initializes Sylib - Motor Controller

    EndGameStateMachine::setState(END_STATES::off);
    def::imu_top.reset();
    def::imu_side.reset();
    def::imu_back.reset();
    def::imu_fl.reset();
    def::imu_fr.reset();

    Auton::suspendAsyncTask();
    Auton::readSettings(); // read sd card to remember the auton selected when the brain was run last
    def::display.setAutonDropMen(); // update auton dropdown to match the sd card

    // Resetting and calibrating the encoder values of the internal motors
	def::mtr_dt_left_front.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    def::mtr_dt_left_mid.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    def::mtr_dt_right_front.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    def::mtr_dt_right_mid.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    def::mtr_dt_right_back.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    def::mtr_dt_left_back.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
}

/*\
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
\*/
void disabled() 
{
EndGameStateMachine::setState(END_STATES::off); //Putting the endgame off state where we need it 
}

/*\
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
\*/

void competition_initialize() {}

/*\
|*| Runs the user autonomous code. This function will be started in its own task
|*| with the default priority and stack size whenever the robot is enabled via
|*| the Field Management System or the VEX Competition Switch in the autonomous
|*| mode. Alternatively, this function may be called in initialize or opcontrol
|*| for non-competition testing purposes.
|*|
|*| If the robot is disabled or communications is lost, the autonomous task
|*| will be stopped. Re-enabling the robot will restart the task, not re-start it
|*| from where it left off.
\*/
void autonomous() 
{
    Auton::runAuton(); //Runs the selected auton code  
}

/*\
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
\*/
void opcontrol() 
{
    //def::flywheel.set_velocity_custom_controller(7200); //Motor Caps at 4200 RPM - HOW?
    sm_dt_task.resume(); // resumes the task from where it left off in case the robot loses connection
    
    // Then we can enable all of the controls for each of the different state machines below
    DrivetrainStateMachine::setState(DT_STATES::manual);
    DrivetrainStateMachine::enableControl();

    FlywheelStateMachine::enableControl();
    IntakeStateMachine::enableControl();
    EndGameStateMachine::enableControl();	   
}