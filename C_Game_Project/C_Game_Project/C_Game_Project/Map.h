#pragma once
#include "Header.h"
#include "Graphic.h"

COORD v_border_top;
COORD v_border_btm;

COORD v_map_buffer;
COORD v_map_top ;


struct S_MapIndex /*to keep track of the maps*/
{
	int v_current;
	int v_selected;
	int v_amount;
};

struct S_MapIndex s_map_index;

struct S_MapData /*to keep track of the maps*/
{
	char V_Map_Array[d_game_width][d_game_height];
};

/*int V_current_map_index = 0;  to keep track of the current map*/

struct S_MapData s_map_db[d_map_amount];
struct S_MapData s_current_map;
/*
char V_Map_Data_Array[d_map_amount][d_game_width][d_game_height];
char V_Map_Array[d_game_width][d_game_height];
*/

void F_Map_Init();

void F_Map_Set(int index); /*set index to the current map*/
void F_Map_Empty(); /*clear screen*/
void F_Map_Print();
void F_Map_Set_And_Print(int index);

/*Drawing border, Using top and btm coordinate only*/
void F_Map_DrawBorder(COORD btm, COORD top);


/*Drawing border with specific ascicode*/
/*void F_Map_DrawBorder(COORD top, COORD btm, int ascicode);*/

void F_Map_Instruction_Printout();