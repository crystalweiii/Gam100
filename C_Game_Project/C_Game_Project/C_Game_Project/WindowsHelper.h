/************************************************************************************************
Filename :	WindowsHelper.h / WindowsHelper.c
Author(s):  Ong Jia Quan Joel
Login(s) :	o.jiaquanjoel (100%)

Description/Features:
Handle Windows Properties

************************************************************************************************/

#pragma once
#include "Header.h"

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

/* Change: Color of text and background */
void WindowsHelper_ChangeColor(int foreground, int background);

/* Reset: Back to original text and background color*/
void WindowsHelper_Reset_DefaultColor();

/* Draw: Color + Draw  + ResetColor */
void WindowsHelper_Print_ChangeColor_And_Reset(int foreground, int background, char* printout);