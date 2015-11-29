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

void PlayerData::AddCharacter(std::shared_ptr<Character> character)
{
	_CharacterList.push_back(character);
}

void PlayerData::RemoveCharacter(std::shared_ptr<Character> character)
{
	_CharacterList.remove(character);
}

std::list<std::shared_ptr<Character>>* PlayerData::getCharacterList()
{
	return &_CharacterList;
}