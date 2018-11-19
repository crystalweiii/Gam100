/************************************************************************************************
Filename :	Graphic.h / Graphic.c
Author(s):	Ong Jia Quan Joel, Teck Wei
Login(s) :	o.jiaquanjoel(30%), teck wei(70%)

Description/Features:
This file contains reading from .txt file.
It also contains function to print out ASCII characters.

************************************************************************************************/

#include "Graphic.h"
#include "Map.h"
#include "GameObjectManager.h"
#include "LevelManager.h"
#include "WindowsHelper.h"

void F_Graphic_Init()
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle(TEXT("NANIIIIIIIII"));
	/*
	short lx,ly;
	WindowsHelper_GetLargestConsoleWindowSize(&lx, &ly);
	
	COORD bufferSize = { ly/2, lx/2 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	

	SMALL_RECT windowSize =  { 0 , 0 ,  100 , 180};
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	*/
	/*WindowsHelper_FullScreen();*/
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(wHnd, c);
}

void hideCursor()
{
	GetConsoleCursorInfo(wHnd, &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(wHnd, &cursorInfo);
}

int F_ReadFromTextAndStore(char* url , char dc_array[d_game_height][d_game_width]) {
	errno_t err;
	FILE *fp;
	char str[d_maxchar];
	char* filename = url;

	int t_widthCount = 0, t_heightCount = 0;

	err = fopen_s(&fp, filename, "r");
	if(err != 0) //if (err != NULL) <-- warning 
	{
		printf("Could not open file %s", filename);
		return 1;
	}
	while (fgets(str, d_maxchar, fp) != NULL)
	{
		/*printf("%s", str);*/
		int t_gw = 0;
		for (t_gw = 0; t_gw < strlen(str); t_gw++)//for (t_gw = 0; t_gw < d_game_width; t_gw++)
		{
			dc_array[t_heightCount][t_gw] = str[t_gw];
			/*s_map_db[s_map_index.v_selected].V_Map_Array[t_gw][t_heightCount] = s_current_map.V_Map_Array[t_gw][t_heightCount];*/
		}

		t_heightCount++;
	}
	fclose(fp);

	return 0;
}

void F_Map_DrawBorder(COORD top, COORD btm)
{
	int j;

	//Top border line...
	gotoxy(top.X, top.Y);
	for (j = 0; j <= btm.X; j++)
		printf("%c", 223);

	//Bottom border line... 
	gotoxy(top.X, top.Y + btm.Y);
	for (j = 0; j <= btm.X; j++)
		printf("%c", 223);

	//Left and Right border line...
	for (j = 0; j < btm.Y; j++)
	{
		gotoxy(top.X, top.Y + j);
		printf("%c", 219);

		gotoxy(top.X + btm.X, top.Y + j);
		printf("%c", 219);
	}
	printf("\n");
}

void F_Map_DrawBorder_Asc(COORD top, COORD btm, int ascicode)
{
	int j;
	//Top border line...
	gotoxy(top.X, top.Y);
	for (j = 0; j <= btm.X; j++)
		printf("%c", ascicode);

	//Bottom border line... 
	gotoxy(top.X, top.Y + btm.Y);
	for (j = 0; j <= btm.X; j++)
		printf("%c", ascicode);

	//Left and Right border line...
	for (j = 0; j < btm.Y; j++)
	{
		gotoxy(top.X, top.Y + j);
		printf("%c", ascicode);

		gotoxy(top.X + btm.X, top.Y + j);
		printf("%c", ascicode);
	}
	printf("\n");
}

void PrintImage(float posX, float posY, char image[ObjectSize])
{
	int j;
	int offsetX = 0, offsetY = 0;
	for (j = 0; j < ObjectSize; ++j)
	{
		if (j != 0 && j % 3 == 0)
		{
			offsetY += 1;
			offsetX = 0;
		}
		gotoxy((short)posX + offsetX, (short)posY + offsetY);
		printf_s("%c", image[j]);
		offsetX += 1;
	}
}

void ClearImage(float posX, float posY)
{
	int j;
	int offsetX = 0, offsetY = 0;
	for (j = 0; j < ObjectSize; ++j)
	{
		if (j != 0 && j % 3 == 0)
		{
			offsetY += 1;
			offsetX = 0;
		}
		gotoxy((short)posX + offsetX, (short)posY + offsetY);
		printf_s("%c", ' ');
		offsetX += 1;
	}
}




/*------------------------------------------------------------------------------
// Render
//----------------------------------------------------------------------------*/
/* Render: Moving objects like player "LOOP" */
void F_Graphic_Draw()
{
	/*
	 * Function Description: Undraw gameObj.previousPos, Draw gameObj.currentPos
	 */

	int i;
	GameObj *objects = GetGameObjectList();
	int processed = 0;

	/* Data for printing the invisible tiles */
	char (*listOfInvincibleTilesType)[d_MAX_INVINCIBLE_TILES] = GetInvincibleTilesListType();
	int (*listOfInvincibleTilesPosX)[d_MAX_INVINCIBLE_TILES] = GetInvincibleTilesListPosX();
	int (*listOfInvincibleTilesPosY)[d_MAX_INVINCIBLE_TILES] = GetInvincibleTilesListPosY();
	int *arrOfMaxInvincibleTiles = F_GameObjectManager_GetNumOfInvincibleTiles();

	int currentLevel = F_LevelManager_GetCurrentLevel();
	int activeObjectCount = F_GameObjectManager_GetNumberInUse();

	///* Prints invincible tiles constantly */
	//for (i = 0; i < d_MAX_INVINCIBLE_TILES; ++i)
	//{
	//	if (i < arrOfMaxInvincibleTiles[currentLevel])
	//	{
	//		gotoxy(*(*(listOfInvincibleTilesPosX + F_LevelManager_GetCurrentLevel()) + i), *(*(listOfInvincibleTilesPosY + F_LevelManager_GetCurrentLevel()) + i));
	//		printf("%c", '=');
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}

	for (i = 0; i < d_MAX_GAMEOBJECTS; ++i)
	{
		if (objects[i].type == Player)
		{
			/* Render: Render EMPTY at previous position*/
			F_DrawScaleTile_Position(TILE_EMPTY, None, (int)objects[i].prevPositionX, (int)objects[i].prevPositionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
													   (int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);
			/* Remove: Render PLAYER at new position*/
			F_DrawScaleTile_Position(TILE_PLAYER, None, (int)objects[i].positionX, (int)objects[i].positionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
														(int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);

			/*Tracking: To optimize checking*/
			++processed;
		}
		else if (objects[i].type == EnemyRed || objects[i].type == EnemyGreen || objects[i].type == EnemyBlue)
		{
			/* Render: Render EMPTY at previous position*/
			F_DrawScaleTile_Position(TILE_EMPTY, None, (int)objects[i].prevPositionX, (int)objects[i].prevPositionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
													   (int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);
			/* Remove: Render ENEMY at position*/
			F_DrawScaleTile_Position(TILE_ENEMY, objects[i].type, (int)objects[i].positionX, (int)objects[i].positionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
																  (int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);

			/*Tracking: To optimize checking*/
			++processed;
		}

		else if (objects[i].type == BulletRed || objects[i].type == BulletGreen || objects[i].type == BulletBlue)
		{
			/* Render: Render EMPTY at previous position*/
			F_DrawScaleTile_Position(TILE_EMPTY, None, (int)objects[i].prevPositionX, (int)objects[i].prevPositionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
													   (int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);
			/* Remove: Render ENEMY at position*/
			if(objects[i].directionX == 1) /* render correct image according to direction */
				F_DrawScaleTile_Position(TILE_BULLET_1, objects[i].type, (int)objects[i].positionX, (int)objects[i].positionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
																(int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);

			else if (objects[i].directionY == -1) /* render correct image according to direction */
			F_DrawScaleTile_Position(TILE_BULLET_2, objects[i].type, (int)objects[i].positionX, (int)objects[i].positionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
				(int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);

			/*Tracking: To optimize checking*/
			++processed;
		}

		else if (objects[i].type == BlockerUp && objects[i].isVisible == true)
		{
			/* Render: Render TILE_ENEMY_MOVEUP*/
			F_DrawScaleTile_Position(TILE_ENEMY_MOVEUP, None, (int)objects[i].positionX, (int)objects[i].positionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
				(int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);
		}
		else if (objects[i].type == BlockerDown && objects[i].isVisible == true)
		{
			/* Render: Render TILE_ENEMY_MOVEUP*/
			F_DrawScaleTile_Position(TILE_ENEMY_MOVEDOWN, None, (int)objects[i].positionX, (int)objects[i].positionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
				(int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);
		}
		else if (objects[i].type == BlockerLeft && objects[i].isVisible == true)
		{
			/* Render: Render TILE_ENEMY_MOVELEFT*/
			F_DrawScaleTile_Position(TILE_ENEMY_MOVELEFT, None, (int)objects[i].positionX, (int)objects[i].positionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
				(int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);
		}
		else if (objects[i].type == BlockerRight && objects[i].isVisible == true)
		{
			/* Render: Render TILE_ENEMY_MOVERIGHT*/
			F_DrawScaleTile_Position(TILE_ENEMY_MOVERIGHT, None, (int)objects[i].positionX, (int)objects[i].positionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
				(int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);
		}

		/*Tracking the number of objects to draw*/
		if (processed >= activeObjectCount)
			break;

	}

	
}




/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Render: 1 tile background color*/
void F_DrawTileBackGround_Position(int posX, int posY)
{
}

/* Render: 1 tile to your desired position */
void F_DrawTile_Position(char tileType, ObjectType objType, int posX, int posY)
{
	/*
	 * Function Description: printf(ascii) and reassign map[y][x] = ? tileType
	 */

	/* Prevent: Array out of range */
	if (posY < 0 || posY >= d_game_height ||
		posX < 0 || posX >= d_game_width)
		return;

	/* Point to: position to print */
	gotoxy(posX, posY);

	/* Set: map[y][x] = tileType */
	F_Set_Map_DataType(tileType, posX, posY);

	/* Enable: Color*/
	/*if (tileType == TILE_PLAYER_DEFENSE)
		WindowsHelper_ChangeTextcolor(LIGHTMAGENTA);*/

	/* Draw: Background color */
	int bcT = F_Map_Get_Background_DataType(posX, posY);
	if (bcT >= 0)
	{
		WindowsHelper_ChangeBackgroundColor((BackgroundColorType)bcT);
	}
	/* Draw: ASCII */
	printf_s("%c", tileType);

	/* Disable: color*/
	/*if (tileType == TILE_PLAYER_DEFENSE)
		WindowsHelper_ChangeTextcolor(LIGHTGRAY);*/
}

/* Render: scaled tile to your desired position */
void F_DrawScaleTile_Position(char tiletype, ObjectType objType, int posX, int posY, int scaleX, int scaleY, int anchorOffsetX, int anchorOffsetY)
{
	/*
	 * Function Description: Draw a character of (e.g) 3x3 and change color if needed
	 */

	int x, y;
	x = y = 0;

	if (objType == BulletRed || objType == EnemyRed)
	{

		//WindowsHelper_ChangeTextcolor(LIGHTRED);

		for (x = 0; x < scaleX; ++x)
		{
			for (y = 0; y < scaleY; ++y)
			{
				F_DrawTile_Position(tiletype, objType, posX - anchorOffsetX + x, posY - anchorOffsetY + y);
			}
		}

		//WindowsHelper_ChangeTextcolor(LIGHTGRAY);
	}
	else if (objType == BulletGreen || objType == EnemyGreen)
	{

		//WindowsHelper_ChangeTextcolor(LIGHTGREEN);

		for (x = 0; x < scaleX; ++x)
		{
			for (y = 0; y < scaleY; ++y)
			{
				F_DrawTile_Position(tiletype, objType, posX - anchorOffsetX + x, posY - anchorOffsetY + y);
			}
		}

		//WindowsHelper_ChangeTextcolor(LIGHTGRAY);
	}
	else if (objType == BulletBlue || objType == EnemyBlue)
	{

		//WindowsHelper_ChangeTextcolor(LIGHTCYAN);

		for (x = 0; x < scaleX; ++x)
		{
			for (y = 0; y < scaleY; ++y)
			{
				F_DrawTile_Position(tiletype, objType, posX - anchorOffsetX + x, posY - anchorOffsetY + y);

			}
		}

		//WindowsHelper_ChangeTextcolor(LIGHTGRAY);
	}

	/* Others thats not do not need coloring*/
	else 
	{
		for (x = 0; x < scaleX; ++x)
		{
			for (y = 0; y < scaleY; ++y)
			{
				F_DrawTile_Position(tiletype, objType, posX - anchorOffsetX + x, posY - anchorOffsetY + y);

			}
		}
	}


}
