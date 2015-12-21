#include "pch.h"
#include "DiceDice.h"
#include "TileMap.h"
#include "Character.h"

DiceDice* DiceDice::_Inst = nullptr;

DiceDice::DiceDice()
{
	srand((unsigned)time(nullptr));
}

int DiceDice::RollDiceBetween(int start, int end)
{
	/*rand_0_1();
	
	int result = static_cast<int>(CCRANDOM_0_1() * end) + start;
	//DisplayDiceOnScreen(result);*/
	int result = random(start, end);
	return result;
}

void DiceDice::DisplayDiceOnScreen(Character* character, int num)
{

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
