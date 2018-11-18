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

#include "Map.h"
#include <stdbool.h>

/*--------------------------------
// Private Variable Declaration
--------------------------------*/
float player1SpawnPosX = 0;
float player1SpawnPosY = 0;
float player2SpawnPosX = 0;
float player2SpawnPosY = 0;

float enemySpawnPosX[d_MAX_ENEMY_SPAWN_POINT];
float enemySpawnPosY[d_MAX_ENEMY_SPAWN_POINT];
int numOfEnemySpawnPoint = 0;


int listOfInvincibleTilesPosX[d_map_amount][d_MAX_INVINCIBLE_TILES];
int listOfInvincibleTilesPosY[d_map_amount][d_MAX_INVINCIBLE_TILES];
char listOfInvincibleTilesType[d_map_amount][d_MAX_INVINCIBLE_TILES];
static int numOfInvincibleTiles[d_map_amount];

/*--------------------------------
// Private Function Declaration
--------------------------------*/
void F_ReadFromCSVAndStore(char tempMap[d_game_height][d_game_width], int mapIndex);
void RetrieveSpawnPositionFromData(float *spawnPlayer1PosX, float *spawnPlayer1PosY, float *spawnPlayer2PosX, float *spawnPlayer2PosY, float *spawnEnemyPosX, float *spawnEnemyPosY);




/*COORD v_border_btm;*/
COORD v_border_top = { d_border_offset_x,d_border_offset_y };
COORD v_map_buffer = { 4,2 };
COORD v_map_top = { d_map_offset_x,  d_map_offset_y };

void F_Map_Init()
{
	/*Init border btm with the buffers*/
	COORD v_temp_border_btm = { d_game_width, d_game_height};				//{ d_game_width + v_map_buffer.X, d_game_height + v_map_buffer.Y };
	COORD v_Text_border_Top = { v_border_top.X ,  v_temp_border_btm.Y };
	COORD v_Text_border_Btm = { d_game_width, d_ui_height };				//{ d_game_width + v_map_buffer.X , 10 };
	/* "Draw: Border to seperate gameplay & UI */
	F_Map_DrawBorder(v_Text_border_Top, v_Text_border_Btm);

	
	v_border_btm = v_temp_border_btm;

	//F_Map_DrawBorder(v_border_top, v_border_btm);

	/* "Read" & "Store": from text file*/
	F_ReadFromTextAndStore(txt_DGPLogo , s_map_db[0].V_Map_Array);	// Digipen logo
	F_ReadFromCSVAndStore(s_map_db[2].V_Map_Array, Level_One);		// Level 1 level design
	F_ReadFromCSVAndStore(s_map_db[3].V_Map_Array, Level_Two);		// Level 2 level design

	/* Draw: Main Menu */
	F_Main_Menu_Print(s_map_db[1].V_Map_Array);

	/* Can i delete this? */
	//F_ReadFromTextAndStore(txt_Map1, s_map_db[2].V_Map_Array);
	
	s_map_index.v_amount = d_map_amount;
	s_map_index.v_current = 0;
	s_map_index.v_selected = 0;
	
	/*F_Map_Set_And_Print(s_map_index.v_selected);*/

	/* Draw: Welcome To GGPen */
	F_Map_Instruction_Printout();
	
	/*F_Map_Set_And_Print(s_map_index.v_current);*/
}

void F_Map_Set(int index) /*set index to the current map*/
{
	s_map_index.v_selected = index;
	s_map_index.v_current = index;
}

void F_Map_Empty() /*clear screen everything*/
{
	int x = v_map_top.X, y = v_map_top.Y;
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		gotoxy(x,y);
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gh_generate][gw_generate] = ' ';
			printf("%c", s_current_map.V_Map_Array[gh_generate][gw_generate]);
		}
		++y;
	}
}

void F_Map_EmptySlow() /*clear screen pixel by pixel*/
{
	int x = v_map_top.X, y = v_map_top.Y;
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		gotoxy(x,y);
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gh_generate][gw_generate] = ' ';
			printf("%c", s_current_map.V_Map_Array[gh_generate][gw_generate]);
		}
		Sleep(10);
		++y;
	}
	gotoxy(0, 0);

}

void F_Map_Print()
{
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			printf("%c", s_current_map.V_Map_Array[gh_generate][gw_generate]);
		}
	}
}

