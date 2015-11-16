#include "pch.h"
#include "Phase_Action.h"


Phase_Action::Phase_Action()
{
}


Phase_Action::~Phase_Action()
{
}

void Phase_Action::Tick()
{
	_NextPhase = PHASE_ACTION;
}