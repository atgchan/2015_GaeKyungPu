#include "pch.h"
#include "DiceDice.h"
#include "TileMap.h"

DiceDice* DiceDice::_Inst = nullptr;

DiceDice::DiceDice()
{
	srand(time(nullptr));
}

int DiceDice::RollDiceBetween(int start, int end)
{
	int result = static_cast<int>(CCRANDOM_0_1() * end) + start;
	//DisplayDiceOnScreen(result);
	return result;
}

void DiceDice::DisplayDiceOnScreen(int num)
{
	//추후추가
}

void DiceDice::RemoveDiceFromScreen(cocos2d::Label* numToDisplay)
{
	TileMap::getInstance()->removeChild(numToDisplay);
}

DiceDice* DiceDice::getInstance()
{
	if (!_Inst)
		_Inst = new DiceDice();
	return _Inst;
}
