#pragma once
USING_NS_CC;

#define GM GameSceneManager::getInstance()
enum { MAX_TILEKIND  = 12};
enum { NUM_OF_PLAYER = 2 };
enum { MAP_MAX_HEIGHT = 11, MAP_MAX_WIDTH = 10 };

enum PhaseInfo{
	PHASE_READY,
	PHASE_HARVEST,
	PHASE_OCCUPY,
	PHASE_VOLCANO,
	PHASE_ACTION,
	PHASE_PASTEUR,
	PHASE_ERR,
	MAX_PHASE
};

enum AnimationState{
	ANIM_DEFAULT,
	ANIM_MOVE,
	ANIM_ERR = -1
};

enum PlayerInfo : int
{
	PLAYER_RED,
	PLAYER_BLUE,
	PLAYER_ERR = -1
};

enum TileKind {
	TILE_NULL,
	TILE_PLAIN,
	TILE_FOREST,
	TILE_VILLAGE,
	TILE_HEADQUARTER,
	TILE_BARRACK,
	TILE_RICH,
	TILE_LAKE,
	TILE_VOCANO,
	TILE_LAVA,
	TILE_RICH_SIDE,
	TILE_MOVE
};
enum DirectionKind : int
{
	DIRECTION_DOWN_LEFT,
	DIRECTION_DOWN,
	DIRECTION_DOWN_RIGHT,
	DIRECTION_UP_RIGHT,
	DIRECTION_UP,
	DIRECTION_UP_LEFT,
	MAX_DIRECTION,
	DIRECTION_ERR = -1
};

enum RotateDirection
{
	ROTATE_LEFT,
	ROTATE_RIGHT,
	ROTATE_ERR = -1
};

enum Winner
{
	WINNER_ATTACKER = true,
	WINDDER_DEFENDER = false
};

enum EventType
{
	HISTORY_EVENT_BATTLE
};

#define ATTACK_POWER_DEFAULT 2;

//SOUND - ogg, mp3, wav able
#define FILENAME_SOUND_MAIN_BGM "Sound/22-forever-credits-.mp3"

#define FILENAME_SOUND_GAME_BGM "Sound/battle.mp3"
#define FILENAME_SOUND_GAME_SWORD "Sound/swords.wav"
#define FILENAME_SOUND_GAME_MOVE "Sound/Jump_03.wav"
#define FILENAME_SOUND_GAME_KILL "Sound/Hit_03.wav"
#define FILENAME_SOUND_GAME_VOLCANO "Sound/lava-01.wav"
#define FILENAME_SOUND_GAME_HARVEST "Sound/Emerge6.wav"

//IMG - png, jpeg able
#define FILENAME_IMG_MAIN_BACKGROUND "Background/Total_War_Rome_2_Roman_Soldier_Sword_warrior_warriors_fantasy_battle_1920x1080.jpg"
#define FILENAME_IMG_MAIN_CURSOR "cursor.png"

#define FILENAME_IMG_GAME_BACKGROUND "Background/ocean water.jpg"
#define FILENAME_IMG_GAME_CHARACTER_MOVABLE_TILE "tile_move.png"
#define FILENAME_IMG_GAME_CHARACTER_EFFECT_HIT_01_FIRST "HitEffect_01.png"
#define FILENAME_IMG_GAME_CHARACTER_EFFECT_HIT_02 "HitEffect_02.png"
#define FILENAME_IMG_GAME_CHARACTER_EFFECT_HIT_03 "HitEffect_03.png"
#define FILENAME_IMG_GAME_CHARACTER_EFFECT_HIT_04_LAST "HitEffect_04.png"

#define FILENAME_IMG_ATTACK_POWER_1 "UI/1.png"
#define FILENAME_IMG_ATTACK_POWER_2 "UI/2.png"
#define FILENAME_IMG_ATTACK_POWER_3 "UI/3.png"
#define FILENAME_IMG_ATTACK_POWER_4 "UI/4.png"
#define FILENAME_IMG_ATTACK_POWER_5 "UI/5.png"
#define FILENAME_IMG_ATTACK_POWER_6 "UI/6.png"

//FONT
#define FILENAME_FONT_MAINMENU "fonts/Marker Felt.ttf"