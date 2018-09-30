#include "Header.h"

char V_Map_Array[d_game_height][d_game_width];


void F_Map_Generate()
{
	for  (int gw_generate = 0; gw_generate < d_game_width ;  gw_generate++)
	{
		for (int gh_generate = 0; gh_generate < d_game_height;  gh_generate++)
		{
			V_Map_Array[gh_generate][gw_generate] = 'X';
		}
	}
}

void F_Map_Printing()
{
	for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
	{
		for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
		{
			printf("%c" , V_Map_Array[gh_generate][gw_generate]);
		}
		printf("\n");
	}
}



