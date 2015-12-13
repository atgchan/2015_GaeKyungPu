#include "pch.h"
#include "HistoryEventChangeTile.h"
#include "Self_Tile.h"

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
	cocos2d::CallFunc* changeCall = CallFunc::create(CC_CALLBACK_0(Self_Tile::ChangeTile,_TargetTile, _TargetType));
	cocos2d::CallFunc* doneCall = CallFunc::create(CC_CALLBACK_0(HistoryEventChangeTile::SetDone, this, true));

	FiniteTimeAction* seq = Sequence::create(changeCall, DelayTime::create(0.5f), doneCall, nullptr);
	_TargetTile->runAction(seq);
}