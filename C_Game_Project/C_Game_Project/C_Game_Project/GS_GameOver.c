/*********************************************************************************************************************
Filename :	GS_GameOver.h / GS_GameOver.c
Author(s): Ong Jia Quan Joel
Login(s) : o.jiaquanjoel(100%)

Description/Features:
This is the gameover page which will be use to display score, transition to main menu page or restart
**********************************************************************************************************************/

#include "GS_GameOver.h"
#include "Map.h"
#include "Menu.h"
#include "GameManager.h"
#include "UiHandler.h"

/*Private var*/
COORD AlignPoint2 = { d_game_width / 2.5f , d_game_height / 3 };

#define gameover_ui_size 10
#define Word_Amount2 3
COORD Word_Pos_Top[Word_Amount2];
COORD Word_Pos_Btm[Word_Amount2];

int selector_ptr;

/*Private function*/
void GS_GameOver_InputCheck();
void F_GameOver_Select(int dir);

/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void GS_GameOver_Init()
{
	selector_ptr = 0;

	/* Print GameOver, restart, menu, exit */
	F_Map_Set_And_Print(7);

	/* Make all box same size*/
	Word_Pos_Btm[0].X = Word_Pos_Btm[1].X;
	Word_Pos_Btm[2].X = Word_Pos_Btm[1].X;

	/* Point */
	COORD top_position = { Word_Pos_Top[selector_ptr].X + v_map_top.X, Word_Pos_Top[selector_ptr].Y + v_map_top.Y };
	COORD btm_position = { (Word_Pos_Btm[selector_ptr].X - Word_Pos_Top[selector_ptr].X) + gameover_ui_size, (Word_Pos_Btm[selector_ptr].Y - Word_Pos_Top[selector_ptr].Y) };
	F_Menu_Select(top_position, btm_position);

	/* Draw instruction*/
	F_UI_Print_Out_Index(PT_Basic_Instruction);
	F_UI_Print_Out_Index(PT_Game_Info_Right);
	
}

void GS_GameOver_Update()
{
	GS_GameOver_InputCheck();
}

void GS_GameOver_Exit()
{
	F_UI_Clear_Index(PT_Basic_Instruction);
	F_Map_EmptySlow();
}


/*------------------------------------------------------------------------------
// Input Function
//----------------------------------------------------------------------------*/
/*For Input checking*/
void GS_GameOver_InputCheck()
{
	/*for tranversing the menu and selection*/
	if (f_Check_KeyDown_Slow(0x27) || f_Check_KeyDown_Slow(0x28))
	{
		F_GameOver_Select(1);
	}

	if (f_Check_KeyDown_Slow(0x25) || f_Check_KeyDown_Slow(0x26))
	{
		F_GameOver_Select(-1);
	}

	if (f_Check_KeyDown(0x20))
	{
		switch (selector_ptr)
		{
		case 0:
			F_GSManager_ChangeState(GamePlay);
			break;
		case 1:
			F_GSManager_ChangeState(MainMenu);
			break;
		case 2:
			F_GSManager_ChangeState(End);
			break;
		}
	}
}

/*Selection logic*/
void F_GameOver_Select(int dir)
{
	COORD top_position = { Word_Pos_Top[selector_ptr].X + v_map_top.X , Word_Pos_Top[selector_ptr].Y + v_map_top.Y };
	COORD btm_position = { (Word_Pos_Btm[selector_ptr].X - Word_Pos_Top[selector_ptr].X) + gameover_ui_size, (Word_Pos_Btm[selector_ptr].Y - Word_Pos_Top[selector_ptr].Y) };

	F_Menu_De_Select(top_position, btm_position);
	if (dir > 0)
		if (selector_ptr < Word_Amount2 - 1)
			selector_ptr += dir;
		else
			selector_ptr = 0;
	else
		if (selector_ptr > 0)
			selector_ptr += dir;
		else
			selector_ptr = Word_Amount2 - 1;

	top_position.X = Word_Pos_Top[selector_ptr].X + v_map_top.X;
	top_position.Y = Word_Pos_Top[selector_ptr].Y + v_map_top.Y;

	btm_position.X = Word_Pos_Btm[selector_ptr].X - Word_Pos_Top[selector_ptr].X + gameover_ui_size;
	btm_position.Y = Word_Pos_Btm[selector_ptr].Y - Word_Pos_Top[selector_ptr].Y;
	F_Menu_Select(top_position, btm_position);
}


