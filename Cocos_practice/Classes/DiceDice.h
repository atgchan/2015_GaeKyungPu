#pragma once
class DiceDice
{
public:
	DiceDice();
	~DiceDice();
	int		RollDiceBetween(int min, int max);
	void	DisplayDiceOnScreen(int min, int max);
	void	RemoveDiceFromScreen(cocos2d::Label* numToDisplay);
};

