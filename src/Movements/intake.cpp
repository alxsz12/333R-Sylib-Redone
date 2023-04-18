#include "main.h"

void Intake::RollerColor()
{
    def::r_rot.reset_position();
    IntakeStateMachine::setState(INTAKE_STATES::in);
    Drivetrain::moveArcade(-0.3, 0.0, false);
        while (def::r_rot.get_position() < 90) 
        {// while its not in the range of the color
        pros::delay(100);
        }        
        Drivetrain::moveArcade(0.0, 0.0, false);       
        IntakeStateMachine::setState(INTAKE_STATES::off);  //then it stops the motor
        def::controller.rumble("-"); // and rumbles the controller
        pros::delay(20); // to signify that it completed the loop
}

void Intake::SkillsColor()
{
    def::r_rot.reset_position();
    IntakeStateMachine::setState(INTAKE_STATES::in);
    Drivetrain::moveArcade(-0.1, 0.0, false);
        while (def::r_rot.get_position() <= 270) 
        {// while its not in the range of the color
        pros::delay(100);
        }        
        Drivetrain::moveArcade(0.0, 0.0, false);       
        IntakeStateMachine::setState(INTAKE_STATES::off);  //then it stops the motor
        def::controller.rumble("-"); // and rumbles the controller
        pros::delay(20); // to signify that it completed the loop
        def::r_rot.reset_position();
        def::r_rot.set_position(10);
}

void Intake::Red()
{
   
        while (def::r_rot.get_position() < 90) 
        {// while its not in the range of the color
            def::mtr_it.moveVoltage(12000);
            Drivetrain::moveArcade(-0.15, 0.0, false);
        }
            def::mtr_it.moveVoltage(0);
        
        Drivetrain::moveArcade(0.0, 0.0, false);       
        def::mtr_it.moveVoltage(0);  //then it stops the motor
        def::controller.rumble("-"); // and rumbles the controller
        pros::delay(20); // to signify that it completed the loop
}

void Intake::Blue()
{       
        IntakeStateMachine::setState(INTAKE_STATES::in); 
        while (200 <= (def::o_rollerL.get_hue()) <= 250)
        {// while its not in the rang of the color
            pros::delay(100);
        } 
        IntakeStateMachine::setState(INTAKE_STATES::off); 
        //Drivetrain::moveArcade(0.0, 0.0, false);
        //mmtr.moveVoltage(0); //then it stops the motor
        //def::controller.rumble("-");// and rumbles the controller
        //pros::delay(20); //to signify that it completed the loop
}