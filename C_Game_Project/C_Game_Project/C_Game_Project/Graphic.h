#pragma once
#include "Header.h"

HANDLE wHnd;    /* Handle to write to the console.*/
HANDLE rHnd;    /* Handle to read from the console.*/
CONSOLE_CURSOR_INFO cursorInfo;
				/*void gotoxy(int x, int y);*/

void F_Graphic_Init();

int F_ReadFromTextAndStore(char* url, char dc_array[d_game_width][d_game_height]);

void gotoxy(int x, int y);
void hideCursor();

/*Window helper*/
void WindowsHelper_GetLargestConsoleWindowSize(int *width, int* height);
void WindowsHelper_FullScreen();


/*Drawing border, Using top and btm coordinate only*/
void F_Map_DrawBorder(COORD btm, COORD top);
void F_Map_DrawBorder_Asc(COORD btm, COORD top, int ascicode);

/* Everything that handles the printing of the image on screen*/
void F_Graphic_Draw();
void PrintImage(float posX, float posY, char image[]);
void ClearImage(float posX, float posY);