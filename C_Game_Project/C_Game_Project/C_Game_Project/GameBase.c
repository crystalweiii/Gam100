/*********************************************************************************************************************
Filename :	GameBase.h / GameBase.c
Author(s): Ngian Teck Wei
Login(s) : teckwei.ngian (100%)

Description/Features:
The basic start up of the program.
**********************************************************************************************************************/


#include "Header.h"
#include "GameBase.h"

void F_Game_Init()
{
	F_Graphic_Init();
	F_Map_Init();
	F_UI_Init();
	F_GSManager_Init();
}

void F_Game_Running()
{
	F_GSManager_RunningStateMachine();
}

