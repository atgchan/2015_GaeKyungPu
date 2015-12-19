#pragma once
#include "definition.h"
#include "GameSceneManager.h"

class Phase
{
public:
	Phase();
	virtual ~Phase();
	virtual void Tick() = 0;
	PhaseInfo _NextPhaseInfo = PHASE_ERR;
	PhaseInfo			getPhaseInfo(){ return _PhaseInfo; }
protected:
	PhaseInfo			_PhaseInfo = PHASE_ACTION;
};

