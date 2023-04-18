#pragma once
#include "main.h"

class Flya
{
public:

//static void flyTest(QAngularSpeed irpm, PID ipid = PID(100.0, 0.001, 100.0, 1, 0.5, 0.01, 1_ms));

static void AShoot(int s, bool wait);

};

namespace def
{
extern Flya flya;  
}