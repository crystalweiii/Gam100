#include "Menu.h"
#include "Graphic.h"
#include "Map.h"

#define Word_Amount 3

COORD Word_Pos_Top[Word_Amount];
COORD Word_Pos_Btm[Word_Amount];

COORD AlignPoint = { d_game_width / 2.5f , d_game_height / 3 };

int selector_ptr;

void F_MainMenu_De_Select();


void F_MainMenu_Init()
{
	selector_ptr = 0;
}

void F_MainMenu_SelectDefault()
{
	COORD top_position = { Word_Pos_Top[selector_ptr].X + v_map_top.X , Word_Pos_Top[selector_ptr].Y + v_map_top.Y };
	COORD btm_position = { (Word_Pos_Btm[selector_ptr].X + v_map_top.X) /8 , (Word_Pos_Btm[selector_ptr].Y + v_map_top.Y) /4 };

	F_Map_DrawBorder(top_position, btm_position);
}

void F_MainMenu_De_Select()
{
	COORD top_position = { Word_Pos_Top[selector_ptr].X + v_map_top.X , Word_Pos_Top[selector_ptr].Y + v_map_top.Y };
	COORD btm_position = { (Word_Pos_Btm[selector_ptr].X + v_map_top.X) / 8 , (Word_Pos_Btm[selector_ptr].Y + v_map_top.Y) / 4 };

    F_Map_DrawBorder_Asc(top_position, btm_position , 32 );
}


void F_MainMenu_Select(int dir)
{
	F_MainMenu_De_Select();
	if (dir > 0)
		if (selector_ptr < Word_Amount)
			selector_ptr += dir;
		else
			selector_ptr = 0;
	else
		if (selector_ptr > 0)
			selector_ptr += dir;
		else
			selector_ptr = Word_Amount;


	F_MainMenu_SelectDefault();
}



void F_Main_Menu_Print(char dc_array[d_game_width][d_game_height])
{
	char* Spaceneed[25]; /*25 max char*/
	int count;
	int space_between_char = 4;

	char play[] = "play";
	char credit[] = "credit";
	char exit[] = "exit";


	Word_Pos_Top[0].X = AlignPoint.X-1;
	Word_Pos_Top[0].Y = AlignPoint.Y-1;
	for (count = 0; count < 4; count++) {
		dc_array[AlignPoint.X + count][AlignPoint.Y] = play[count];
	}
	Word_Pos_Btm[0].X = AlignPoint.X + count ;
	Word_Pos_Btm[0].Y = AlignPoint.Y ;

	AlignPoint.Y += space_between_char;

	Word_Pos_Top[1].X = AlignPoint.X-1;
	Word_Pos_Top[1].Y = AlignPoint.Y-1;
	for (count = 0; count < 6; count++) {
		dc_array[AlignPoint.X + count][AlignPoint.Y] = credit[count];
	}
	Word_Pos_Btm[1].X = AlignPoint.X + count;
	Word_Pos_Btm[1].Y = AlignPoint.Y ;

	AlignPoint.Y += space_between_char;

	Word_Pos_Top[2].X = AlignPoint.X - 1;
	Word_Pos_Top[2].Y = AlignPoint.Y - 1;
	for (count = 0; count < 4; count++) {
		dc_array[AlignPoint.X + count][AlignPoint.Y] = exit[count];
	}
	Word_Pos_Btm[2].X = AlignPoint.X + count;
	Word_Pos_Btm[2].Y = AlignPoint.Y;
}