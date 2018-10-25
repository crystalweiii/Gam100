#pragma once
#include "Header.h"
#include "Graphic.h"
#include "Menu.h"

/*Cordinate for outer border*/
COORD v_border_top;
COORD v_border_btm;

/*Space better outer border and map*/
COORD v_map_buffer;

/*Cordinate for map border top*/
COORD v_map_top;
COORD v_map_btm;

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
void F_Map_EmptySlow();

void F_Map_Print();
void F_Map_Set_And_Print(int index);



/*Drawing border with specific ascicode*/
/*void F_Map_DrawBorder(COORD top, COORD btm, int ascicode);*/

void F_Map_Instruction_Printout();