void F_Map_Set_And_Print(int index)
{
	int x = v_map_top.X, y = v_map_top.Y;
	s_map_index.v_selected = index;

	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		gotoxy(x, y);
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gh_generate][gw_generate] = s_map_db[s_map_index.v_selected].V_Map_Array[gh_generate][gw_generate];

			if(s_current_map.V_Map_Array[gh_generate][gw_generate] != '~')
				printf("%c", s_current_map.V_Map_Array[gh_generate][gw_generate]);

			/* Stores the position and type of tiles that bullets can go through in a list */
			if (index >= 2)
			{
				/* STORING FOR IF POS X and POS Y  = TILE_ROAH_H */
				if (F_Get_Map_DataType(gw_generate, gh_generate) == TILE_ROAD_H)
				{
					listOfInvincibleTilesPosX[index-2][numOfInvincibleTiles[index-2]] = gw_generate;
					listOfInvincibleTilesPosY[index-2][numOfInvincibleTiles[index-2]] = gh_generate;
					listOfInvincibleTilesType[index-2][numOfInvincibleTiles[index-2]] = TILE_ROAD_H;
					numOfInvincibleTiles[index-2] = numOfInvincibleTiles[index - 2] + 1;
				}
				/* STORING FOR IF POS X and POS Y  = TILE_ROAH_V */
				else if (F_Get_Map_DataType(gw_generate, gh_generate) == TILE_ROAD_V)
				{
					listOfInvincibleTilesPosX[index - 2][numOfInvincibleTiles[index - 2]] = gw_generate;
					listOfInvincibleTilesPosY[index - 2][numOfInvincibleTiles[index - 2]] = gh_generate;
					listOfInvincibleTilesType[index - 2][numOfInvincibleTiles[index - 2]] = TILE_ROAD_V;
					numOfInvincibleTiles[index - 2] = numOfInvincibleTiles[index - 2] + 1;
				}
			}
		}
 		++y;
	}
 	printf("%d ", listOfInvincibleTilesPosX[index - 2][2]);
}

void F_Map_Instruction_Printout()
{
	/*
	gotoxy(d_game_width / 2, 2);
	printf("Welcome to GGPEN");
	*/
}

/*------------------------------------------------------------------------------
// Init
//----------------------------------------------------------------------------*/
void F_MapManager_Gameplay_Init(LevelType levelType)
{
	/* Init: mapWidth, mapHeight to 0 */
	mapWidth = mapHeight = 0;

	/* Render: Static environment "ONLY" once*/
	switch (levelType)
	{
		case Level_One:
			F_Map_Set_And_Print(2);
			break;
		case Level_Two:
			F_Map_Set_And_Print(3);
			break;
	}
	/* Get: player/enemy spawn point positions*/
	RetrieveSpawnPositionFromData(&player1SpawnPosX, &player1SpawnPosY, &player2SpawnPosX, &player2SpawnPosY, enemySpawnPosX, enemySpawnPosY);
}



/*------------------------------------------------------------------------------
// Setter & Getter
//----------------------------------------------------------------------------*/
/* Set: map[y][x] = TileType */
void F_Set_Map_DataType(char type, int x, int y)
{
	s_current_map.V_Map_Array[y][x] = type;
}

/* Get: TileType of map[?][?]*/
char F_Get_Map_DataType(int x, int y)
{
	if (x < 0 || x > d_game_width ||
		y < 0 || y > d_game_height)
		return -1;

	return s_current_map.V_Map_Array[y][x];
}

/* Get: Player 1 Spawn Point Position*/
Vector2D F_MapManager_GetPlayer1SpawnPosition()
{
	Vector2D pos;
	pos.X = player1SpawnPosX;
	pos.Y = player1SpawnPosY;
	pos.X = player1SpawnPosX;
	pos.Y = player1SpawnPosY;
	return pos;
}

/* Get: Player 2 Spawn Point Position*/
Vector2D F_MapManager_GetPlayer2SpawnPosition()
{
	Vector2D pos;
	pos.X = player2SpawnPosX;
	pos.Y = player2SpawnPosY;
	return pos;
}

/* Get: Playable Map Width*/
int F_MapManager_GetMapWidth()
{
	return mapWidth;
}

/* Get: Playable Map Height*/
int F_MapManager_GetMapHeight()
{
	return mapHeight;
}





