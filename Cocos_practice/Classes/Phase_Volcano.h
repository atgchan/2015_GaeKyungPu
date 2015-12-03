#pragma once
#include "Phase.h"

class Phase_Volcano : public Phase
{
public:
	Phase_Volcano();
	void Tick();

private:
	std::vector<Self_Tile*> _VolcanoTileList;
	std::vector<Self_Tile*>::iterator _VolcanoTileListIter;

	void ChangeRichToLava(int repeat);
	void ChangeAllLavaToPlane();
	void ChangePlanesToRich();
	std::random_device _RandomDevice;

	std::mt19937 _Gen;
};

