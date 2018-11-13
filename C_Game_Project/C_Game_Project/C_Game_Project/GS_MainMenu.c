#include "GS_MainMenu.h"
#include "Map.h"
#include "Menu.h"
/*Private function*/
void GS_MainMenu_InputCheck();


void GS_MainMenu_Init()
{
	F_MainMenu_Init();
	F_Map_Set_And_Print(1);
	F_MainMenu_SelectDefault();
}


void GS_MainMenu_Update()
{
	GS_MainMenu_InputCheck();
}

void GS_MainMenu_Exit()
{
	F_Map_EmptySlow();
}

void GS_MainMenu_InputCheck()
{
	/*Check for number 1 key hit*/
	if (f_Check_KeyDown_Once(0x73) || f_Check_KeyDown_Once(0x53) )
	{
		F_MainMenu_Select(1);
	}
}
