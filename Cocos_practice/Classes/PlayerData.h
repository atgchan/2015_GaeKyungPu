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

	std::list<std::shared_ptr<Character>>* getCharacterList();
	void	AddCharacter(std::shared_ptr<Character> character);
	void	RemoveCharacter(std::shared_ptr<Character> character);
	
	//PlayerData* _OpponentPlayer;

private:
	int		_Food;
	std::list<std::shared_ptr<Character>> _CharacterList;
};