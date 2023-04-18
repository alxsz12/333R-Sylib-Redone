#include "definitions.hpp"
#include "main.h" // gives access to HolderStateMachine.hpp and other dependancies
#include "pros/misc.h"
#include "stateMachines/EndGameStateMachine.hpp"


END_STATES EndGameStateMachine::getState() { return mstate; }
void EndGameStateMachine::setState(const END_STATES istate)
{
    mstate = istate;
}

void EndGameStateMachine::enableControl()
{
    mcontrolEnabled = true;
}

void EndGameStateMachine::disableControl()
{
    mcontrolEnabled = false;
}

void EndGameStateMachine::controlState()
{
    if (mbtnon.changedToPressed() && mbtnon2.changedToPressed()) // if the toggle button is pressed
    {
            def::controller.rumble("- . ----....."); // Rumbles the controller with a very long rumble 
                                                                    // to distinguish that you pushed the button
                                                                    //Then it fires
            setState(END_STATES::on);   // close it.                  
    }
    // else
    // {
            // setState(END_STATES::off);     // open it.
    // }
}

void EndGameStateMachine::update() // Two states for on and off
{
    switch (mstate)
    {
    case END_STATES::off:
            def::sol_endg.set_value(false);
        break;
    case END_STATES::on:
            def::sol_endg.set_value(true);
        break;
    }
}

void EndGameStateMachine::run()
{
    while (true)
    {
        
        if(def::flywheel.get_temperature() >= 45)
        {
            pros::screen::set_pen(COLOR_RED);
            pros::screen::fill_rect(1,35,480,300);
            pros::screen::set_pen(COLOR_GHOST_WHITE);
            pros::screen::print(pros::E_TEXT_LARGE_CENTER, 3, " ! - DANGER - ! ");
            pros::delay(1000);
            //pros::screen::erase_rect(1,35,480,300);
            DisplayControl();
            pros::delay(500);
        }
        
        if (mcontrolEnabled)
            controlState();
        update();
        pros::delay(20);
    }
}

SolenoidWrapper EndGameStateMachine::msol = SolenoidWrapper(def::sol_endg, false);

/* -------------------------- State -------------------------- */
END_STATES EndGameStateMachine::mstate = END_STATES::on;
bool EndGameStateMachine::mcontrolEnabled = false;

/* ------------------------- Controls ------------------------ */
ControllerButton &EndGameStateMachine::mbtnon = def::btn_end_on;  
ControllerButton &EndGameStateMachine::mbtnon2 = def::btn_end_on2;