#include "Map.h"


COORD v_border_top = { 3,4 };

/*COORD v_border_btm;*/

COORD v_map_buffer = { 4, 2 };


COORD v_map_top = { 3 + 2, 4 + 1 };

void F_Map_Init()
{
	/*Init border btm with the buffers*/
	COORD v_temp_border_btm = { d_game_width + v_map_buffer.X, d_game_height + v_map_buffer.Y };
	
	COORD v_Text_border_Top = { v_border_top.X ,  v_temp_border_btm.Y + 3 };
	COORD v_Text_border_Btm = { d_game_width + v_map_buffer.X , 10 };
	
	v_border_btm = v_temp_border_btm;


	F_Map_DrawBorder(v_border_top, v_border_btm);
	F_Map_DrawBorder(v_Text_border_Top, v_Text_border_Btm);


	F_ReadFromTextAndStore(txt_DGPLogo , s_map_db[0].V_Map_Array);
	F_Main_Menu_Print(s_map_db[1].V_Map_Array);

	F_ReadFromTextAndStore(txt_Map1, s_map_db[2].V_Map_Array);
	

	s_map_index.v_amount = d_map_amount;
	s_map_index.v_current = 0;
	s_map_index.v_selected = 0;
	
	/*F_Map_Set_And_Print(s_map_index.v_selected);*/

	F_Map_Instruction_Printout();
	
	/*F_Map_Set_And_Print(s_map_index.v_current);*/
}




void F_Map_Set(int index) /*set index to the current map*/
{
	s_map_index.v_selected = index;
	s_map_index.v_current = index;
}

void F_Map_Empty() /*clear screen*/
{
	int x = v_map_top.X, y = v_map_top.Y;
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		gotoxy(x,y);
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gw_generate][gh_generate] = ' ';
			printf("%c", s_current_map.V_Map_Array[gw_generate][gh_generate]);
		}
		++y;
	}
}

void F_Map_EmptySlow() /*clear screen*/
{
	int x = v_map_top.X, y = v_map_top.Y;
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		gotoxy(x,y);
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gw_generate][gh_generate] = ' ';
			printf("%c", s_current_map.V_Map_Array[gw_generate][gh_generate]);
		}
		Sleep(10);
		++y;
	}
	gotoxy(0, 0);

}



void F_Map_Print()
{
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			printf("%c", s_current_map.V_Map_Array[gw_generate][gh_generate]);
		}
	}
}

void F_Map_Set_And_Print(int index)
{
	int x = v_map_top.X, y = v_map_top.Y;

	s_map_index.v_selected = index;

	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		gotoxy(x, y);
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gw_generate][gh_generate] = s_map_db[s_map_index.v_selected].V_Map_Array[gw_generate][gh_generate];
			printf("%c", s_current_map.V_Map_Array[gw_generate][gh_generate]);
			
		}
		++y;
	}
}

void F_Map_Instruction_Printout()
{
	gotoxy(d_game_width / 2, 2);
	printf("Welcome to GGPEN");
}