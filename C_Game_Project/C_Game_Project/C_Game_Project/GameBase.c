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
	F_GSManager_RunningStateMachine();
}

