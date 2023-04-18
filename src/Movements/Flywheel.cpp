#include "main.h"

// void Flya::flyTest(QAngularSpeed irpm, PID ipid)
// {
//     QAngularSpeed targetrpm = irpm;
//     while(!ipid.isSettled())
//     {
//         double rpmError = targetrpm.convert(rpm) - def::mtr_fw.get_actual_velocity();//def::r_rot.get_position()
//         def::mtr_fw.move_velocity(ipid.iterate(rpmError));
//         pros::delay(20);
//         def::display.setMiscData(2, "FW Target: " + std::to_string(targetrpm.convert(rpm)));
//     }
// }

void Flya::AShoot(int s, bool wait)
{
    def::fwv = s;
    FlywheelStateMachine::setState(FW_STATES::shoot);
    
    if(wait){
        pros::delay(3000); //waits for it to spin up if its told to wait
    }
    IntakeStateMachine::setState(INTAKE_STATES::in); //shoots first disc
    pros::delay(125); //Waits for the shot
    IntakeStateMachine::setState(INTAKE_STATES::off);//turns off the intake
    pros::delay(1000); // waits for the fly to spin back up
    IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
    pros::delay(500); //waits to turn the intake off
    IntakeStateMachine::setState(INTAKE_STATES::off);
    def::controller.rumble("-");
}