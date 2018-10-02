#include "Graphic.h"



void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void printNote()
{
	gotoxy(d_game_width , d_game_height / 2 + 10);

	printf("Press R to reset");
}

void drawBorder()
{
	int i, j;
	gotoxy(d_game_width/4 + 5, 2);
	printf("Set Your Game Logic in following Area.");

	//Top border line...
	gotoxy(5, 5);
	for (j = 0; j < d_game_width+10; j++)
		printf("%c", 223);

	//Bottom border line... 
	gotoxy(5, 5+d_game_height+5);
	for (j = 0; j <= d_game_width+10; j++)
		printf("%c", 223);

	//Left and Right border line...
	for (j = 0; j < d_game_height+5; j++)
	{
		gotoxy(5, 5 + j);
		printf("%c", 219);

		gotoxy(5+d_game_width+ 10, 5 + j);
		printf("%c", 219);
	}
	printf("\n");

	printNote();

}

void graphicInit()
{
	drawBorder();

	F_ReadFromTextAndStore(txt_DGPLogo);
	F_ReadFromTextAndStore(txt_Map1);

	s_map_index.v_amount = d_map_amount;
	s_map_index.v_current = 0;
	s_map_index.v_selected = 0;

	SMALL_RECT windowSize = { 0 , 0 ,  d_game_width*3, d_game_height*3 }; //change the values
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);


	/*F_Map_Set_And_Print(s_map_index.v_current);*/
}

void F_Map_Set(int index) /*set index to the current map*/
{
	s_map_index.v_selected = index;
	s_map_index.v_current = index;
}


int F_ReadFromTextAndStore(char* url) {
	errno_t err;
	FILE *fp;
	char str[d_maxchar];
	char* filename = url;

	int t_widthCount = 0, t_heightCount = 0;

	err = fopen_s(&fp, filename, "r");
	if (err != NULL) {
		printf("Could not open file %s", filename);
		return 1;
	}
	while (fgets(str, d_maxchar, fp) != NULL)
	{
		/*printf("%s", str);*/
		int t_gw = 0;
		for (t_gw = 0; t_gw < d_game_width; t_gw++)
		{
			s_current_map.V_Map_Array[t_gw][t_heightCount] = str[t_gw];
			s_map_db[s_map_index.v_selected].V_Map_Array[t_gw][t_heightCount] = s_current_map.V_Map_Array[t_gw][t_heightCount];

			/*printf("%c", s_current_map.V_Map_Array[t_gw][t_heightCount]);*/
		}
		/*printf("\n");*/
		/*printf("%d,%d\n",t_gw, t_heightCount);*/
		t_heightCount++;
	}
	/*s_map_db[s_map_index.v_selected].V_Map_Array = s_current_map.V_Map_Array;*/

	++s_map_index.v_selected;
	fclose(fp);

	return 0;
}

void F_Map_Empty() /*clear screen*/
{
	int x = 7, y = 7;
	for (int gh_generate = 0; gh_generate < d_game_height; gh_generate++)
	{
		gotoxy(x, y);
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
	int x=7, y=7;
	
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

