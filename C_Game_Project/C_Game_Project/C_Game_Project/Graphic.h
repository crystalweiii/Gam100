#include "Header.h"

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


void gotoxy(int x, int y);
int F_ReadFromTextAndStore(char* url);

void graphicInit();

void F_Map_Set(int index); /*set index to the current map*/
void F_Map_Empty(); /*clear screen*/
void F_Map_Print();
void F_Map_Set_And_Print(int index);

void F_Map_DrawBorder();

void printNote();
