#include "Map.h"
#include <stdbool.h>

/*--------------------------------
// Private Variable Declaration
--------------------------------*/
float playerSpawnPosX = 0;
float playerSpawnPosY = 0;
float enemySpawnPosX[d_MAX_ENEMY_SPAWN_POINT];
float enemySpawnPosY[d_MAX_ENEMY_SPAWN_POINT];
int numOfEnemySpawnPoint = 0;

/*--------------------------------
// Private Function Declaration
--------------------------------*/
void F_ReadFromCSVAndStore(int tempMap[d_game_height][d_game_width], int mapIndex);
void RetrieveSpawnPositionFromData(float *spawnPlayerPosX, float *spawnPlayerPosY, float *spawnEnemyPosX, float *spawnEnemyPosY);


COORD v_border_top = { 3,4 };

/*COORD v_border_btm;*/

COORD v_map_buffer = { 4, 2 };


COORD v_map_top = { 3 + 2, 4 + 1 };

void F_Map_Init()
{
	/*Init border btm with the buffers*/
	COORD v_temp_border_btm = { d_game_width + v_map_buffer.X, d_game_height + v_map_buffer.Y };
	
	COORD v_Text_border_Top = { v_border_top.X ,  v_temp_border_btm.Y + 3 };
	COORD v_Text_border_Btm = { d_game_width + v_map_buffer.X , 10 };
	
	v_border_btm = v_temp_border_btm;


	F_Map_DrawBorder(v_border_top, v_border_btm);
	F_Map_DrawBorder(v_Text_border_Top, v_Text_border_Btm);


	F_ReadFromTextAndStore(txt_DGPLogo , s_map_db[0].V_Map_Array);
	F_Main_Menu_Print(s_map_db[1].V_Map_Array);

	/* "Read" & "Store": gameplay level 1 map data from csv*/
	//F_ReadFromCSVAndStore(s_map_db[2].V_Map_Array, Level_One);

	F_ReadFromTextAndStore(txt_Map1, s_map_db[2].V_Map_Array);
	
	

	s_map_index.v_amount = d_map_amount;
	s_map_index.v_current = 0;
	s_map_index.v_selected = 0;
	
	/*F_Map_Set_And_Print(s_map_index.v_selected);*/

	F_Map_Instruction_Printout();
	
	/*F_Map_Set_And_Print(s_map_index.v_current);*/
}

void F_Map_Set(int index) /*set index to the current map*/
{
	s_map_index.v_selected = index;
	s_map_index.v_current = index;
}

void F_Map_Empty() /*clear screen*/
{
	int x = v_map_top.X, y = v_map_top.Y;
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		gotoxy(x,y);
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gw_generate][gh_generate] = ' ';
			printf("%c", s_current_map.V_Map_Array[gw_generate][gh_generate]);
		}
		++y;
	}
}

void F_Map_EmptySlow() /*clear screen*/
{
	int x = v_map_top.X, y = v_map_top.Y;
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		gotoxy(x,y);
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gw_generate][gh_generate] = ' ';
			printf("%c", s_current_map.V_Map_Array[gw_generate][gh_generate]);
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
			printf("%c", s_current_map.V_Map_Array[gw_generate][gh_generate]);
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
			s_current_map.V_Map_Array[gw_generate][gh_generate] = s_map_db[s_map_index.v_selected].V_Map_Array[gw_generate][gh_generate];
			printf("%c", s_current_map.V_Map_Array[gw_generate][gh_generate]);
			
		}
		++y;
	}
}

void F_Map_Instruction_Printout()
{
	gotoxy(d_game_width / 2, 2);
	printf("Welcome to GGPEN");
}

/*------------------------------------------------------------------------------
// Init
//----------------------------------------------------------------------------*/
void F_MapManager_Gameplay_Init(LevelType levelType)
{
	/* Init: mapWidth, mapHeight to 0 */
	mapWidth = mapHeight = 0;

	/* Get: map data from CSV */
	F_ReadFromCSVAndStore(map, (int)levelType);

	/* Get: player/enemy spawn point positions*/
	RetrieveSpawnPositionFromData(&playerSpawnPosX, &playerSpawnPosY, enemySpawnPosX, enemySpawnPosY);
}



/*------------------------------------------------------------------------------
// Setter & Getter
//----------------------------------------------------------------------------*/
/* Set: map[y][x] = TileType */
void F_Set_Map_DataType(TileType type, int x, int y)
{
	map[y][x] = (int)type;
}

