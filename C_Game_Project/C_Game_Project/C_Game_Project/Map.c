#include "Map.h"

COORD v_top = { 3,4 };
COORD v_btm = { d_game_width , d_game_height };
COORD v_buffer = { 4, 2 };

COORD v_map_top = { 3 + 2, 4 + 1 };

void F_Map_Init()
{
	F_Map_DrawBorder(v_top, v_btm, v_buffer);

	F_ReadFromTextAndStore(txt_DGPLogo , s_map_db[0].V_Map_Array);
	F_ReadFromTextAndStore(txt_Map1, s_map_db[1].V_Map_Array);

	s_map_index.v_amount = d_map_amount;
	s_map_index.v_current = 0;
	s_map_index.v_selected = 0;
	
	F_Map_Set_And_Print(s_map_index.v_selected);

	F_PrintNote();
	
	/*F_Map_Set_And_Print(s_map_index.v_current);*/
}

void F_Map_DrawBorder(COORD top, COORD btm, COORD buffer)
{
	int i, j;
	gotoxy( (top.X+btm.X+buffer.X) / 3 , 2);
	printf("Set Your Game Logic in following Area.");

	//Top border line...
	gotoxy(top.X, top.Y);
	for (j = 0; j < btm.X + buffer.X; j++)
		printf("%c", 223);
	
	//Bottom border line... 
	gotoxy(top.X, top.Y + btm.Y + buffer.Y);
	for (j = 0; j < btm.X + buffer.X; j++)
		printf("%c", 223);

	//Left and Right border line...
	for (j = 0; j < btm.Y + buffer.Y; j++)
	{
		gotoxy(top.X, top.Y + j);
		printf("%c", 219);

		gotoxy(top.X + btm.X + buffer.X, top.Y + j);
		printf("%c", 219);
	}
	printf("\n");
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
		gotoxy(v_map_top.X, v_map_top.Y);
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gw_generate][gh_generate] = ' ';
			printf("%c", s_current_map.V_Map_Array[gw_generate][gh_generate]);
		}
		++y;
	}
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

void F_PrintNote()
{
	gotoxy(v_top.X+v_btm.X+v_buffer.X*3 , (v_top.Y+v_btm.Y+v_buffer.X*3) / 3);

	printf("Press R to reset");
}