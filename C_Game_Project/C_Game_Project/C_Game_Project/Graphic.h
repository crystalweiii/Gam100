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

void graphicInit()
{
	F_ReadFromText(txt_DGPLogo);

	s_map_index.v_amount = d_map_amount;
	s_map_index.v_current = 0;
	s_map_index.v_selected = 0;
}

void F_Map_Set(int index) /*set index to the current map*/
{
	s_map_index.v_selected = index;
	s_map_index.v_current = index;
}


int F_ReadFromText(char* url) {
	errno_t err;
	FILE *fp;
	char str[d_maxchar];
	char* filename = url;

	int t_widthCount = 0 , t_heightCount = 0; 

	err = fopen_s(&fp, filename, "r");
	if (err != NULL) {
		printf("Could not open file %s", filename);
		return 1;
	}
	while (fgets(str, d_maxchar, fp) != NULL)
	{
		/*printf("%s", str);*/
		for (int t_gw = 0; t_gw < d_game_width; t_gw++)
		{
			s_current_map.V_Map_Array[t_gw][t_heightCount] = str[t_gw];
			s_map_db[s_map_index.v_selected].V_Map_Array[t_gw][t_heightCount] = s_current_map.V_Map_Array[t_gw][t_heightCount];

			/*printf("%c(%d,%d)", V_Map_Array[t_gw][t_heightCount], t_gw , t_heightCount);*/
		}
		t_heightCount++;
	}
	/*s_map_db[s_map_index.v_selected].V_Map_Array = s_current_map.V_Map_Array;*/

	++s_map_index.v_selected;
	fclose(fp);

	return 0;
}

void F_Map_Empty() /*clear screen*/
{
	
	for (int gh_generate = 0; gh_generate < d_game_height;  gh_generate++)
	{
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gw_generate][gh_generate] = ' ';
		}
	}
	
	system("cls");
}

void F_Map_Print()
{
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			printf("%c" , s_current_map.V_Map_Array[gw_generate][gh_generate]);
		}
	}
}

void F_Map_Set_And_Print() 
{
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		for (int gw_generate = 0; gw_generate < d_game_width; gw_generate++)
		{
			s_current_map.V_Map_Array[gw_generate][gh_generate] = s_map_db[s_map_index.v_selected].V_Map_Array[gw_generate][gh_generate];
			printf("%c", s_map_db[s_map_index.v_selected].V_Map_Array[gw_generate][gh_generate]);
		}
	}

}


