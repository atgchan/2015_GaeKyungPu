#pragma once

class Character;

class PlayerData
{
public:
	PlayerData(int food, int barrackNum, int id);
	~PlayerData();

	int		_PlayerBarrackNum;
	int		getFood();
	int		GetSqlId(){ return _SqlId; };

	void	setFood(int _food);
	void	AddFood(int num);

	std::list<Character*>* getCharacterList();
	void	AddCharacter(Character* character);
	void	RemoveCharacter(Character* character);

private:
	int		_SqlId = 0;
	int		_Food;
	std::list<Character*> _CharacterList;
};