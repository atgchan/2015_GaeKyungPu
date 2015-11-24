#pragma once

class Character;

//���������� �����͸� ��� �ְ� ������ �޾ƿ´�
class PlayerData
{
public:
	///# ���� �Ҹ����� ��� �ƹ��͵� ������ ������ �������� ���� �� ��.
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