/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Function: Load from csv + Assign data*/
void F_ReadFromCSVAndStore(char tempMap[d_game_height][d_game_width], int mapIndex)
{
	FILE *inFile;
	int tempNum = 0;
	int k = mapIndex;
	char buffer[512]; // The filename buffer.
	errno_t err;

	bool stop = false; //Use to retrieve mapWidth;

	snprintf(buffer, sizeof(char) * 64, "Map%i.csv", k);

	err = fopen_s(&inFile, buffer, "r");
	int x, y;
	x = y = 0;

	/*
	 * Init: all map elements to 0
	 */
	for (y = 0; y < d_game_height; ++y)
	{
		for (x = 0; x < d_game_width; ++x)
			tempMap[y][x] = '~';
	}
	int xCounter = 0;
	mapHeight = mapWidth = 0;

	if (err == 0)
	{
		/*
		 * Read each line from the file.
		 */
		for (y = 0; fgets(buffer, sizeof buffer, inFile); ++y)
		{
			xCounter = 0;
			for (x = 0; x < strlen(buffer); ++x)
			{
				if (buffer[x] != ',')
				{
					tempMap[y][xCounter] = buffer[x];

					if (!stop)
						mapWidth++;

					/*Need this for delimiter skipping*/
					xCounter++;
				}
			}
			/* Stop: checking for mapWidth, already done */
			stop = true;
		}

		/*Get: Playable Height*/
		mapHeight = y;
		mapWidth -= 1; //-'\0'
	}
	//if (err == 0)
	//{
	//	char buffer[BUFSIZ], *ptr;
	//	/*
	//	 * Read each line from the file.
	//	 */
	//	for (y = 0; fgets(buffer, sizeof buffer, inFile); ++y)
	//	{
	//		/*
	//		 * Parse the comma-separated values from each line into 'array'.
	//		 */
	//		for (x = 0, ptr = buffer; x < ARRAYSIZE(*tempMap); ++x, ++ptr)
	//		{
	//			/* Assign: map[y][x] = (int)TILE_??? */
	//			tempMap[y][x] = (int)strtol(ptr, &ptr, 10);

	//			/*Get: Playable Width*/
	//			if(!stop)
	//				mapWidth++;
	//		}

	//		/* Stop: checking for mapWidth, already done */
	//		stop = true;
	//	}

	//	/*Get: Playable Height*/
	//	mapHeight = y;
	//}
	else
	{
		printf_s("CHECK YOUR FILE NAME. FILE %d NOT FOUND\n", mapIndex);
	}


	fclose(inFile);
}

/* Function: Retrieve player/enemy spawn point positions from map[][]*/
void RetrieveSpawnPositionFromData(float *spawnPlayer1PosX, float *spawnPlayer1PosY, float *spawnPlayer2PosX, float *spawnPlayer2PosY, float *spawnEnemyPosX, float *spawnEnemyPosY)
{
	int x = 0;
	int y = 0;
	numOfEnemySpawnPoint = 0;

	for (y = 0; y < d_game_height; y++)
	{
		for (x = 0; x < d_game_width; x++)
		{
			/* Finding: Tile that represent "Player Spawn Point"*/
			if (s_current_map.V_Map_Array[y][x] == TILE_PLAYER_SPAWNER)
			{
				/*Record down: player spawn point ==> posX, posY*/
				*spawnPlayer1PosX = (float)x;
				*spawnPlayer1PosY = (float)y;

				/* Remove: remove spawner on the map[][], after retrieving the spawn position, we dont want it to be display out*/
				s_current_map.V_Map_Array[y][x] = TILE_EMPTY;
				F_DrawTile_Position(TILE_EMPTY, None, x, y);
			}

			/* Finding: Tile that represent "Player Spawn Point"*/
			else if (s_current_map.V_Map_Array[y][x] == TILE_PLAYER_SPAWNER_2)
			{
				/*Record down: player spawn point ==> posX, posY*/
				*spawnPlayer2PosX = (float)x;
				*spawnPlayer2PosY = (float)y;

				/* Remove: remove spawner on the map[][], after retrieving the spawn position, we dont want it to be display out*/
				s_current_map.V_Map_Array[y][x] = TILE_EMPTY;
				F_DrawTile_Position(TILE_EMPTY, None, x, y);
			}

			/* Finding: Tile that represent "Enemy Spawn Point"*/
			else if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_SPAWNER)
			{
				/* Check: Don't record down more than 5 spawn point, because we only have 5 lanes*/
				if (numOfEnemySpawnPoint >= d_MAX_ENEMY_SPAWN_POINT)
					return;

				/*Record down: enemy spawn point ==> posX, posY*/
				spawnEnemyPosX[numOfEnemySpawnPoint] = (float)x;
				spawnEnemyPosY[numOfEnemySpawnPoint] = (float)y;


				/* Track: Number of enemy spawn point*/
				numOfEnemySpawnPoint++;

				/* Remove: remove spawner on the map[][], after retrieving the spawn position, we dont want it to be display out*/
				s_current_map.V_Map_Array[y][x] = TILE_EMPTY;
				F_DrawTile_Position(TILE_EMPTY, None, x, y);
			}
		}
	}
}

float* F_MapManager_GetEnemySpawnPositionX()
{
	return enemySpawnPosX;
}
float* F_MapManager_GetEnemySpawnPositionY()
{
	return enemySpawnPosY;
}
int F_MapManager_GetEnemyTotalSpawnPoint()
{
	return numOfEnemySpawnPoint;
}


/*------------------------------------------------------------------------------
// Invincible tiles use
//----------------------------------------------------------------------------*/
char *GetInvincibleTilesListType()
{
	return listOfInvincibleTilesType;
}
int *GetInvincibleTilesListPosX()
{
	return listOfInvincibleTilesPosX;
}
int *GetInvincibleTilesListPosY()
{
	return listOfInvincibleTilesPosY;
}
int *F_GameObjectManager_GetNumOfInvincibleTiles()
{
	return numOfInvincibleTiles;
}