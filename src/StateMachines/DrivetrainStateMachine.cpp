/**
 * DrivetrainStateMachine.cpp
 *
 * This file contains the definitions of the DrivetrainStateMachine class.
 * DrivetrainStateMachine is a state machine that inherits from VStateMachine.
 * It has an enumeration of different possible states to make it easy for
 * the user to controll the drivetrain.
 *
 * To use the state machine in auton, you use doAutonMotion() to disable
 * the normal state machine tasks and run the specified action.
 */
#include "main.h" // gives access to DrivetrainStateMachine and other dependencies

/* ----------------------------------------------------------- */
/* -------------------------- State -------------------------- */
DT_STATES DrivetrainStateMachine::mstate = DT_STATES::off;
DT_STATES DrivetrainStateMachine::mlastState = mstate;

bool DrivetrainStateMachine::mcontrolEnabled = false;

bool DrivetrainStateMachine::stateChanged() // returns whether the last state is the same as the
                                            // current one
{
    if (mstate != mlastState)
    {
        return true;
    }
    return false;
}

/* ------------------------- Controls ------------------------ */
Controller &DrivetrainStateMachine::mcontroller = def::controller;

/* ----------------------------------------------------------- */
/*                      Public Information                     */
/* ----------------------------------------------------------- */
DT_STATES DrivetrainStateMachine::getState() { return mstate; }
void DrivetrainStateMachine::setState(DT_STATES istate)
{
    mlastState = mstate;
    mstate = istate;
}

void DrivetrainStateMachine::enableControl()
{
  mcontrolEnabled = true;
}

void DrivetrainStateMachine::disableControl()
{
  mcontrolEnabled = false;
}

void DrivetrainStateMachine::doAutonMotion(
    std::function<void()> iaction) // disable manual control, and execute the action
{
    DT_STATES oldState = mstate;
    setState(DT_STATES::busy);
    iaction();
    setState(oldState);
}

void DrivetrainStateMachine::imuCheck()
{
    while (def::imu_top.is_calibrating() || def::imu_side.is_calibrating() || def::imu_back.is_calibrating() || def::imu_fl.is_calibrating() || def::imu_fr.is_calibrating())
    {
        def::display.setInertialData(1, "IMU1: Is Calibrating");
        def::display.setInertialData(2, "IMU2: Is Calibrating");
        def::display.setInertialData(3, "IMU3: Is Calibrating");
        def::display.setInertialData(4, "IMU4: Is Calibrating");
        def::display.setInertialData(5, "IMU5: Is Calibrating");
    }
}

void DrivetrainStateMachine::controlState() // update the state based on controller input
{
}

void DrivetrainStateMachine::update() // move the robot based on the state
{
    switch (mstate)
    {
    case DT_STATES::off:
        break;
    case DT_STATES::busy:
        break;
    case DT_STATES::manual: // normal, arcade control
        Drivetrain::moveArcade(mcontroller.getAnalog(ControllerAnalog::leftY), 
         controlAdjust(mcontroller.getAnalog(ControllerAnalog::rightX), 2), 
         false);
       
        break;
    }
}

void DrivetrainStateMachine::run()
{
  while (true)
  {
        //Graph Data
        //def::display.setChartData(0, def::mtr_dt_left_front.getActualVelocity() - 150);
        //def::display.setChartData(1, def::mtr_dt_left_mid.getActualVelocity() - 150);
        //def::display.setChartData(2, def::mtr_dt_left_back.getActualVelocity() - 150);
        //def::display.setChartData(3, def::mtr_dt_right_front.getActualVelocity() - 150);
        //def::display.setChartData(4, def::mtr_dt_right_mid.getActualVelocity() - 150);
        //def::display.setChartData(5, def::mtr_dt_right_back.getActualVelocity() - 150);
        
    //  def::display.setInertialData(1, "IMU1-H: " + std::to_string(std::round(def::imu_back.get_heading())));//1
    //  def::display.setInertialData(2, "IMU1-R: " + std::to_string(std::round(def::imu_back.get_roll())));//1
    //  def::display.setInertialData(3, "IMU1-P: " + std::to_string(std::round(def::imu_back.get_pitch())));//1
    //  def::display.setInertialData(4, " IMU2-H: " + std::to_string(std::round(def::imu_side.get_heading())));//2
    //  def::display.setInertialData(5, " IMU2-P: " + std::to_string(std::round(def::imu_side.get_roll())));//2
     

      if (mcontrolEnabled)
          controlState();
      update();
      pros::delay(20);
  }
}
