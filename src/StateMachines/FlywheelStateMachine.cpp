#include "definitions.hpp"
#include "main.h"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "pros/motors.hpp"
#include "stateMachines/FlywheelStateMachine.hpp"
#include "stateMachines/IntakeStateMachine.hpp"

pros::Controller master (CONTROLLER_MASTER);// Gets the controller reference so that 
                                              // so that we can print to the controller
                                              // the voltage that the flywheel is currently
                                              // spinning at

FW_STATES FlywheelStateMachine::getState() { return mstate; }
void FlywheelStateMachine::setState(const FW_STATES istate)
{
    mstate = istate;
}

void FlywheelStateMachine::enableControl()
{
    mcontrolEnabled = true;
}

void FlywheelStateMachine::disableControl()
{
    mcontrolEnabled = false;
}

void FlywheelStateMachine::controlState(){
    if(mbtnShoot.changedToPressed()){
        if (getState() == FW_STATES::off) // if it's already shooting
            setState(FW_STATES::shoot);    // make it stop.
        else 
            setState(FW_STATES::off);  //Otherwise the flywheel should be off
    }
}   

void FlywheelStateMachine::speedu(){ // Function to be able to change the flywheel speed //AKA Speed Update 
    if(mbtnUp.changedToPressed()){   // by the voltage, and as you press the buttons  
        def::fwv+= 500;                   // the flywheel voltage will update by increments of 500

        master.print(0, 0, "Flywheel: %d", def::fwv); // Then we can go and get the controller reference
    }                                // And print the new voltage after the voltage was changed
    if(mbtnDown.changedToPressed()){
        def::fwv-= 500;
        
        master.print(0, 0, "Flywheel: %d", def::fwv);
    }
    master.print(0, 0, "Flywheel: %d", def::fwv); // Prints it at the end of the loop in case there was
    // a button pressed that did not register with printing on the screen
    if(def::fwv > 4500){
        def::fwv = 4500;
    }
    if(def::fwv < 0){
        def::fwv = 0; 
    }
}


/*---------------------Flywheel PID----------------------*/
/*This will be used to try and have the flywheel operate */
/*around a set RPM using the RPM int variable and having */
/*PID iterate around the error that we are calculating   */
/*from the RPM value that we want, and the current       */
/*RPM that the flywheel rpm                              */
/*-------------------------------------------------------*/



/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
 
void FlywheelStateMachine::update() // updates the subsystem based on the state
{
    switch (mstate)
    {
        case FW_STATES::off: // Turns the flywheel Off
            def::flywheel.stop();
            break;
        case FW_STATES::shoot: // Spins the flywheel 
            def::flywheel.set_velocity_custom_controller(def::fwv); //Moves the flywheel by the changeable variable
            break;
    }
}

void FlywheelStateMachine::run()
{
    while (true)
    {
        def::display.setChartData(6, def::flywheel.get_velocity() - 3400);
        def::display.setMiscData(1, "FW Actual: " + std::to_string(def::flywheel.get_velocity()));

		printf("%d,%f,%f,%f,%d\n", sylib::millis(), def::flywheel.get_velocity_target(), def::flywheel.get_velocity(), def::flywheel.get_torque(), def::flywheel.get_applied_voltage());
        // Prints to the terminal with csv format seperate by commas
        // Can then be copied to a data.csv file where we run it through
        // a python file which will graph our data into a window where we 
        // can then view our information and start debugging
        
        def::display.setMiscData(2, "FW Target: " + std::to_string(def::flywheel.get_velocity_target()));
        def::display.setMiscData(5, "FW TEMP: " + std::to_string(def::flywheel.get_temperature()));

        def::display.setGauge(0, def::flywheel.get_temperature());

        //Updating the brain here so that we can accurately see where the current velocity is
        //in comparison to the actual target value that the PID has calculated. 
        //This helps with debugging flywheel issues as we think it is issues with the PID, but
        //it helps with figuring that the problem is not the PID, but rather the flywheel
        //needs to he tuned properly with the values printed on the brain here
        if (mcontrolEnabled)
                controlState();
            speedu(); // We can add the speed update function here to run
        update();     // and update the voltage so that it updates as often as possible
        pros::delay(20);
    }
}

/* ------------------------- Devices ------------------------- */
//sylib::Motor &FlywheelStateMachine::mmtr = def::flywheel;
/* -------------------------- State -------------------------- */

//FW_STATES FlywheelStateMachine::moverrideState = FW_STATES::off;
 FW_STATES FlywheelStateMachine::mstate = FW_STATES::off;

 bool FlywheelStateMachine::mcontrolEnabled = false;

ControllerButton &FlywheelStateMachine::mbtnShoot = def::btn_fw_shoot;

ControllerButton &FlywheelStateMachine::mbtnUp = def::btn_fw_up;
ControllerButton &FlywheelStateMachine::mbtnDown = def::btn_fw_down;