#include "pch.h"
#include <list>
#include "PlayerData.h"

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
}

int	 PlayerData::getFood()
{
	return food;
}

void PlayerData::setFood(int _food)
{
	food = _food;
}

void PlayerData::AddFood(int num)
{
	food += num;
}

void PlayerData::AddCharacter(Character* character)
{
	characterList.push_back(character);
}

void PlayerData::RemoveCharacter(Character* character)
{
	characterList.remove(character);
}

std::list<Character*>* PlayerData::getCharacterList()
{
	return &characterList;
}