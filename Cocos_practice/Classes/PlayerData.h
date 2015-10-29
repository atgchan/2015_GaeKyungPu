#ifndef PlayerData_h__
#define PlayerData_h__


//멤버변수들로 데이터를 들고 있고 겟으로 받아온다
class PlayerData
{
public:
	PlayerData();
	~PlayerData();

	int		getFood();
	void	setFood(int _food);
	void	addFood(int num);

	std::list<Character*>* getCharacterList();
	void	addCharacter(Character* character);
	void	removeCharacter(Character* character);
	
	PlayerData* opponentPlayer;

	static PlayerData* create();
private:
	int		food;
	std::list<Character*>* characterList;
};
#endif // PlayerData_h__