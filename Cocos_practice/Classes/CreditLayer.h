#pragma once
#include "definition.h"

class CreditLayer : public cocos2d::LayerColor
{
public:
	bool init();
	static cocos2d::Scene* scene();

	CREATE_FUNC(CreditLayer);

private:
	LayerColor* BackLayer;
	void		Resume();
};