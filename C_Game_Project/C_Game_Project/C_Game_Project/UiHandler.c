#include "UiHandler.h"

COORD v_instr_startSpot;
COORD v_gamUI_startSpot;

/*Assigning position according downwards*/
void F_Pos_Assignment(COORD start_spot , int *UI_Count)
{
	gotoxy(start_spot.X, start_spot.Y + *UI_Count);
	(*UI_Count)++;
}

void F_UI_Init()
{
	F_UI_Border_PO();
	F_UI_Print_Out_Index(PT_Basic_Instruction);
}
/*Debug and instructional printout is heree*/
void F_UI_Print_Out()
{
	int count;
	for (count = 0; count < PrintTrack_Total; count++)
	{
		F_UI_Print_Out_Index(count);
	}
}

void F_UI_Print_Out_Index(int index) {
	switch (index)
	{
	case PT_Basic_Instruction:
		F_UI_Basic_Instru();
		break;
	case PT_Game_Instruction:
		F_UI_Game_Instru();
		break;
	case PT_Game_Info_Right:
		F_UI_Game_Info_Right();
		break;
	case PT_Game_Info_Below:
		F_UI_Game_Info_Below();
		break;
	}
}

void F_UI_Border_PO()
{
	/*Top Right*/
	/* Retrieve: Position X right next to game map */
	COORD v_instr_borderStart = { d_game_width, 0 };										//{ v_border_btm.X , v_border_top.Y };

	/* Retrieve: Total height: game map height + ui height*/
	COORD v_instr_borderEnd = { d_instruction_width , (d_game_height + d_ui_height) / 3 };		//{ 40 , v_border_btm.Y + 10 };
	F_Map_DrawBorder(v_instr_borderStart, v_instr_borderEnd);

	v_instr_startSpot.X = v_instr_borderStart.X + 5;
	v_instr_startSpot.Y = v_instr_borderStart.Y + v_instr_borderEnd.Y / 4 ;

	/*Middle Right*/
	/* Retrieve: Position X right next to game map */
	COORD v_gamUI_borderStart = { d_game_width,  (d_game_height + d_ui_height) / 3 };
	/* Retrieve: Total height: game map height + ui height*/
	COORD v_gamUI_borderEnd = { d_instruction_width , (d_game_height + d_ui_height) / 3 };
	F_Map_DrawBorder(v_gamUI_borderStart, v_gamUI_borderEnd);

	v_gamUI_startSpot.X = v_gamUI_borderStart.X + 5;
	v_gamUI_startSpot.Y = v_gamUI_borderStart.Y + v_gamUI_borderEnd.Y / 4 ;

}


void F_UI_Basic_Instru() {

	int BI_Count = 0;

	/*Any print out you want to put just follow this format
		F_Pos_Assignment(v_temp_startSpot, &BI_Count);
		printf("Key to use:");
	It will automatically place in the right spot
	*/
	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("Info Key:");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("'Q' to quit");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("'R' to reset");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("Space to shoot");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("Arrow Keys for direction");

}

void F_UI_Game_Instru(){

	int BI_Count = 0;

	/*Any print out you want to put just follow this format
		F_Pos_Assignment(v_temp_startSpot, &BI_Count);
		printf("Key to use:");
	It will automatically place in the right spot
	*/
	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("Game Key:");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("'Q' to quit");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("'R' to reset");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("Space to shoot");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("Arrow Keys for direction");

}

void F_UI_Game_Info_Right()
{
	/*CONT WITH GAMEUI*/

	int BI_Count = 0;

	/*Any print out you want to put just follow this format
		F_Pos_Assignment(v_temp_startSpot, &BI_Count);
		printf("Key to use:");
	It will automatically place in the right spot
	*/
	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	printf("Game Info:");

	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	printf("Score:" );

	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	printf("Level:");
}


void F_UI_Game_Info_Below()
{


}