#include "pch.h"
#include "HistoryEventChangeTile.h"
#include "Self_Tile.h"
#include "SimpleAudioEngine.h"
#include "TileMap.h"

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
	Self_Tile* copySpr = Self_Tile::create(_TargetType);
	copySpr->setPosition(_TargetTile->getPosition());
	copySpr->setZOrder(_TargetTile->getZOrder()+1);
	copySpr->setOpacity(0);
	TileMap::getInstance()->addChild(copySpr);
	FiniteTimeAction* fadeInCall = FadeIn::create(0.7);
	cocos2d::CallFunc* removeSelfCall = CallFunc::create(CC_CALLBACK_0(TileMap::removeChild,TileMap::getInstance(), copySpr,true));
	FiniteTimeAction* seqForCopySpr = Sequence::create(fadeInCall, changeCall, removeSelfCall,doneCall, nullptr);
	copySpr->runAction(seqForCopySpr);
	if (_TargetType == TILE_LAVA)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FILENAME_SOUND_GAME_VOLCANO);
}