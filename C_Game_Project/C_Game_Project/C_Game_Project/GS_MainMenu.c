#include "GS_MainMenu.h"
#include "Map.h"

void GS_MainMenu_Init()
{
	F_Map_Set_And_Print(1);
}


void GS_MainMenu_Update()
{


}

void GS_MainMenu_Exit()
{
	F_Map_EmptySlow();
}

