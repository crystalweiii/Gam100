/************************************************************************************************
Filename :	Map.h / Map.c
Author(s):	Ong Jia Quan Joel, Desmond, Ngian Teck Wei
Login(s) :	o.jiaquanjoel(25%), seeweedesmond.yeo(25%), teckwei.ngian(50%)

Description/Features:
This file contains reading from .csv (for level design) file.
It also contains function to print out ASCII characters.
It also contains function to print out game instructions.
It also contains setter and getter functions to retrieve map[][] data

************************************************************************************************/
#pragma once
#include "Header.h"
#include "Graphic.h"
#include "Menu.h"
#include "Math.h"

/*Cordinate for outer border*/
COORD v_border_top;
COORD v_border_btm;

/*Space better outer border and map*/
COORD v_map_buffer;

/*Cordinate for map border top*/
COORD v_map_top;
COORD v_map_btm;


struct S_MapIndex /*to keep track of the maps*/
{
	int v_current;
	int v_selected;
	int v_amount;
};

struct S_MapIndex s_map_index;

struct S_MapData /*to keep track of the maps*/
{
	char V_Map_Array[d_game_width][d_game_height];
};

/*int V_current_map_index = 0;  to keep track of the current map*/

struct S_MapData s_map_db[d_map_amount];
struct S_MapData s_current_map;
/*
char V_Map_Data_Array[d_map_amount][d_game_width][d_game_height];
char V_Map_Array[d_game_width][d_game_height];
*/

void F_Map_Init();

void F_Map_Set(int index); /*set index to the current map*/
void F_Map_Empty(); /*clear screen*/
void F_Map_EmptySlow();

void F_Map_Print();
void F_Map_Set_And_Print(int index);

/*Drawing border with specific ascicode*/
/*void F_Map_DrawBorder(COORD top, COORD btm, int ascicode);*/

void F_Map_Instruction_Printout();

/*------------------------------------------------------
// Public Variable Declaration
------------------------------------------------------*/
/* Reusable: for lvl 1, 2, 3, etc..       */
char map[d_game_height][d_game_width];
int mapWidth;
int mapHeight;


/*------------------------------------------------------
// Init
------------------------------------------------------*/
/* Map Init: for Gameplay State*/
void F_MapManager_Gameplay_Init(LevelType levelType);



/*------------------------------------------------------
// Setter & Getter
------------------------------------------------------*/
/* Set: map[y][x] = TileType */
void F_Set_Map_DataType(char type, int x, int y);

/* Get: map[y][x] = ? */
char F_Get_Map_DataType(int x, int y);

/* Get: Player Spawn Point Position*/
Vector2D F_MapManager_GetPlayerSpawnPosition();

/* Get: Map playable width */
int F_MapManager_GetMapWidth();

/* Get: Map playable height */
int F_MapManager_GetMapHeight();


/*------------------------------------------------------
// Others
------------------------------------------------------*/
/* Retrieve: Enemy Spawn Point[] positions*/
void F_MapManager_GetEnemySpawnPosition(float *spawnEnemyPosX, float *spawnEnemyPosY, int *noOfSpawnPoint);
