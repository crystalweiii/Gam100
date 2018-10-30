#include "Graphic.h"


void F_Graphic_Init()
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle(TEXT("NANIIIIIIIII"));
	
	int lx,ly;
	WindowsHelper_GetLargestConsoleWindowSize(&lx, &ly);

	COORD bufferSize = { (short)lx/1.2, (short)lx/1.2 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	
	SMALL_RECT windowSize =  { 0 , 0 ,  lx/1.2-1 , ly/1.2-1 }; 
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	
}


void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(wHnd, c);
}



int F_ReadFromTextAndStore(char* url , char dc_array[d_game_width][d_game_height]) {
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
			dc_array[t_gw][t_heightCount] = str[t_gw];
			/*s_map_db[s_map_index.v_selected].V_Map_Array[t_gw][t_heightCount] = s_current_map.V_Map_Array[t_gw][t_heightCount];*/
		}

		t_heightCount++;
	}
	fclose(fp);

	return 0;
}


/*Wrapper to the function*/
void WindowsHelper_GetLargestConsoleWindowSize(int *width, int* height)
{
	if (width == NULL || height == NULL)
	{
		return;
	}

	COORD size = GetLargestConsoleWindowSize(wHnd);
	//Dereferncing pointers to assign integer values into the integers being pointed at
	*width = size.X;
	*height = size.Y;
}

/*Setting the window to be as big as possible*/
void WindowsHelper_FullScreen()
{
	int width = 0, height = 0;
	WindowsHelper_GetLargestConsoleWindowSize(&width, &height);

	COORD bufferSize = { width, height };
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
}


void F_Map_DrawBorder(COORD top, COORD btm)
{
	int j;

	//Top border line...
	gotoxy(top.X, top.Y);
	for (j = 0; j < btm.X; j++)
		printf("%c", 223);

	//Bottom border line... 
	gotoxy(top.X, top.Y + btm.Y);
	for (j = 0; j < btm.X; j++)
		printf("%c", 223);

	//Left and Right border line...
	for (j = 0; j < btm.Y; j++)
	{
		gotoxy(top.X, top.Y + j);
		printf("%c", 219);

		gotoxy(top.X + btm.X, top.Y + j);
		printf("%c", 219);
	}
	printf("\n");
}


void F_Map_DrawBorder_Asc(COORD top, COORD btm, int ascicode)
{
	int j;
	//Top border line...
	gotoxy(top.X, top.Y);
	for (j = 0; j < btm.X; j++)
		printf("%c", ascicode);

	//Bottom border line... 
	gotoxy(top.X, top.Y + btm.Y);
	for (j = 0; j < btm.X; j++)
		printf("%c", ascicode);

	//Left and Right border line...
	for (j = 0; j < btm.Y; j++)
	{
		gotoxy(top.X, top.Y + j);
		printf("%c", ascicode);

		gotoxy(top.X + btm.X, top.Y + j);
		printf("%c", ascicode);
	}
	printf("\n");
}
