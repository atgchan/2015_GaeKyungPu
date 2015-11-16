#pragma once

#include "definition.h"
#include "PlayerData.h"

#include "TileMap.h"

class Phase;
class BattleManager;
class DiceDice;

struct TILEARRAYSET
{
	Self_Tile* tile = nullptr;
	Rect rect = Rect();
};
//싱글톤으로 구현
class GameSceneManager
{
public:

	/*
	@brief		게임의 초기 셋팅을 진행합니다. 현재 기능 : 초기 맵 그리기
	@warning	이 함수를 통해 셋팅하지 않은 GameMaster는 사용할 수 없습니다.
	*/
	void		InitializeGame();
	void		EndGame();

	/*
	@brief		mouse버튼 이벤트 리스너에 걸어둘 수 있는 2차 디스패쳐입니다.
	*/
	void		MouseDownDispatcher(cocos2d::EventMouse *event);

	/*
	@brief		mouse버튼 이벤트 리스너에 걸어둘 수 있는 2차 디스패쳐입니다.
	*/
	void		KeyReleasedDispatcher(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	/*
	@brief		GameMaster에게서 요청할 어떠한 기능이라도 getInstance()를 통해 pointer를 얻어 요청합니다.
	*/
	static GameSceneManager* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new GameSceneManager();
		}
		return inst;
	}
	/*
	@brief		GameMaster가 포함하고 있는 모든 node를 하나의 트리로 묶어 포인터로 반환합니다.
	*/
	Node*		getNodes(){ return _Nodes;}

	PlayerData*	getCurrentPlayerData();
	PlayerInfo	getCurrentPlayer();

	void		ChangePlayer();
	bool		getIsVolcanoActivated(){	return _IsVolcanoActivated;	}
	int			getProgressVolcano(){ return _ProgressVolcano; }
	void		setProgressVolcano(int progress){ _ProgressVolcano = progress; }
	bool		getIsMouseLocked(){ return _IsMouseLocked; }

	void		ScheduleCallback(float delta);

	/*
	@brief		GameScene으로부터 CALLBACK 받아 턴 변경. (추후에 UI 클래스에서 CALLBACK 하도록)
	*/
	void		ToggleTurn(Object* pSender);

	/*
		@brief	타일의 포인터와 타일의 클릭 가능한 위치를 나타내는 사각형을 받아서 배열로 저장한다.
	*/
	void		PushTileToList(Rect rect, Self_Tile* tile);

	/*
		@brief	타일 리스트에서 해당 좌표값의 위치에 포함되는 타일이 있는지 검사해서 있으면 타일 포인터를 반환한다.
	*/
	Self_Tile*	getExistingTileWithMousePoint(Vec2 vec);

	void		AddChild(Node* targetNode);
	void		ChangeRichToLava(Self_Tile* target);
	void		GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);
	void		KillCharacter(Character* target);
	void		setVolcanoActivated(bool activated){ _IsVolcanoActivated = activated; };

	Self_Tile*	getTileFromMouseEvent(const cocos2d::EventMouse *event);

	PlayerData*	getPlayerDataByPlayerInfo(PlayerInfo player);
	bool		DraftNewCharacterByClick(Self_Tile* clickedTile);
	void		MoveCharacterByClick(Self_Tile* clickedTile);

	bool		_ReadyToMove = false;
	Character*	_CharacterToMove = nullptr;
	void		setInputMode(bool mode){ _IsInputAble = mode; }

private:
	BattleManager*	_BMInstance;
	GameSceneManager();
	~GameSceneManager();

	static GameSceneManager *inst;
	TileMap*	_TileMap;
	PlayerData*	_PlayerData[NUM_OF_PLAYER];
	Node*		_Nodes;

	PhaseInfo	_CurrentPhaseInfo = PHASE_HARVEST;
	PlayerInfo	_RurrentPlayer = PLAYER_RED;
	Phase*		_CurrentPhase = nullptr;

	bool		_DraftMode = false;

	void		SpawnCharacterOnTile(Self_Tile* tile, int spriteNum, int spendFood=1);

	int			_ProgressVolcano = 0;

	/*타일만 별도로 저장할 배열을 만든다..*/
	std::vector<TILEARRAYSET> _TileList;

	bool		_IsMouseLocked = true;
	bool		_IsGameInitialized = false;
	bool		_IsVolcanoActivated = false;
	bool		_IsTurnRunning = true;
	bool		_IsDebugingActivated = false;
	bool		_IsInputAble = true;

	Phase*		_Phases[7];
	Self_Tile*	_DraftTile;

	DiceDice* _Dice;

	void		ChangePhase(PhaseInfo);

};