/*********************************************************************************************************************
Filename :	GameManager.h / GameManager.c
Author(s): Ngian Teck Wei , Ong Jia Quan Joel 
Login(s) : teckwei.ngian(90%) , o.jiaquanjoel(10%)

Description/Features:
This is game state manager is to control and handle the flow of the whole program
**********************************************************************************************************************/

#include <time.h>
#include "GameManager.h"
#include "Input.h"
#include "Map.h"

/*Game State*/
#include "GS_StartUp.h"
#include "GS_MainMenu.h"
#include "GS_GamePlay.h"


int v_gs_current;
int v_gs_previous;
int v_gs_next;

int currentScreenIndex = 0;

int  v_running = 1;

int temp_c_input = 0;

COORD CO_TextPrintOut = { 0 };
/*Each key check will be stored here*/

/* DT DONE HERE */
clock_t ticksThen, ticksNow;
float dt;

void F_GSManager_Init()
{
	COORD TextColumn = { v_border_btm.X + 5, (v_border_btm.Y) / 3 };
	CO_TextPrintOut = TextColumn;

	v_gs_current = StartUp;
	v_gs_previous = StartUp;
	v_gs_next = StartUp;
	
	currentScreenIndex = 0;
	v_running = 1;
	temp_c_input = 0;

	F_GSManager_InitState(v_gs_current);
}

/*use for other files to change state / may need checks*/
void F_GSManager_ChangeState(int state)
{
	v_gs_next = state;
}

/*Initialising of states is done here*/
void F_GSManager_InitState(int state)
{
	switch (state)
	{
	case StartUp:
		GS_StartUp_Init();
		break;
	case MainMenu:
		GS_MainMenu_Init();
		break;
	case GamePlay:
		GS_GamePlay_Init();
		break;
	case Pause:
		F_GSManager_ChangeState(End);
		break;
	case End:
		v_running = 0;
		break;
	}
}

/*Updating of states is done here*/
void F_GSManager_UpdateState(int state, float dt) {
	
	switch (state)
		{
		case StartUp:
			GS_StartUp_Update();
			break;
		case MainMenu:
			GS_MainMenu_Update();
			break;
		case GamePlay:
			GS_GamePlay_Update(dt);
			break;
		case Pause:
			v_running = 0;
			break;
		case End:
			v_running = 0;
			break;
		}
}

/*Exit and cleaning of states is done here*/
void F_GSManager_ExitState(int state) {
	switch (state)
	{
	case StartUp:
		GS_StartUp_Exit();
		break;
	case MainMenu:
		GS_MainMenu_Exit();
		break;
	case GamePlay:
		GS_GamePlay_Exit();
		break;
	case Pause:
		v_running = 0;
		break;
	case End:
		v_running = 0;
		break;
	}
}

int F_GSManager_RunningStateMachine()
{
	ticksThen = clock();
	while (v_running)
	{	
		/*Check for valid gamestate*/
		if (F_GSManager_CheckForChangeState())
		{
			v_gs_previous = v_gs_current;
			F_GSManager_ExitState(v_gs_current);
			v_gs_current = v_gs_next;
			F_GSManager_InitState(v_gs_current);
		}
		/*Input check and updates here*/
		F_GSManager_InputCheck();

		/* DT UPDATE DONE HERE */
		ticksNow = clock();
		dt = (ticksNow - ticksThen) / (float)CLOCKS_PER_SEC;
		if (dt >= 0.016f)
		{
			/* Update the game state manager */
			ticksThen = ticksNow;
			F_GSManager_UpdateState(v_gs_current, dt);
			f_KeyUpdate(dt);
			/*
			gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 5);
			printf("dt: %f", dt);
			*/
		}
	}
	return 0;
}

/*input checking done here*/
void F_GSManager_InputCheck()
{
	/*
	/*Check for number 1 key hit/
	if (f_Check_KeyDown(0x31))
	{
		if (currentScreenIndex < d_map_amount - 1)
			currentScreenIndex++;
		else
			currentScreenIndex = 0;

		v_gs_next = currentScreenIndex;
	}

	/*Check for number 2 key hit/
	if (f_Check_KeyDown(0x32))
	{
		if (currentScreenIndex > 0)
			currentScreenIndex--;
		else
			currentScreenIndex = d_map_amount - 1;

		v_gs_next = currentScreenIndex;
	}
	*/
	/*Check for Q small and Q caps*/
	if (f_Check_KeyDown(0x71) || f_Check_KeyDown(0x51))
	{
		v_gs_next = Pause;
	}


	/*Check for R small and R caps*/
	if (f_Check_KeyDown(0x72) || f_Check_KeyDown(0x52))
	{
		v_gs_next = currentScreenIndex;
	}

}
/*check for changing of state done here*/
int F_GSManager_CheckForChangeState()
{
	return v_gs_next != v_gs_current;

}

/*Debug and instructional printout is heree*/
void F_Basic_Instruction_Printout()
{
    COORD v_temp_startSpot = { v_border_btm.X + 5 , (v_border_btm.Y) / 3 };
	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y);
	printf("'Q' to quit");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 1);
	printf("'R' to reset");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 2);
	printf("Space to select");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 3);
	printf("'W' & 'S' For up and down");

	COORD v_temp_borderStart = { v_border_btm.X , v_border_top.Y };
	COORD v_temp_borderEnd = { 40 , v_border_btm.Y + 10 };
	F_Map_DrawBorder(v_temp_borderStart, v_temp_borderEnd);

}