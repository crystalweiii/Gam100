/************************************************************************************************
Filename :	Header.h 
Author(s):  Darren Low, Ngian Teck Wei, Ong Jia Quan Joel
Login(s) :	s.low (33%), teckwei.ngian (33%),  o.jiaquanjoel (33%)

Description/Features:
Gather all the Marco together, easier for us to tweak the values.

************************************************************************************************/

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <dos.h>
#include <stdbool.h>

/*
 *  Window Console Size:
 */
#define d_window_width 211					/* Guys, resize your console window to this size */
#define d_window_height 49					/* Guys, resize your console window to this size */

/*
 *  Map Macro:
 */
#define d_game_width 120					/*Adjust: Gameplay map->size*/
#define d_game_height 40					/*Adjust: Gameplay map->size*/
#define d_border_offset_x 0					/*Adjust: Dont touch please*/
#define d_border_offset_y 0					/*Adjust: Dont touch please*/

#define d_map_offset_x 0					/*Adjust: Dont touch please*/
#define d_map_offset_y 0					/*Adjust: Dont touch please*/

#define d_instruction_width 35				/*Adjust: Instruction on the right side of gameplay map->size*/
#define d_ui_height 8						/*Adjust: UI on the btm of gameplay map->size*/

 /*
  *  Spawner Macro:
  */
#define d_MAX_ENEMY_SPAWN_POINT 5

  /*
   *  GameObject Macro:
   */
#define d_MAX_GAMEOBJECTS 400

   /*
	*  Invincible tiles Macro:
	*/
#define d_MAX_INVINCIBLE_TILES 1000

  /*
   *  Character Properties:
   */
#define d_CHARACTER_SCALE_X 3			//Character: scale X  (player/enemy/bullet scale X)
#define d_CHARACTER_SCALE_Y 2			//Character: scale Y  (player/enemy/bullet scale X)

   /*
	*  Player Properties:
	*/
#define d_PLAYER_SPEED 30				//Player: move speed
#define d_RATE_OF_PLAYER_FIRE 0.73f		//Player: shoot cooldown
#define d_PLAYER_SHOOT_X_OFFSET 9		//Player: Bullet Spawn position
#define d_PLAYER_SHOOT_Y_OFFSET -5		//Player: Bullet Spawn position
#define d_PLAYER_LIFE 3
	/*
	 *  Bullet Properties:
	 */
#define d_MAX_BULLETS 50
#define d_BULLET_SPEED 35
#define d_BULLET_INVENTORY 5
	/*
	 *  Blocker Properties:
	 */
#define d_MAX_BLOCKERS 150
#define d_BLOCKER_IS_VISIBLE false

	 /*
	  *  Enemy Properties:
	  */
#define d_MAX_ENEMIES 30
#define d_ENEMY_SPEED 8
#define d_ENEMY_ANGRY_SPEED d_ENEMY_SPEED * 2.0f
#define d_RATE_OF_ENEMY_SPAWN 1.45f
  /*
   *  Textfile Macro:
   */
#define d_maxchar 1000

#define d_map_amount 9
#define txt_Map1 "txt_file/Map1.txt"
#define txt_GameLogo "txt_file/GameLogo.txt" 
#define txt_Gameover "txt_file/GameOver.txt"
#define txt_DGPLogo "txt_file/DigipenLogo.txt"
#define txt_Win "txt_file/Win.txt"
 /*
  *  LevelType: Use to generate correct map [e.g "Map%d.csv", levelType]
  */
typedef enum {
	Level_One,
	Level_Two,
	Level_Three,
	Level_Four,
	Level_Five,
	Level_GameOver,
	Level_Win,
} LevelType;

/*
 *  FaceDirType: enemy face dir during spawning
 */
typedef enum {
	FACE_LEFT,
	FACE_DOWN,
	FACE_DOWN_LEFT,
	FACE_UP_LEFT
} FaceDir;

static char TILE_EMPTY = ' ';
static char TILE_WALL_H = '-';
static char TILE_WALL_V = '|';
static char TILE_PLAYER_SPAWNER = 'P';
static char TILE_PLAYER_SPAWNER_2 = 'D';

