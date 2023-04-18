#include "main.h"

BLOOP_STATES BlooperStateMachine::getState() { return mstate; }
void BlooperStateMachine::setState(const BLOOP_STATES istate)
{
    mstate = istate;
}

void BlooperStateMachine::enableControl()
{
    mcontrolEnabled = true;
}

void BlooperStateMachine::disableControl()
{
    mcontrolEnabled = false;
}

void BlooperStateMachine::controlState()
{
    if (mbtnon.changedToPressed()) // if the toggle button is pressed
    {
        setState(BLOOP_STATES::on);   // flip it up.                  
    }
    else
    {
        setState(BLOOP_STATES::off);   // flip it down.
    }
}