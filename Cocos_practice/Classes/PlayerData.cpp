#include "pch.h"
#include "PlayerData.h"
#include "Character.h"
#include <list>

PlayerData* PlayerData::create()
{
	PlayerData* pData = new PlayerData();
	return pData;
}

PlayerData::PlayerData()
{
}

PlayerData::~PlayerData()
{
	delete characterList;
}

int	 PlayerData::getFood()
{
	return food;
}

void PlayerData::setFood(int _food)
{
	food = _food;
}

void PlayerData::addFood(int num)
{
	food += num;
}

void PlayerData::addCharacter(Character* character)
{
	characterList->push_back(character);
}

void PlayerData::removeCharacter(Character* character)
{
	characterList->remove(character);
}

std::list<Character*>* PlayerData::getCharacterList()
{
	return characterList;
}