#pragma once

class Character;

class PlayerData
{
public:
	PlayerData(int food, int barrackNum);
	~PlayerData();

	int		_PlayerBarrackNum;
	int		getFood();
	void	setFood(int _food);
	void	AddFood(int num);

	std::list<Character*>* getCharacterList();
	void	AddCharacter(Character* character);
	void	RemoveCharacter(Character* character);

private:
	int		_Food;
	std::list<Character*> _CharacterList;
};