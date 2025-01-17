#include "UiHandler.h"
#include "Math.h"
#include "Graphic.h"
#include "GameObjectManager.h"
#include "BulletManager.h"			// "GetBulletInventoryArray()"
#include "WindowsHelper.h"			// "WindowsHelper_Print_ChangeColor_And_Reset()"
#include "PlayerManager.h"			// "GetPlayerLife();
#include "LevelManager.h"
#include "EnemyManager.h"

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
	v_instr_borderEnd.Y = (SHORT)((d_game_height + d_ui_height) / 2.4f);
	F_Graphic_DrawBorder(v_instr_borderStart, v_instr_borderEnd);

	v_instr_startSpot.X = v_instr_borderStart.X + 5;
	v_instr_startSpot.Y = v_instr_borderStart.Y + v_instr_borderEnd.Y / 4 ;

	/*Middle Right*/
	/* Retrieve: Position X right next to game map */
	v_gamUI_borderStart.X = d_game_width;
	v_gamUI_borderStart.Y = (SHORT)((d_game_height + d_ui_height) / 2.4f);

	/* Retrieve: Total height: game map height + ui height*/
	v_gamUI_borderEnd.X = d_instruction_width;
	v_gamUI_borderEnd.Y = (SHORT)((d_game_height + d_ui_height) / 2.4f);
	F_Graphic_DrawBorder(v_gamUI_borderStart, v_gamUI_borderEnd);

	v_gamUI_startSpot.X = v_gamUI_borderStart.X + 5;
	v_gamUI_startSpot.Y = v_gamUI_borderStart.Y + v_gamUI_borderEnd.Y / 4 ;
	
	v_btmL_borderStart.X = 0;
	v_btmL_borderStart.Y = d_game_height;
	
	v_btmL_borderEnd.X = d_game_width + d_instruction_width;
	v_btmL_borderEnd.Y = d_ui_height;				
	/* "Draw: Border to seperate gameplay & UI */
	F_Graphic_DrawBorder(v_btmL_borderStart, v_btmL_borderEnd);

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
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BKG_BLUE, "Info Key:");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "'Q' to quit");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "'R' to reset");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "'Space' to Enter");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "<^> for direction");

}

void F_UI_Game_Instru(){

	int BI_Count = 0;

	/*Any print out you want to put just follow this format
		F_Pos_Assignment(v_temp_startSpot, &BI_Count);
		printf("Key to use:");
	It will automatically place in the right spot
	*/
	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BKG_GREEN, "Game Key:");


	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "'Q' to quit");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "'R' to reset");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "'Z' to horizontal shooting");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "'X' to Vertical shooting ");

	F_Pos_Assignment(v_instr_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "<^>  for direction");

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
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BKG_BLUE, "Game Info: ");

	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "Score: ");
	printf("%d", score);

	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "Level: ");
	printf("%d", F_LevelManager_GetCurrentLevel()+1);

	F_Pos_Assignment(v_gamUI_startSpot, &BI_Count);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_BLUE, BKG_GREY, "Enemy Left to win: ");
	if(GetEnemiesToKill() < 10)
		printf("0%d", GetEnemiesToKill());
	else
		printf("%d", GetEnemiesToKill());
}


