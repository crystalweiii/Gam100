#include "GS_StartUp.h"
#include "Map.h"
void GS_StartUp_Init()
{
	F_Map_Set_And_Print(0);
}

void GS_StartUp_Update()
{

}

void GS_StartUp_Exit()
{
	F_Map_EmptySlow();
}

