/*********************************************************************************************************************
Filename :	GS_MainMenu.h / GS_MainMenu.c
Author(s): Ngian Teck Wei
Login(s) : teckwei.ngian(100%)

Description/Features:
This is the main menu page which will be use to transition to game play page, credit page, and exit
**********************************************************************************************************************/

#include "GS_MainMenu.h"
#include "Map.h"
#include "Menu.h"
#include "GameManager.h"
#include "UiHandler.h"

/*Private var*/
COORD AlignPoint = { d_game_width / 2.5f , d_game_height / 3 };

#define Word_Amount 3

COORD Word_Pos_Top[Word_Amount];
COORD Word_Pos_Btm[Word_Amount];

int selector_ptr;

/*Private function*/
void GS_MainMenu_InputCheck();
void F_MainMenu_Select(int dir);


void GS_MainMenu_Init()
{
	selector_ptr = 0;

	F_Map_Set_And_Print(1);

	COORD top_position = { Word_Pos_Top[selector_ptr].X + v_map_top.X , Word_Pos_Top[selector_ptr].Y + v_map_top.Y };
	COORD btm_position = { (Word_Pos_Btm[selector_ptr].X - Word_Pos_Top[selector_ptr].X), (Word_Pos_Btm[selector_ptr].Y - Word_Pos_Top[selector_ptr].Y) };
	F_Menu_Select(top_position, btm_position);


	F_UI_Print_Out_Index(PT_Basic_Instruction);
}


void GS_MainMenu_Update()
{
	GS_MainMenu_InputCheck();
}

void GS_MainMenu_Exit()
{
	F_UI_Clear_Index(PT_Basic_Instruction);
	F_Map_EmptySlow();
}
/*For Input checking*/
void GS_MainMenu_InputCheck()
{
	/*for tranversing the menu and selection*/
	if (f_Check_KeyDown_Slow(0x27) || f_Check_KeyDown_Slow(0x28) )
	{
		F_MainMenu_Select(1);
	}

	if (f_Check_KeyDown_Slow(0x25) || f_Check_KeyDown_Slow(0x26))
	{
		F_MainMenu_Select(-1);
	}

	if (f_Check_KeyDown(0x20))
	{
		switch (selector_ptr)
		{
		case 0:
			F_GSManager_ChangeState(GamePlay);
			break;
		case 1:
			F_GSManager_ChangeState(Credit);
			break;
		case 2:
			F_GSManager_ChangeState(End);
			break;
		}
	}
}

/*Selection logic*/
void F_MainMenu_Select(int dir)
{
	COORD top_position = { Word_Pos_Top[selector_ptr].X + v_map_top.X , Word_Pos_Top[selector_ptr].Y + v_map_top.Y };
	COORD btm_position = { (Word_Pos_Btm[selector_ptr].X - Word_Pos_Top[selector_ptr].X)  , (Word_Pos_Btm[selector_ptr].Y - Word_Pos_Top[selector_ptr].Y) };

	F_Menu_De_Select(top_position, btm_position);
	if (dir > 0)
		if (selector_ptr < Word_Amount - 1)
			selector_ptr += dir;
		else
			selector_ptr = 0;
	else
		if (selector_ptr > 0)
			selector_ptr += dir;
		else
			selector_ptr = Word_Amount - 1;
	
	top_position.X = Word_Pos_Top[selector_ptr].X + v_map_top.X;
	top_position.Y = Word_Pos_Top[selector_ptr].Y + v_map_top.Y;

	btm_position.X = Word_Pos_Btm[selector_ptr].X - Word_Pos_Top[selector_ptr].X;
	btm_position.Y = Word_Pos_Btm[selector_ptr].Y - Word_Pos_Top[selector_ptr].Y;
	F_Menu_Select(top_position, btm_position);
}


/*Coding out the main menu and the intended choices*/
void F_Main_Menu_Print(char dc_array[d_game_height][d_game_width])
{
	char* Spaceneed[25]; /*25 max char*/
	int count;
	int space_between_char = 4;

	char play[] = "play";
	char credit[] = "credit";
	char exit[] = "exit";


	Word_Pos_Top[0].X = AlignPoint.X - 1;
	Word_Pos_Top[0].Y = AlignPoint.Y - 1;
	for (count = 0; count < 4; count++) {
		dc_array[AlignPoint.Y][AlignPoint.X + count] = play[count];
	}
	Word_Pos_Btm[0].X = AlignPoint.X + count + 1;
	Word_Pos_Btm[0].Y = AlignPoint.Y + 1;

	AlignPoint.Y += space_between_char;

	Word_Pos_Top[1].X = AlignPoint.X - 1;
	Word_Pos_Top[1].Y = AlignPoint.Y - 1;
	for (count = 0; count < 6; count++) {
		dc_array[AlignPoint.Y][AlignPoint.X + count] = credit[count];
	}
	Word_Pos_Btm[1].X = AlignPoint.X + count + 1;
	Word_Pos_Btm[1].Y = AlignPoint.Y + 1;

	AlignPoint.Y += space_between_char;

	Word_Pos_Top[2].X = AlignPoint.X - 1;
	Word_Pos_Top[2].Y = AlignPoint.Y - 1;
	for (count = 0; count < 4; count++) {
		dc_array[AlignPoint.Y][AlignPoint.X + count] = exit[count];
	}
	Word_Pos_Btm[2].X = AlignPoint.X + count + 1;
	Word_Pos_Btm[2].Y = AlignPoint.Y + 1;
}