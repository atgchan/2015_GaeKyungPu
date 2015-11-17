#include "pch.h"
#include <list>
#include "PlayerData.h"

PlayerData* PlayerData::create()
{
	///# �̰� ���� create�Լ��� ���� �� �ʿ䰡 �ֳ�?
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
	///# ���� �÷��ǿ� ���� �����͸� ������ �����ϴ� ���� ���� ��ü ���������� ���ϴ�.
	return &_CharacterList;
}