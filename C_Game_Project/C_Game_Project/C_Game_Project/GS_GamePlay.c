#include "GS_GamePlay.h"
#include "Map.h"

void GS_GamePlay_Init()
{
	F_Map_Set_And_Print(2);
}

void GS_GamePlay_Update() 
{
	
}

void GS_GamePlay_Exit()
{
	F_Map_EmptySlow();
}

