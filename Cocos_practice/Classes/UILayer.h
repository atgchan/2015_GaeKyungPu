#pragma once
#include "definition.h"
#include "PlayerData.h"

class UILayer : public cocos2d::LayerColor
{
public:
	bool					init();
	static cocos2d::Scene*	scene();
	const void SetFoodValue(PlayerData* currentPlayerData) const;
	void					SelectCharacter(Character* character);
	CREATE_FUNC(UILayer);
	void toggleTurn();
private:
	LayerColor* BackLayer;
	LayerColor* PopUpLayer;

	void		SetUIBar();
	void		ShowOptionWindow(Object *pSender);
	void		ShowHowToPlay();
	Sprite*		_TurnLabel = nullptr;
};