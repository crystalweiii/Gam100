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
#define d_MAX_ROWS 48		//map height:  48
#define d_MAX_COLUMNS 200	//map width : 200

#define d_game_width 90
#define d_game_height 20

 /*
  *  Spawner Macro:
  */
#define d_MAX_ENEMY_SPAWN_POINT 5

  /*
   *  GameObject Macro:
   */
#define d_MAX_GAMEOBJECTS 200

  /*
   *  Character Properties:
   */
#define d_CHARACTER_SCALE_X 5			//Character: scale X  (player/enemy/bullet scale X)
#define d_CHARACTER_SCALE_Y 3			//Character: scale Y  (player/enemy/bullet scale X)

   /*
	*  Player Properties:
	*/
#define d_PLAYER_SPEED 15				//Player: move speed
#define d_RATE_OF_PLAYER_FIRE 0.25f		//Player: shoot cooldown
#define d_PLAYER_SHOOT_X_OFFSET 9		//Player: Bullet Spawn position

	/*
	 *  Bullet Properties:
	 */
#define d_MAX_BULLETS 50
#define d_BULLET_SPEED 50

	 /*
	  *  Enemy Properties:
	  */
#define d_MAX_ENEMIES 30
#define d_ENEMY_SPEED 20
#define d_ENEMY_ANGRY_SPEED d_ENEMY_SPEED * 2
  /*
   *  Textfile Macro:
   */
#define d_maxchar 1000

#define d_map_amount 3
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

/*
 *  TileType: Use to "Print Character" & for "Collision"
 */
typedef enum
{
	TILE_INVALID,
	TILE_EMPTY,
	TILE_WALL_TL,
	TILE_WALL_TR,
	TILE_WALL_BL,
	TILE_WALL_BR,
	TILE_WALL_H,
	TILE_WALL_V,
	TILE_PLAYER_SPAWNER = 8,
	TILE_ENEMY_SPAWNER = 9,
	TILE_PLAYER_DEFENSE = 10,
	TILE_PLAYER_DEFENSE_DECORATION1 = 11,
	TILE_PLAYER,
	TILE_ENEMY,
	TILE_BULLET,
} TileType;

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

	NumberOfState

};

#endif // !Header.h



