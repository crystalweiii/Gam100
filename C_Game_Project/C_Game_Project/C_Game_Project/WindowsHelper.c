/************************************************************************************************
Filename :	WindowsHelper.h / WindowsHelper.c
Author(s):  Ong Jia Quan Joel
Login(s) :	o.jiaquanjoel (100%)

Description/Features:
Handle Windows Properties

************************************************************************************************/

#include <windows.h>
#include "WindowsHelper.h"
#include "Header.h"

/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/
/* Handle: Windows stuff, not exposed to other parts of the game */
static HANDLE wHnd;		/* Handle: write to console  */
static HANDLE rHnd;		/* Handle: read from console */

/*------------------------------------------------------------------------------
// Init:
//----------------------------------------------------------------------------*/
void WindowsHelper_Init()
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	/*Hide Cursor*/
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(wHnd, &info);
}


/*------------------------------------------------------------------------------
// Setter and Getter:
//----------------------------------------------------------------------------*/
void WindowsHelper_SetCursorPosition(short x, short y)
{
	COORD center;
	center.X = x;
	center.Y = y;
	SetConsoleCursorPosition(wHnd, center);
}
void WindowsHelper_GetLargestConsoleWindowSize(short *width, short *height)
{
	if (width == NULL || height == NULL)
		return;


	COORD size = GetLargestConsoleWindowSize(wHnd);
	*width = size.X;
	*height = size.Y;
}
int WindowsHelper_GetConsoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(wHnd, &csbi);
	return csbi.dwSize.X;
}
int WindowsHelper_GetConsoleHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(wHnd, &csbi);
	return csbi.dwSize.Y;
}


/*------------------------------------------------------------------------------
// Utility:
//----------------------------------------------------------------------------*/
/* System: Set window to full screen*/
void WindowsHelper_FullScreen()
{
	short width = 0, height = 0;
	WindowsHelper_GetLargestConsoleWindowSize(&width, &height);

	COORD bufferSize;
	bufferSize.X = width;
	bufferSize.Y = height;
	SetConsoleScreenBufferSize(wHnd, bufferSize);


	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
}

/* Display: Change printf color*/
void WindowsHelper_ChangeTextcolor(int color)
{
	static int __BACKGROUND;

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


	GetConsoleScreenBufferInfo(wHnd, &csbiInfo);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		color + (__BACKGROUND << 4));
}

void WindowsHelper_ChangeBackgroundColor(BackgroundColorType type)
{
	static int BACKGROUND;

	if (type == BKG_GREY)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	else if (type == BKG_LIGHT_RED)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
	else if (type == BKG_LIGHT_BLUE)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	else if (type == BKG_LIGHT_GREEN)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	else if (type == BKG_LIGHT_YELLOW)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	else if (type == BKG_LIGHT_MAGENTA)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	else  if (type == BKG_LIGHT_CYAN)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	else  if (type == BKG_LIGHT_WHITE)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

	else if (type == BKG_DARK_RED)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
	else if (type == BKG_DARK_BLUE)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
	else if (type == BKG_DARK_GREEN)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
	else if (type == BKG_DARK_YELLOW)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN);
	else if (type == BKG_DARK_MAGENTA)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE);
	else  if (type == BKG_DARK_CYAN)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_BLUE);
	else  if (type == BKG_DARK_WHITE)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	else if (type == BKG_BLACK) /* TextColor: white, BackgroundColor: None*/
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 + (BACKGROUND << 4));
}

/* System: Clear screen*/
void WindowsHelper_ClearScreen()
{
	system("cls");
}