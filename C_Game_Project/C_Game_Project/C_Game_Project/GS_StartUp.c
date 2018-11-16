/*********************************************************************************************************************
Filename :	GS_StartUp.h / GS_StartUp.c
Author(s):
Login(s) :

Description/Features:
...

**********************************************************************************************************************/


#include "GS_StartUp.h"
#include "Map.h"
#include "GameManager.h"

/*Private Function*/
void GS_StartUp_InputCheck();

void GS_StartUp_Init()
{
	F_Map_Set_And_Print(0);
}

void GS_StartUp_Update()
{
	GS_StartUp_InputCheck();
}

void GS_StartUp_Exit()
{
	F_Map_EmptySlow();
}

void GS_StartUp_InputCheck()
{
	if (f_Check_KeyDown(0x20))
	{
		F_GSManager_ChangeState(MainMenu);
	}
}