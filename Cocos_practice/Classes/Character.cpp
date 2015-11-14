#include "pch.h"
#include "definition.h"
#include "CharacterAnimation.h"
#include "Character.h"

Character::Character(PlayerInfo cPInfo, int spriteNum)
{
	autorelease();
	setCurrentPlayerInfo(cPInfo);
	setCurrentDirection((DirectionKind)spriteNum);
}

Character* Character::create(PlayerInfo cPInfo, int spriteNum)
{
	Character* character = new Character(cPInfo, spriteNum);

//	파일 명 때문에 Red Blue 구분은 CharacterAnimation내부에서 구분한다.
//	create은 그저 캐릭터 객체를 만들 뿐, 실제 그래픽 구현은 CharacterAnimation에서 처리하는 형식

	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(cPInfo, spriteNum);
	character->init();
	character->runAction(Animate::create(animationDefault));

	if (!character)
	{
		CC_SAFE_DELETE(character);
		return nullptr;
	}

	return character;
}

bool Character::isOnTile(TileKind tileTypeToCheck)
{
	if (this->getCurrentTile()->getTypeOfTile() == tileTypeToCheck)
		return true;
	else
		return false;
}

void Character::rotateToDirection(RotateDirection rotateDirection)
{
	int chracterDirection = getCurrentDirection();

	if (rotateDirection == ROTATE_LEFT)
		chracterDirection = (chracterDirection + 1) % 6;

	if (rotateDirection == ROTATE_RIGHT)
		chracterDirection = (chracterDirection + 5) % 6;

	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(getCurrentPlayerInfo(), chracterDirection);
	init();
	stopAllActions();
	setAnchorPoint(Vec2(0.5, 0.13));
	runAction(Animate::create(animationDefault));

	setCurrentDirection(DirectionKind(chracterDirection));

	return;	
}

Character* Character::GetNearCharacter(DirectionKind direction)
{
	return this->getCurrentTile()->GetNearTile(direction)->getCharacterOnThisTile();
}

void Character::MovoToTile(Self_Tile* dest)
{
	Animation* animationMove = CharacterAnimation::CreateAnimationDefault(GetOwnerPlayer(), 1);
	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(GetOwnerPlayer(), getCurrentDirection());
	
	Animate* actionMove = Animate::create(animationMove);
	MoveTo* moveTo = MoveTo::create(0.5f, Vec2(dest->getPositionX() + 80, dest->getPositionY() + 60));
	Animate* actionDefault = Animate::create(animationDefault);

	ActionInterval* action1 = actionMove;
	ActionInterval* action2 = moveTo;
	ActionInterval* action3 = actionDefault;

	action1->setDuration(0.5f);
	FiniteTimeAction* seq = Spawn::create(action1, action2, NULL);
	FiniteTimeAction* seq1 = Sequence::create(seq, action3, NULL);

	init();
	stopAllActions();
	setAnchorPoint(Vec2(0.5, 0.13));

	getCurrentTile()->setCharacterOnThisTile(nullptr);
	dest->setCharacterOnThisTile(this);
	setCurrentTile(dest);
	this->setZOrder(dest->getZOrder() + 100);

	/*runAction(moveTo);*/
	runAction(seq1);
}

const PlayerInfo Character::GetOwnerPlayer()
{ 
	return _OwnerPlayer;
}

void Character::SetOwnerPlayer(PlayerInfo pInfo)
{ 
	_OwnerPlayer = pInfo;
}

Character::~Character()
{
	stopAllActions();
}