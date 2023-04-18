#pragma once
#include "main.h"

class BlooperStateMachine
{
public:
    enum class MStates
    {
        off, 
        on,
    };
    
    static MStates getState();
    static void setState(const MStates istate);

    static void enableControl();
    static void disableControl();

    static void controlState();
    static void update();
    static void run();

private:
    /* ------------------------- Devices ------------------------- */
    static SolenoidWrapper msol;
    /* -------------------------- State -------------------------- */
    static MStates mstate;
    static bool mtoggling;
    static bool mcontrolEnabled;

    /* ------------------------- Controls ------------------------ */
    static ControllerButton &mbtnon; 
};