/* Get: TileType of map[?][?]*/
TileType F_Get_Map_DataType(int x, int y)
{
	if (x < 0 || x > d_MAX_COLUMNS ||
		y < 0 || y > d_MAX_ROWS)
		return -1;

	return (TileType)map[y][x];
}

/* Get: Player Spawn Point Position*/
Vector2D F_MapManager_GetPlayerSpawnPosition()
{
	Vector2D pos;
	pos.X = playerSpawnPosX;
	pos.Y = playerSpawnPosY;
	return pos;
}

/* Get: Playable Map Width*/
int F_MapManager_GetMapWidth()
{
	return mapWidth-1;
}

/* Get: Playable Map Height*/
int F_MapManager_GetMapHeight()
{
	return mapHeight-1;
}





/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Function: Load from csv + Assign data*/
void F_ReadFromCSVAndStore(int tempMap[d_game_height][d_game_width], int mapIndex)
{
	FILE *inFile;
	int tempNum = 0;
	int k = mapIndex;
	char buffer[64]; // The filename buffer.
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
			tempMap[y][x] = 0;
	}

	if (err == 0)
	{
		char buffer[BUFSIZ], *ptr;
		/*
		 * Read each line from the file.
		 */
		for (y = 0; fgets(buffer, sizeof buffer, inFile); ++y)
		{
			/*
			 * Parse the comma-separated values from each line into 'array'.
			 */
			for (x = 0, ptr = buffer; x < ARRAYSIZE(*tempMap); ++x, ++ptr)
			{
				/* Assign: map[y][x] = (int)TILE_??? */
				tempMap[y][x] = (int)strtol(ptr, &ptr, 10);

				/*Get: Playable Width*/
				if(!stop)
					mapWidth++;
			}

			/* Stop: checking for mapWidth, already done */
			stop = true;
		}

		/*Get: Playable Height*/
		mapHeight = y;
	}
	else
	{
		printf_s("CHECK YOUR FILE NAME. FILE %d NOT FOUND\n", mapIndex);
	}


	fclose(inFile);
}

/* Function: Retrieve player/enemy spawn point positions from map[][]*/
void RetrieveSpawnPositionFromData(float *spawnPlayerPosX, float *spawnPlayerPosY, float *spawnEnemyPosX, float *spawnEnemyPosY)
{
	/* Clean: set all data bytes to be 0 */
	memset(spawnEnemyPosX, 0, sizeof(float)*d_MAX_ENEMY_SPAWN_POINT);
	memset(spawnEnemyPosY, 0, sizeof(float)*d_MAX_ENEMY_SPAWN_POINT);

	int x = 0;
	int y = 0;

	for (y = 0; y < d_MAX_ROWS; y++)
	{
		for (x = 0; x < d_MAX_COLUMNS; x++)
		{
			/* Finding: Tile that represent "Player Spawn Point"*/
			if ((TileType)map[y][x] == TILE_PLAYER_SPAWNER)
			{
				/*Record down: player spawn point ==> posX, posY*/
				*spawnPlayerPosX = (float)x;
				*spawnPlayerPosY = (float)y;

				/* Remove: remove spawner on the map[][], after retrieving the spawn position, we dont want it to be display out*/
				(TileType)map[y][x] = TILE_EMPTY;
			}

			/* Finding: Tile that represent "Enemy Spawn Point"*/
			else if ((TileType)map[y][x] == TILE_ENEMY_SPAWNER)
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
				(TileType)map[y][x] = TILE_EMPTY;
			}
		}
	}
}

/* Retrieve: Enemy Spawn Point[] positions*/
void F_MapManager_GetEnemySpawnPosition(float *spawnEnemyPosX, float *spawnEnemyPosY, int *noOfSpawnPoint)
{
	*noOfSpawnPoint = 0;

	int x = 0;
	int y = 0;

	for (y = 0; y < d_MAX_ROWS; y++)
	{
		for (x = 0; x < d_MAX_COLUMNS; x++)
		{
			if ((TileType)map[y][x] == TILE_ENEMY_SPAWNER)
			{
				if (*noOfSpawnPoint >= d_MAX_ENEMY_SPAWN_POINT)
					return;

				spawnEnemyPosX[*noOfSpawnPoint] = (float)x;
				spawnEnemyPosY[*noOfSpawnPoint] = (float)y;


				/* Track: Number of enemy spawn point*/
				*noOfSpawnPoint++;

				/* Remove: remove spawner, after retrieving the spawn position*/
				(TileType)map[y][x] = TILE_EMPTY;
			}
		}
	}
}
