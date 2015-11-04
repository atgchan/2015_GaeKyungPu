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
	void	addFood(int num);

	std::list<Character*>* getCharacterList(); ///# ������ �÷��� ��ü�� �ܺη� ������ �Ѱ��ִ� �Ŵ� ��ü����� �Ÿ��� �ִ�. ��κ��� ��� �ٸ� ���� ����� �ִ�. ����غ�����.
	void	addCharacter(Character* character);
	void	removeCharacter(Character* character);
	
	PlayerData* opponentPlayer;

	static PlayerData* create();
private:
	int		food;
	std::list<Character*> characterList;
};