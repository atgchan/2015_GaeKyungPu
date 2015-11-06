#pragma once
#include "definition.h"

class PopLayer : public cocos2d::LayerColor
{
public:
	virtual bool init();
	static cocos2d::Scene* scene();

	CREATE_FUNC(PopLayer);

private:
	LayerColor* backLayer;
	LayerColor* popUpLayer;

	void PopLayer::doClose(CCObject* pSender);

};