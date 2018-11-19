#include "UiHandler.h"
#include "Math.h"
#include "Graphic.h"

COORD v_instr_startSpot;
COORD v_gamUI_startSpot;
COORD v_btmL_startSpot;

COORD v_instr_borderStart;
COORD v_instr_borderEnd;

COORD v_gamUI_borderStart;
COORD v_gamUI_borderEnd;

COORD v_btmR_borderStart;
COORD v_btmR_borderEnd;

COORD v_btmL_borderStart;
COORD v_btmL_borderEnd;			


/*Assigning position according downwards*/
void F_Pos_Assignment(COORD start_spot , int *UI_Count)
{
	gotoxy(start_spot.X, start_spot.Y + *UI_Count);
	(*UI_Count)++;
}

void F_UI_Init()
{
	F_UI_Border_PO();
	/*F_UI_Print_Out_Index(PT_Basic_Instruction);*/
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

void F_UI_Clear_Index(int index) {
	switch (index)
	{
	case PT_Basic_Instruction:
		F_Graphic_DrawSquare_Asc(Math_Get_Border(v_instr_borderStart,1), Math_Get_Border(v_instr_borderEnd, -2), ' ' );
		break;
	case PT_Game_Instruction:
		F_Graphic_DrawSquare_Asc(Math_Get_Border(v_instr_borderStart, 1), Math_Get_Border(v_instr_borderEnd, -2), ' ');
		break;
	case PT_Game_Info_Right:
		F_Graphic_DrawSquare_Asc(Math_Get_Border(v_gamUI_borderStart, 1), Math_Get_Border(v_gamUI_borderEnd, -2), ' ');
		break;
	case PT_Game_Info_Below:
		F_Graphic_DrawSquare_Asc(Math_Get_Border(v_btmR_borderStart, 1), Math_Get_Border(v_btmR_borderEnd, -2), ' ');
		break;
	}
}


void F_UI_Border_PO()
{
	/*Top Right*/
	/* Retrieve: Position X right next to game map */
	v_instr_borderStart.X = d_game_width;
	v_instr_borderStart.Y = 0;									

	/* Retrieve: Total height: game map height + ui height*/
	v_instr_borderEnd.X = d_instruction_width;
	v_instr_borderEnd.Y = (d_game_height + d_ui_height) / 2.4;
	F_Map_DrawBorder(v_instr_borderStart, v_instr_borderEnd);

	v_instr_startSpot.X = v_instr_borderStart.X + 5;
	v_instr_startSpot.Y = v_instr_borderStart.Y + v_instr_borderEnd.Y / 4 ;

	/*Middle Right*/
	/* Retrieve: Position X right next to game map */
	v_gamUI_borderStart.X = d_game_width;
	v_gamUI_borderStart.Y = (d_game_height + d_ui_height) / 2.4;

	/* Retrieve: Total height: game map height + ui height*/
	v_gamUI_borderEnd.X = d_instruction_width;
	v_gamUI_borderEnd.Y = (d_game_height + d_ui_height) / 2.4;
	F_Map_DrawBorder(v_gamUI_borderStart, v_gamUI_borderEnd);

	v_gamUI_startSpot.X = v_gamUI_borderStart.X + 5;
	v_gamUI_startSpot.Y = v_gamUI_borderStart.Y + v_gamUI_borderEnd.Y / 4 ;
	
	/*Btm right*/
	/*
	v_btmR_borderStart.X = d_game_width;
	v_btmR_borderStart.Y = (d_game_height + d_ui_height) * 2 / 3;

	v_btmR_borderEnd.X = d_instruction_width;
	v_btmR_borderEnd.Y = (d_game_height + d_ui_height) / 3 ;
	F_Map_DrawBorder(v_btmR_borderStart, v_btmR_borderEnd);
	*/
	/*
	v_btmR_startSpot.X = v_btmR_borderStart.X + 5;
	v_btmR_startSpot.Y = v_btmR_borderStart.Y + v_btmR_borderEnd.Y / 4;
 */
	v_btmL_borderStart.X = 0;
	v_btmL_borderStart.Y = d_game_height;
	
	v_btmL_borderEnd.X = d_game_width + d_instruction_width;
	v_btmL_borderEnd.Y = d_ui_height;				
	/* "Draw: Border to seperate gameplay & UI */
	F_Map_DrawBorder(v_btmL_borderStart, v_btmL_borderEnd);

	v_btmL_startSpot.X = v_btmL_borderStart.X + 2;
	v_btmL_startSpot.Y = v_btmL_borderStart.Y + (v_btmL_borderEnd.Y / 4);
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
	printf("Space to Enter");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	printf("<^> for direction");

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
	printf("Score:OVER 9000" );

	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	printf("Level:OVER 3.14159");
}


void F_UI_Game_Info_Below()
{
	gotoxy(v_btmL_startSpot.X, v_btmL_startSpot.Y );
	printf("Lifes:");
	gotoxy(v_btmL_startSpot.X, v_btmL_startSpot.Y+1);
	printf("$$$");

	gotoxy(v_btmL_startSpot.X + 20, v_btmL_startSpot.Y);
	printf("Bullets:");
	gotoxy(v_btmL_startSpot.X + 20, v_btmL_startSpot.Y+1);
	printf("RBGBGB");

	gotoxy(v_btmL_startSpot.X + 80, v_btmL_startSpot.Y);
	printf("Something:");

}
