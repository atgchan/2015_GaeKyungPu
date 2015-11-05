#pragma once
#include "Phase.h"
class Phase_Harvest : public Phase
{
public:
	Phase_Harvest();
	~Phase_Harvest();
	void Tick();
};

