/*********************************************************************************************************************
Filename :	GS_MainMenu.h / GS_MainMenu.c
Author(s): Ngian Teck Wei
Login(s) : teckwei.ngian(100%)

Description/Features:
This is the main menu page which will be use to transition to game play page, credit page, and exit
**********************************************************************************************************************/


#include "Header.h"
extern void GS_MainMenu_Init();

extern void GS_MainMenu_Update();

extern void GS_MainMenu_Exit();

void F_Main_Menu_Print(char dc_array[d_game_width][d_game_height]);