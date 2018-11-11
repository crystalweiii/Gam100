#include "Graphic.h"
#include "Map.h"
#include "GameObjectManager.h"
#include "WindowsHelper.h"

void F_Graphic_Init()
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle(TEXT("NANIIIIIIIII"));
	
	short lx,ly;
	WindowsHelper_GetLargestConsoleWindowSize(&lx, &ly);

	COORD bufferSize = { (double)(lx/1.2), (double)(lx/1.2) };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	
	SMALL_RECT windowSize =  { (double)0 , (double)0 ,  (double)lx/1.2-1 , (double)ly/1.2-1 };
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	
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

int F_ReadFromTextAndStore(char* url , char dc_array[d_game_width][d_game_height]) {
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
		for (t_gw = 0; t_gw < d_game_width; t_gw++)
		{
			dc_array[t_gw][t_heightCount] = str[t_gw];
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
	for (j = 0; j < btm.X; j++)
		printf("%c", 223);

	//Bottom border line... 
	gotoxy(top.X, top.Y + btm.Y);
	for (j = 0; j < btm.X; j++)
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
	for (j = 0; j < btm.X; j++)
		printf("%c", ascicode);

	//Bottom border line... 
	gotoxy(top.X, top.Y + btm.Y);
	for (j = 0; j < btm.X; j++)
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
/* Render: All Static objects like wall "ONCE" */
void F_Graphic_RenderStaticObject()
{
	/*
	 * Function Description: Draw only static object like wall "ONCE"
	 */

	int x, y;
	x = y = 0;

	for (y = 0; y < d_MAX_ROWS; y++)
	{
		for (x = 0; x < d_MAX_COLUMNS; x++)
		{
			/* Render: 1 desired tile at desired position*/
			F_DrawTile_Position((TileType)map[y][x], None, x, y);
		}

		/* Dont molest my '\n' */
		printf_s("\n");
	}
}

/* Render: Moving objects like player "LOOP" */
void F_Graphic_Draw()
{
	/*
	 * Function Description: Undraw gameObj.previousPos, Draw gameObj.currentPos
	 */

	int i;
	GameObj *objects = GetGameObjectList();
	int activeObjectCount = F_GameObjectManager_GetNumberInUse();
	int processed = 0;

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
			F_DrawScaleTile_Position(TILE_BULLET, objects[i].type, (int)objects[i].positionX, (int)objects[i].positionY, (int)objects[i].scaleX, (int)objects[i].scaleY,
																   (int)objects[i].anchorOffsetX, (int)objects[i].anchorOffsetY);

			/*Tracking: To optimize checking*/
			++processed;
		}

		/*Tracking the number of objects to draw*/
		if (processed >= activeObjectCount)
			return;

	}
}




/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Render: 1 tile to your desired position */
void F_DrawTile_Position(TileType tileType, ObjectType objType, int posX, int posY)
{
	/*
	 * Function Description: printf(ascii) and reassign map[y][x] = ? tileType
	 */

	/* Prevent: Array out of range */
	if (posY < 0 || posY >= d_MAX_ROWS ||
		posX < 0 || posX >= d_MAX_COLUMNS)
		return;

	/* Point to: position to print */
	gotoxy(posX, posY);

	/* Set: map[y][x] = tileType */
	F_Set_Map_DataType(tileType, posX, posY);

	/* Print: Draw ascii */
	if (tileType == TILE_INVALID)
		printf_s("-");
	else if (tileType == TILE_EMPTY)
		printf_s(" ");
	else if (tileType == TILE_WALL_TL)
		printf_s("%c", 201);
	else if (tileType == TILE_WALL_TR)
		printf_s("%c", 187);
	else if (tileType == TILE_WALL_BL)
		printf_s("%c", 200);
	else if (tileType == TILE_WALL_BR)
		printf_s("%c", 188);
	else if (tileType == TILE_WALL_H)
		printf_s("%c", 205);
	else if (tileType == TILE_WALL_V)
		printf_s("%c", 186);
	else if (tileType == TILE_PLAYER)
		printf_s("%c", 36);
	else if (tileType == TILE_ENEMY)
		printf_s("%c", 219);
	else if (tileType == TILE_BULLET)
		printf_s("%c", 62);
	else if (tileType == TILE_PLAYER_SPAWNER)
		printf_s("Q");
	else if (tileType == TILE_ENEMY_SPAWNER)
		printf_s("S");
	else if (tileType == TILE_PLAYER_DEFENSE)
	{
		WindowsHelper_ChangeTextcolor(LIGHTMAGENTA);
		printf_s("%c", 178);
		WindowsHelper_ChangeTextcolor(LIGHTGRAY);
	}
	else if (tileType == TILE_PLAYER_DEFENSE_DECORATION1)
	{
		WindowsHelper_ChangeTextcolor(LIGHTMAGENTA);
		printf_s("%c", 144);
		WindowsHelper_ChangeTextcolor(LIGHTGRAY);
	}
}

/* Render: scaled tile to your desired position */
void F_DrawScaleTile_Position(TileType tiletype, ObjectType objType, int posX, int posY, int scaleX, int scaleY, int anchorOffsetX, int anchorOffsetY)
{
	/*
	 * Function Description: Draw a character of (e.g) 3x3 and change color if needed
	 */

	int x, y;
	x = y = 0;

	if (objType == BulletRed || objType == EnemyRed)
	{

		WindowsHelper_ChangeTextcolor(LIGHTRED);

		for (x = 0; x < scaleX; ++x)
		{
			for (y = 0; y < scaleY; ++y)
			{
				F_DrawTile_Position(tiletype, objType, posX - anchorOffsetX + x, posY - anchorOffsetY + y);

			}
		}

		WindowsHelper_ChangeTextcolor(LIGHTGRAY);
	}
	else if (objType == BulletGreen || objType == EnemyGreen)
	{

		WindowsHelper_ChangeTextcolor(LIGHTGREEN);

		for (x = 0; x < scaleX; ++x)
		{
			for (y = 0; y < scaleY; ++y)
			{
				F_DrawTile_Position(tiletype, objType, posX - anchorOffsetX + x, posY - anchorOffsetY + y);

			}
		}

		WindowsHelper_ChangeTextcolor(LIGHTGRAY);
	}
	else if (objType == BulletBlue || objType == EnemyBlue)
	{

		WindowsHelper_ChangeTextcolor(LIGHTCYAN);

		for (x = 0; x < scaleX; ++x)
		{
			for (y = 0; y < scaleY; ++y)
			{
				F_DrawTile_Position(tiletype, objType, posX - anchorOffsetX + x, posY - anchorOffsetY + y);

			}
		}

		WindowsHelper_ChangeTextcolor(LIGHTGRAY);
	}
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
