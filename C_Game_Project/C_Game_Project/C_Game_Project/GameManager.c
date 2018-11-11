#include <time.h>
#include "GameManager.h"
#include "Input.h"
#include "TextReader.h"
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

void F_GSManager_ChangeState(int state)
{

}

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
	/*COORD v_temp_startSpot = { (short)v_border_btm.X + 5 , (short)(v_border_btm.Y) / 2.5 };*/

	/* DT DONE HERE */
	clock_t ticksThen, ticksNow;
	float dt;
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

			gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y - 1);

			//printf("Current Map Index: %d", currentScreenIndex);
		}
		/*Input check and updates here, Most likely gonna move input check to another*/
		F_GSManager_InputCheck();

		/* DT UPDATE DONE HERE */
		ticksNow = clock();
		dt = (ticksNow - ticksThen) / (float)CLOCKS_PER_SEC;
		if (dt >= 0.016f)
		{
			/* Update the game state manager. */
			ticksThen = ticksNow;
			F_GSManager_UpdateState(v_gs_current, dt);
		}
	}
	return 0;
}

void F_GSManager_InputCheck()
{
	/*Check for number 1 key hit*/
	if (f_Check_KeyDown(0x31))
	{
		if (currentScreenIndex < d_map_amount - 1)
			currentScreenIndex++;
		else
			currentScreenIndex = 0;

		v_gs_next = currentScreenIndex;
	}

	/*Check for number 2 key hit*/
	if (f_Check_KeyDown(0x32))
	{
		if (currentScreenIndex > 0)
			currentScreenIndex--;
		else
			currentScreenIndex = d_map_amount - 1;

		v_gs_next = currentScreenIndex;
	}

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

int F_GSManager_CheckForChangeState()
{
	return v_gs_next != v_gs_current;

}

void F_Basic_Instruction_Printout()
{
	COORD v_temp_startSpot = { v_border_btm.X + 5 , (v_border_btm.Y) / 3 };
	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y);
	printf("'Q' to quit");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 1);
	printf("'R' to reset");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 2);
	printf("'1' for next map");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 3);
	printf("'2' for previous map");
}