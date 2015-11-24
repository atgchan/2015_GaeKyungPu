#pragma once

class Character;

//멤버변수들로 데이터를 들고 있고 겟으로 받아온다
class PlayerData
{
public:
	///# 생성 소멸자의 경우 아무것도 내용이 없으면 선언조차 하지 말 것.
	PlayerData();
	~PlayerData();

	int		_PlayerBarrackNum;
	int		getFood();
	void	setFood(int _food);
	void	AddFood(int num);

	std::list<Character*>* getCharacterList();
	void	AddCharacter(Character* character);
	void	RemoveCharacter(Character* character);
	
	PlayerData* _OpponentPlayer;

private:
	int		_Food;
	std::list<Character*> _CharacterList;
};