static char TILE_ENEMY_SPAWNER_DOWN = 'E';
static char TILE_ENEMY_SPAWNER_LEFT = 'F';
static char TILE_ENEMY_SPAWNER_DOWN_LEFT = 'G';  
static char TILE_ENEMY_SPAWNER_UP_LEFT = 'H';

static char TILE_PLAYER = '$';
static char TILE_ENEMY = 'X';
static char TILE_BULLET_1 = '>';
static char TILE_BULLET_2 = '^';
static char TILE_PLAYER_DEFENSE = 'B';
static char TILE_ROAD_H = '=';
static char TILE_ROAD_V = '/';
static char TILE_ENEMY_MOVEUP = 'U';
static char TILE_ENEMY_MOVEDOWN = 'V';
static char TILE_ENEMY_MOVELEFT = 'L';
static char TILE_ENEMY_MOVERIGHT = 'R';
static char TILE_ENEMY_MOVE_DOWNLEFT = 'T';
static char TILE_ENEMY_MOVE_UPLEFT = 'Y';
static char TILE_ENEMY_MOVE_THREEDIR = 'S';
static char TILE_ENEMY_MOVE_TWODIR_LEFT_TOPLEFT = 'I';
static char TILE_ENEMY_MOVE_TWODIR_LEFT_BTMLEFT = 'O';
/*
 *  ObjectType: Use to differentiate which is "active GameObject" & differentiate color GameObject
 */
typedef enum
{
	None,
	Taken,
	Player,
	EnemyRed,
	EnemyBlue,
	EnemyGreen,
	BulletRed,
	BulletGreen,
	BulletBlue,
	BlockerUp,
	BlockerDown,
	BlockerLeft,
	BlockerRight,
	BlockerUpLeft,
	BlockerDownLeft,
	BlockerThreeDir,
	BlockerTwoDir_Left_TopLeft,
	BlockerTwoDir_Left_BtmLeft,
} ObjectType;

/*
 *  TextColorType: Use to change printf color
 */
typedef enum {
	FG_BLACK = 0,
	FG_BLUE = 1,
	FG_GREEN = 2,
	FG_CYAN = 3,
	FG_RED = 4,
	FG_MAGENTA = 5,
	FG_BROWN = 6,
	FG_LIGHTGRAY = 7,
	FG_DARKGRAY = 8,
	FG_LIGHTBLUE = 9,
	FG_LIGHTGREEN = 10,
	FG_LIGHTCYAN = 11,
	FG_LIGHTRED = 12,
	FG_LIGHTMAGENTA = 13,
	FG_YELLOW = 14,
	FG_WHITE = 15
} TextColorType;

/*
 *  BackgroundColorType: Use to change background color
 */
typedef enum {
	BKG_BLACK	= 0,
	BKG_WHITE	= 1,
	BKG_GREY	= 2,
	BKG_RED		= 3,
	BKG_GREEN	= 4,
	BKG_BLUE	= 5,
} BackgroundColorType;

/* Basic Colors */
#define BG_BLACK		0x0000
#define BG_BLUE			0x0010
#define BG_GREEN		0x0020
#define BG_RED			0x0040 
#define BG_INTENSITY	0x0080

/* Mixed Colors */
#define BG_WHITE	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BG_GREY		BACKGROUND_INTENSITY
#define BG_CYAN		BG_GREEN | BG_BLUE
#define BG_YELLOW	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define BG_LIGHT_RED BACKGROUND_RED | BACKGROUND_INTENSITY
#define BG_LIGHT_GREEN BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define BG_LIGHT_BLUE BACKGROUND_BLUE | BACKGROUND_INTENSITY

typedef struct
{
	int active;
	COORD position;
}GameObject;

enum GameState
{
	Pause = -2,
	End = -1,

	StartUp = 0,
	MainMenu,
	GamePlay,
	Credit,
	GameOver,

	NumberOfState

};

enum PrintTrack
{
	PT_Basic_Instruction = 0,
	PT_Game_Instruction,
	PT_Game_Info_Right,
	PT_Game_Info_Below,
	PrintTrack_Total
};

#endif // !Header.h



