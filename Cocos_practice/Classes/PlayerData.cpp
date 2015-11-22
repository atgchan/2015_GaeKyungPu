#include "pch.h"
#include <list>
#include "PlayerData.h"

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
	return &_CharacterList;
}