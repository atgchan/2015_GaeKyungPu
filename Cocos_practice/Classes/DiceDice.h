#pragma once
class DiceDice
{
public:
	DiceDice();
	int		RollDiceBetween(int min, int max);
	void DisplayDiceOnScreen(int num);
	void	RemoveDiceFromScreen(cocos2d::Label* numToDisplay);
	static DiceDice* getInstance();


private:
	static DiceDice*	_Inst;
};