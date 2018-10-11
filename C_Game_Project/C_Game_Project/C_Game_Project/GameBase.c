#include "Header.h"
#include "GameBase.h"

void F_GameBase()
{
	F_Graphic_Init();
	F_Map_Init();
	F_GSManager_Init();

	F_Basic_Instruction_Printout();
	F_GSManager_RunningState();
}

void F_Basic_Instruction_Printout()
{
	COORD v_temp_startSpot = { v_border_btm.X + 5 , (v_border_btm.Y) / 2.5 };
	gotoxy(v_temp_startSpot.X, v_temp_startSpot.Y);
	printf("Press P to quit");

	gotoxy(v_temp_startSpot.X, v_temp_startSpot.Y + 1);
	printf("Press R for first map");

	gotoxy(v_temp_startSpot.X, v_temp_startSpot.Y + 2);
	printf("Press T for second map");
}