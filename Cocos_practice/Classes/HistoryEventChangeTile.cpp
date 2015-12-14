#include "pch.h"
#include "HistoryEventChangeTile.h"
#include "Self_Tile.h"
#include "SimpleAudioEngine.h"

HistoryEventChangeTile::HistoryEventChangeTile()
{
}


HistoryEventChangeTile::~HistoryEventChangeTile()
{
}

std::shared_ptr<HistoryEventChangeTile> HistoryEventChangeTile::Create(Self_Tile* targetTile, TileKind targetType)
{
	std::shared_ptr<HistoryEventChangeTile> newInst = std::make_shared<HistoryEventChangeTile>();
	newInst->_TargetTile = targetTile;
	newInst->_TargetType = targetType;
	return newInst;
}

void HistoryEventChangeTile::Run()
{
	cocos2d::CallFunc* changeCall = CallFunc::create(CC_CALLBACK_0(Self_Tile::ChangeTile, _TargetTile, _TargetType));
	
	cocos2d::CallFunc* doneCall = CallFunc::create(CC_CALLBACK_0(HistoryEventChangeTile::SetDone, this, true));

	FiniteTimeAction* fadeOutCall = FadeOut::create(0.5);
	FiniteTimeAction* fadeInCall = FadeIn::create(0.5);
	_TargetTile->setOpacity(255);
	FiniteTimeAction* seq = Sequence::create(fadeOutCall,changeCall, fadeInCall, doneCall, nullptr);
	_TargetTile->runAction(seq);
	if (_TargetType == TILE_LAVA)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FILENAME_SOUND_GAME_VOLCANO);
}