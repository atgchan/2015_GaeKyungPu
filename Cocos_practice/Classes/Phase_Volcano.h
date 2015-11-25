#pragma once
#include "Phase.h"

class Phase_Volcano : public Phase
{
public:
	Phase_Volcano();
	~Phase_Volcano(); ///# 소멸자가 하는일 없으면 선언하지 마라. 사실 요놈은 virtual인데, 선언시에 virtual을 붙여 놓지 않으면 코드 읽는 사람이 헷갈린다.
	void Tick();

private:
	///# 아래는 타일 리스트인데 왜 Node*인지?
	Vector<cocos2d::Node*> _VolcanoTileList;
	Vector<cocos2d::Node*>::iterator _VolcanoTileListIter;

	void ChangeRichToLava(int repeat);
	void ChangeAllLavaToPlane();
	void ChangePlanesToRich();
	std::random_device _RandomDevice;

	std::mt19937 _Gen;
};

