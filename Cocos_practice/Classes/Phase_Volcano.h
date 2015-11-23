#pragma once
#include "Phase.h"

class Phase_Volcano : public Phase
{
public:
	Phase_Volcano();
	~Phase_Volcano();
	void Tick();

private:
	Vector<cocos2d::Node*> _VolcanoTileList;
	Vector<cocos2d::Node*>::iterator _VolcanoTileListIter;

	void ChangeRichToLava(int repeat);
	void ChangeAllLavaToPlane();
	void ChangePlanesToRich();
};