void F_UI_Game_Info_Below()
{
	int i = 0;
	gotoxy(v_btmL_startSpot.X, v_btmL_startSpot.Y );
	printf("Lifes:");

	int UI_LIFE_OFFSET = 10;
	// Erase first
	for (i = 0; i < d_PLAYER_LIFE; ++i)
	{
		gotoxy(v_btmL_startSpot.X + i * UI_LIFE_OFFSET, v_btmL_startSpot.Y + 1);
		WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BG_BLACK, "       ");
		gotoxy(v_btmL_startSpot.X + i * UI_LIFE_OFFSET, v_btmL_startSpot.Y + 2);
		WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BG_BLACK, "       ");
		gotoxy(v_btmL_startSpot.X + i * UI_LIFE_OFFSET, v_btmL_startSpot.Y + 3);
		WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BG_BLACK, "       ");
	}

	// Draw again
	for (i = 0; i < F_PlayerManager_GetPlayerLife(); ++i)
	{
		gotoxy(v_btmL_startSpot.X + i * UI_LIFE_OFFSET, v_btmL_startSpot.Y + 1);
		WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BG_BLACK, "  _+_  ");
		gotoxy(v_btmL_startSpot.X + i * UI_LIFE_OFFSET, v_btmL_startSpot.Y + 2);
		WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BG_BLACK, " (^_^)");
		gotoxy(v_btmL_startSpot.X + i * UI_LIFE_OFFSET, v_btmL_startSpot.Y + 3);
		WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BG_BLACK, "<(___)>");
	}


	gotoxy(v_btmL_startSpot.X + 35, v_btmL_startSpot.Y);
	printf("Bullets:");

	int BULLET_UI_GAP_OFFSET = 10;
	int *bulletInventory = F_BulletManager_GetBulletInventoryArray();
	for (i = 0; i < d_BULLET_INVENTORY; ++i)
	{
		if (bulletInventory[i] == BulletRed)
		{
			gotoxy(v_btmL_startSpot.X + 35 + i * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 1);
			WindowsHelper_Print_ChangeColor_And_Reset(FG_WHITE, BG_RED, ">>>>>");
			gotoxy(v_btmL_startSpot.X + 35 + i * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 2);
			WindowsHelper_Print_ChangeColor_And_Reset(FG_WHITE, BG_RED, ">>>>>");
			gotoxy(v_btmL_startSpot.X + 35 + i * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 3);
			WindowsHelper_Print_ChangeColor_And_Reset(FG_WHITE, BG_RED, ">>>>>");
		}
		else if (bulletInventory[i] == BulletGreen)
		{
			gotoxy(v_btmL_startSpot.X + 35 + i * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 1);
			WindowsHelper_Print_ChangeColor_And_Reset(FG_WHITE, BG_GREEN, ">>>>>");
			gotoxy(v_btmL_startSpot.X + 35 + i * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 2);
			WindowsHelper_Print_ChangeColor_And_Reset(FG_WHITE, BG_GREEN, ">>>>>");
			gotoxy(v_btmL_startSpot.X + 35 + i * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 3);
			WindowsHelper_Print_ChangeColor_And_Reset(FG_WHITE, BG_GREEN, ">>>>>");
		}
		else if (bulletInventory[i] == BulletBlue)
		{
			gotoxy(v_btmL_startSpot.X + 35 + i * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 1);
			WindowsHelper_Print_ChangeColor_And_Reset(FG_WHITE, BG_BLUE, ">>>>>");
			gotoxy(v_btmL_startSpot.X + 35 + i * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 2);
			WindowsHelper_Print_ChangeColor_And_Reset(FG_WHITE, BG_BLUE, ">>>>>");
			gotoxy(v_btmL_startSpot.X + 35 + i * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 3);
			WindowsHelper_Print_ChangeColor_And_Reset(FG_WHITE, BG_BLUE, ">>>>>");
		}
	}

	// UI Arrow: Indicate which one is the next bullet
	gotoxy(v_btmL_startSpot.X + 35, v_btmL_startSpot.Y + 4);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_YELLOW, BG_BLACK, "\\[^]/");

	// UI Enemy
	gotoxy(v_btmL_startSpot.X + 100, v_btmL_startSpot.Y);
	printf("Enemy Type:");
	gotoxy(v_btmL_startSpot.X + 100 + 0 * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 1);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BG_RED, "XXXXX");
	gotoxy(v_btmL_startSpot.X + 100 + 0 * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 2);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BG_RED, "XXXXX");
	gotoxy(v_btmL_startSpot.X + 100 + 0 * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 3);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTRED, BG_RED, "XXXXX");

	gotoxy(v_btmL_startSpot.X + 100 + 1 * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 1);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTGREEN, BG_GREEN, "XXXXX");
	gotoxy(v_btmL_startSpot.X + 100 + 1 * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 2);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTGREEN, BG_GREEN, "XXXXX");
	gotoxy(v_btmL_startSpot.X + 100 + 1 * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 3);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTGREEN, BG_GREEN, "XXXXX");

	gotoxy(v_btmL_startSpot.X + 100 + 2 * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 1);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTBLUE, BG_BLUE, "XXXXX");
	gotoxy(v_btmL_startSpot.X + 100 + 2 * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 2);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTBLUE, BG_BLUE, "XXXXX");
	gotoxy(v_btmL_startSpot.X + 100 + 2 * BULLET_UI_GAP_OFFSET, v_btmL_startSpot.Y + 3);
	WindowsHelper_Print_ChangeColor_And_Reset(FG_LIGHTBLUE, BG_BLUE, "XXXXX");
}

void F_UI_Game_Continue_Instru()
{
	v_instr_borderStart.X = (SHORT)(d_game_width / 3.2f);
	v_instr_borderStart.Y = (SHORT)(d_game_height / 2.7f);

	v_instr_borderEnd.X = 50;
	v_instr_borderEnd.Y = 10;
	
	F_Graphic_DrawBorder_With_Text(v_instr_borderStart, v_instr_borderEnd, " ");
	F_Graphic_DrawBorder(v_instr_borderStart, v_instr_borderEnd);

	gotoxy((int)(d_game_width / 2.3f), (int)(d_game_height / 2.5f));
	printf("%s", "*******************");
	gotoxy((int)(d_game_width / 2.3f), (int)(d_game_height / 2.3));
	printf("%s", "*     YOU WIN     *");
	gotoxy((int)(d_game_width / 2.3f), (int)(d_game_height / 2.2f));
	printf("%s", "*******************");
	gotoxy((int)(d_game_width / 2.8f), (int)(d_game_height / 1.8f));
	printf("%s", "press space to continue to next level...");
}