#include "Menu.h"

void F_Main_Menu_Print(char dc_array[d_game_width][d_game_height])
{
	COORD AlignPoint = { d_game_width / 2.5f ,  d_game_height / 3 };

	char* Spaceneed[25]; /*25 max char*/
	int count;

	char play[] = "play";
	char credit[] = "credit";
	char exit[] = "exit";

	for (count = 0; count < 4; count++) {
		dc_array[AlignPoint.X + count][AlignPoint.Y] = play[count];
	}

	AlignPoint.Y += 3;

	for (count = 0; count < 6; count++) {
		dc_array[AlignPoint.X + count][AlignPoint.Y] = credit[count];
	}

	AlignPoint.Y += 3;

	for (count = 0; count < 4; count++) {
		dc_array[AlignPoint.X + count][AlignPoint.Y] = exit[count];
	}
}