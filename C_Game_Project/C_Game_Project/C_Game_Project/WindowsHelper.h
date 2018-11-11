#pragma once

/*------------------------------------------------------------------------------
// Init:
//----------------------------------------------------------------------------*/
void WindowsHelper_Init();


 /*------------------------------------------------------------------------------
 // Setter & Getter
 //----------------------------------------------------------------------------*/
void WindowsHelper_SetCursorPosition(short x, short y);
int WindowsHelper_GetConsoleWidth();
int WindowsHelper_GetConsoleHeight();
void WindowsHelper_GetLargestConsoleWindowSize(short *width, short *height);


 /*------------------------------------------------------------------------------
 // Utility
 //----------------------------------------------------------------------------*/
/* System: Set window to full screen*/
void WindowsHelper_FullScreen();

/* System: Clear screen*/
void WindowsHelper_ClearScreen();

/* Display: Change printf color*/
void WindowsHelper_ChangeTextcolor(int color);