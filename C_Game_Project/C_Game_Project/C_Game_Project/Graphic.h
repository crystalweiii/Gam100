#pragma once
#include "Header.h"
#include "GameObject.h"

HANDLE wHnd;    /* Handle to write to the console.*/
HANDLE rHnd;    /* Handle to read from the console.*/
CONSOLE_CURSOR_INFO cursorInfo;
				/*void gotoxy(int x, int y);*/

void F_Graphic_Init();

int F_ReadFromTextAndStore(char* url, char dc_array[d_game_width][d_game_height]);

void gotoxy(int x, int y);
void hideCursor();

/*Drawing border, Using top and btm coordinate only*/
void F_Map_DrawBorder(COORD top, COORD btm);
void F_Map_DrawBorder_Asc(COORD btm, COORD top, int ascicode);

/* Everything that handles the printing of the image on screen*/
void PrintImage(float posX, float posY, char image[ObjectSize]);
void ClearImage(float posX, float posY);

/*------------------------------------------------------------------------------
// Render
//----------------------------------------------------------------------------*/
/* Render: All Static objects like wall, "ONCE"*/
void F_Graphic_RenderStaticObject();

/* Render: All Moving objects like player "LOOP" */
void F_Graphic_Draw();

/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Render: 1 tile to your desired position */
void F_DrawTile_Position(TileType tileType, ObjectType objType, int posX, int posY);

/* Render: scaled tile to your desired position */
void F_DrawScaleTile_Position(TileType tiletype, ObjectType objType, int posX, int posY, int scaleX, int scaleY, int anchorOffsetX, int anchorOffsetY);
