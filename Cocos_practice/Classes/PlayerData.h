#pragma once

class Character;

//멤버변수들로 데이터를 들고 있고 겟으로 받아온다
class PlayerData
{
public:
	PlayerData();
	~PlayerData();

	int		getFood();
	void	setFood(int _food);
	void	addFood(int num);

	std::list<Character*>* getCharacterList(); ///# 내부의 컬렉션 객체를 외부로 포인터 넘겨주는 거는 객체지향과 거리가 멀다. 대부분의 경우 다른 좋은 방법이 있다. 고민해보도록.
	void	addCharacter(Character* character);
	void	removeCharacter(Character* character);
	
	PlayerData* opponentPlayer;

	static PlayerData* create();
private:
	int		food;
	std::list<Character*> characterList;
};