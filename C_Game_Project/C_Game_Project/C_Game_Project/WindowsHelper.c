#include <windows.h>
#include "WindowsHelper.h"

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

/* System: Clear screen*/
void WindowsHelper_ClearScreen()
{
	system("cls");
}