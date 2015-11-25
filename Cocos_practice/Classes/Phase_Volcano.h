#pragma once
#include "Phase.h"

class Phase_Volcano : public Phase
{
public:
	Phase_Volcano();
	~Phase_Volcano(); ///# �Ҹ��ڰ� �ϴ��� ������ �������� ����. ��� ����� virtual�ε�, ����ÿ� virtual�� �ٿ� ���� ������ �ڵ� �д� ����� �򰥸���.
	void Tick();

private:
	///# �Ʒ��� Ÿ�� ����Ʈ�ε� �� Node*����?
	Vector<cocos2d::Node*> _VolcanoTileList;
	Vector<cocos2d::Node*>::iterator _VolcanoTileListIter;

	void ChangeRichToLava(int repeat);
	void ChangeAllLavaToPlane();
	void ChangePlanesToRich();
	std::random_device _RandomDevice;

	std::mt19937 _Gen;
};

