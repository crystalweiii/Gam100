/*********************************************************************************************************************
Filename :	GS_StartUp.h / GS_StartUp.c
Author(s): Ngian Teck Wei
Login(s) : teckwei.ngian(100%)

Description/Features:
This is the start up page where it will print the digipen logo
**********************************************************************************************************************/

#include "GS_StartUp.h"
#include "Map.h"
#include "GameManager.h"

/*Private Function*/
void GS_StartUp_InputCheck();

void GS_StartUp_Init()
{
	F_Map_Set_And_Print(0);
	F_UI_Print_Out_Index(PT_Basic_Instruction);
}

void GS_StartUp_Update()
{
	GS_StartUp_InputCheck();
}

void GS_StartUp_Exit()
{
	F_UI_Clear_Index(PT_Basic_Instruction);
	F_Map_EmptySlow();
}

void GS_StartUp_InputCheck()
{
	if (f_Check_KeyDown(0x20))
	{
		F_GSManager_ChangeState(MainMenu);
	}
}