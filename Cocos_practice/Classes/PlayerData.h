#pragma once

class Character;

//���������� �����͸� ��� �ְ� ������ �޾ƿ´�
class PlayerData
{
public:
	PlayerData();
	~PlayerData();

	int		getFood();
	void	setFood(int _food);
	void	AddFood(int num);

	std::list<Character*>* getCharacterList(); ///# ������ �÷��� ��ü�� �ܺη� ������ �Ѱ��ִ� �Ŵ� ��ü����� �Ÿ��� �ִ�. ��κ��� ��� �ٸ� ���� ����� �ִ�. ����غ�����.
	void	AddCharacter(Character* character);
	void	RemoveCharacter(Character* character);
	
	PlayerData* opponentPlayer;

	static PlayerData* create();
private:
	int		food;
	std::list<Character*> characterList;
};