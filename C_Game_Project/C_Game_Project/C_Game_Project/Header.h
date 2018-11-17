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

/*
 *  Map Macro:
 */
#define d_game_width 120					/*Adjust: Gameplay map->size*/
#define d_game_height 49					/*Adjust: Gameplay map->size*/

#define d_border_offset_x 0					/*Adjust: Dont touch please*/
#define d_border_offset_y 0					/*Adjust: Dont touch please*/

#define d_map_offset_x 0					/*Adjust: Dont touch please*/
#define d_map_offset_y 0					/*Adjust: Dont touch please*/

#define d_instruction_width 40				/*Adjust: Instruction on the right side of gameplay map->size*/
#define d_ui_height 10						/*Adjust: UI on the btm of gameplay map->size*/

 /*
  *  Spawner Macro:
  */
#define d_MAX_ENEMY_SPAWN_POINT 5

  /*
   *  GameObject Macro:
   */
#define d_MAX_GAMEOBJECTS 200

   /*
	*  Invincible tiles Macro:
	*/
#define d_MAX_INVINCIBLE_TILES 1000

  /*
   *  Character Properties:
   */
#define d_CHARACTER_SCALE_X 2			//Character: scale X  (player/enemy/bullet scale X)
#define d_CHARACTER_SCALE_Y 2			//Character: scale Y  (player/enemy/bullet scale X)

   /*
	*  Player Properties:
	*/
#define d_PLAYER_SPEED 15				//Player: move speed
#define d_RATE_OF_PLAYER_FIRE 0.25f		//Player: shoot cooldown
#define d_PLAYER_SHOOT_X_OFFSET 9		//Player: Bullet Spawn position
#define d_PLAYER_SHOOT_Y_OFFSET -5		//Player: Bullet Spawn position

	/*
	 *  Bullet Properties:
	 */
#define d_MAX_BULLETS 50
#define d_BULLET_SPEED 50

	 /*
	  *  Enemy Properties:
	  */
#define d_MAX_ENEMIES 30
#define d_ENEMY_SPEED 5
#define d_ENEMY_ANGRY_SPEED d_ENEMY_SPEED * 2
  /*
   *  Textfile Macro:
   */
#define d_maxchar 1000

#define d_map_amount 4
#define txt_DGPLogo "txt_file/DigipenLogo.txt"
#define txt_Map1 "txt_file/Map1.txt"
 
 /*
  *  LevelType: Use to generate correct map [e.g "Map%d.csv", levelType]
  */
typedef enum {
	Level_One,
	Level_Two,
	Level_Three
} LevelType;


static char TILE_EMPTY = ' ';
static char TILE_WALL_H = '-';
static char TILE_WALL_V = '|';
static char TILE_PLAYER_SPAWNER = 'P';
static char TILE_PLAYER_SPAWNER_2 = 'D';
static char TILE_ENEMY_SPAWNER = 'E';
static char TILE_PLAYER = '$';
static char TILE_ENEMY = 'X';
static char TILE_BULLET_1 = '>';
static char TILE_BULLET_2 = '^';
static char TILE_PLAYER_DEFENSE = 'B';
static char TILE_ROAD_H = '=';
static char TILE_ROAD_V = '/';
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
	BulletBlue,
	BulletGreen
} ObjectType;

/*
 *  ColorType: Use to change printf color
 */
typedef enum {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGRAY = 7,
	DARKGRAY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
} ColorType;

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

	NumberOfState

};

#endif // !Header.h



