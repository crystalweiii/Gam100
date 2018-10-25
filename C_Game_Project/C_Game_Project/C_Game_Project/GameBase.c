#include "Header.h"
#include "GameBase.h"

void F_Game_Init()
{
	F_Graphic_Init();
	F_Map_Init();
	F_GSManager_Init();

	F_Basic_Instruction_Printout();
	
}

void F_Game_Running()
{
	dt = time(NULL) / 3600;
	F_GSManager_RunningState(&dt);
}

