#include "UiHandler.h"


/*Assigning position according downwards*/
void F_Pos_Assignment(COORD start_spot , int *UI_Count)
{
	gotoxy(start_spot.X, start_spot.Y + *UI_Count);
	(*UI_Count)++;
}


/*Debug and instructional printout is heree*/
void F_Basic_Instruction_Printout()
{
	/* Retrieve: Position X right next to game map */
	COORD v_instr_borderStart = { d_game_width, 0 };										//{ v_border_btm.X , v_border_top.Y };

	/* Retrieve: Total height: game map height + ui height*/
	COORD v_instr_borderEnd = { d_instruction_width , (d_game_height + d_ui_height) / 3 };		//{ 40 , v_border_btm.Y + 10 };
	F_Map_DrawBorder(v_instr_borderStart, v_instr_borderEnd);

	COORD v_instr_startSpot = { v_instr_borderStart.X + 5 ,  v_instr_borderStart.Y + v_instr_borderEnd.Y /4 };
	int BI_Count = 0;
	
	/*Any print out you want to put just follow this format
		F_Pos_Assignment(v_temp_startSpot, &BI_Count);
		printf("Key to use:");
	It will automatically place in the right spot
	*/
	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("Key to use:");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("'Q' to quit");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("'R' to reset");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("Space to select/shoot");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("Arrow Keys for direction");


	/*CONT WITH GAMEUI*/
	/* Retrieve: Position X right next to game map */
	COORD v_gamUI_borderStart = { d_game_width,  (d_game_height + d_ui_height)/3 };										
	/* Retrieve: Total height: game map height + ui height*/
	/*COORD v_temp_borderEnd = { d_instruction_width , (d_game_height + d_ui_height) / 3 };	*/	
	F_Map_DrawBorder(v_gamUI_borderStart, v_instr_borderEnd);

	COORD v_gamUI_startSpot = { v_gamUI_borderStart.X + 5 , v_gamUI_borderStart.Y + v_instr_borderEnd.Y / 4 };
	BI_Count = 0;

	/*Any print out you want to put just follow this format
		F_Pos_Assignment(v_temp_startSpot, &BI_Count);
		printf("Key to use:");
	It will automatically place in the right spot
	*/
	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	printf("Game Info:");

	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	printf("Score:");

	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	printf("Level:");

}