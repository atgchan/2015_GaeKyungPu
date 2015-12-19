#include "pch.h"
#include "Phase_Action.h"


Phase_Action::Phase_Action()
{
	_PhaseInfo = PHASE_ACTION;
}


Phase_Action::~Phase_Action()
{
}

void Phase_Action::Tick()
{
	_NextPhaseInfo = PHASE_ACTION;
}