#include "pch.h"
#include <list>
#include "PlayerData.h"

PlayerData* PlayerData::create()
{
	///# 이걸 굳이 create함수를 만들어서 할 필요가 있나?
	PlayerData* pData = new PlayerData(); 
	return pData;
}

PlayerData::PlayerData()
{
}

PlayerData::~PlayerData()
{
}

int	 PlayerData::getFood()
{
	return _Food;
}

void PlayerData::setFood(int _food)
{
	_Food = _food;
}

void PlayerData::AddFood(int num)
{
	_Food += num;
}

void PlayerData::AddCharacter(Character* character)
{
	_CharacterList.push_back(character);
}

void PlayerData::RemoveCharacter(Character* character)
{
	_CharacterList.remove(character);
}

std::list<Character*>* PlayerData::getCharacterList()
{
	///# 내부 컬렉션에 대한 포인터를 밖으로 노출하는 것은 전혀 객체 지향적이지 못하다.
	return &_CharacterList;
}