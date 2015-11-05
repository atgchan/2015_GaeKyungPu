#pragma once
#include "definition.h"
#include "GameSceneManager.h"

class Phase
{
public:
	Phase();
	virtual ~Phase();
	virtual void Tick() = 0;
	PhaseInfo nextPhase = PHASE_ERR;
};

