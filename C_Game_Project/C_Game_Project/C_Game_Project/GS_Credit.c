#include "GS_Credit.h"
#include "UiHandler.h"
#include "Map.h"
#include "GameManager.h"
#include "Graphic.h"

void GS_Credit_Init()
{
	F_UI_Print_Out_Index(PT_Basic_Instruction);
	GS_Credit_Print();
}


void GS_Credit_Update()
{
	GS_Credit_InputCheck();
}

void GS_Credit_Exit()
{
	F_UI_Clear_Index(PT_Basic_Instruction);
	F_Map_EmptySlow();
}

void GS_Credit_InputCheck()
{
	if (f_Check_KeyDown(0x20))
	{
		F_GSManager_ChangeState(MainMenu);
	}
}

void GS_Credit_Print()
{
	COORD startPT = { d_game_width / 3, d_game_height / 4 };

	gotoxy(startPT.X, startPT.Y);
	printf("Game Producer: Desmond Yeo");

	gotoxy(startPT.X, startPT.Y + 4);
	printf("Lead Programmer/Art director: Joel Ong");

	gotoxy(startPT.X, startPT.Y + 8);
	printf("Level Designer/Programmer: Darren Low");

	gotoxy(startPT.X, startPT.Y + 12);
	printf("Ui Programmer: Ngian Teck Wei");


	COORD trollStartPt = { d_game_width / 8, d_game_height / 6 };
	COORD trollEndPt = { 8, 4 };
	F_Graphic_DrawSquare_Asc(trollStartPt, trollEndPt, '#');


	COORD trollStartPt2 = { d_game_width / 1.5, d_game_height / 6 };
	F_Graphic_DrawSquare_Asc(trollStartPt2, trollEndPt, '@');

	COORD trollStartPt3 = { d_game_width / 8, d_game_height / 1.5 };
	F_Graphic_DrawSquare_Asc(trollStartPt3, trollEndPt, '$');


	COORD trollStartPt4 = { d_game_width / 1.5, d_game_height / 1.5 };
	F_Graphic_DrawSquare_Asc(trollStartPt4, trollEndPt, '%');
}