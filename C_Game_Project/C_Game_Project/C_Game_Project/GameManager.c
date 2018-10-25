#include "GameManager.h"

enum GameState
{
	InitialLoad = 0,
	MainMenu,
	MainGame,
	Running,
	Pause,
	End
};


int v_current_gs = Running;
int v_previous_gs = Running;

int currentScreenIndex = 0;

int  v_running = 1;

int temp_c_input = 0;

COORD CO_TextPrintOut = { 0 };

int f_input()
{
	if (_kbhit())
	{
		int temp = _getch();
		return temp;
	}
	return 0;
}

void F_GSManager_Init()
{
	COORD TextColumn = { v_border_btm.X + 5, (v_border_btm.Y) / 3 };
	CO_TextPrintOut = TextColumn;

	F_GSManager_ChangeState(InitialLoad);
	F_GSManager_InitState(InitialLoad);

}

void F_GSManager_ChangeState(int state)
{
	v_previous_gs = v_current_gs;
	v_current_gs = state;
	/*Transition*/
	F_Map_EmptySlow();

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y - 1);
	printf("Current Map Index: %d", currentScreenIndex);
}

void F_GSManager_InitState(int state)
{
	switch (v_current_gs)
	{
	case InitialLoad:
		F_Map_Set_And_Print(0);
		break;
	case MainMenu:
		F_Map_Set_And_Print(1);
		break;
	case MainGame:
		F_Map_Set_And_Print(2);
		break;
	case Pause:
		F_GSManager_ChangeState(End);
		break;
	case End:
		v_running = 0;
		break;
	}

}


int F_GSManager_RunningState(int* dt)
{
	COORD v_temp_startSpot = { v_border_btm.X + 5 , (v_border_btm.Y) / 2.5 };

	while (v_running)
	{
		F_GSManager_InputCheck();
	}
}

void F_GSManager_InputCheck()
{
	/*Checking of input for running*/
	switch(f_input())
	{
		case 'P':
		case 'p':
			F_GSManager_ChangeState(Pause);
			F_GSManager_InitState(Pause);
			break;
		case 'C':
		case 'c':
			F_Map_Empty();
			break;
		case 'T':
		case 't':
			currentScreenIndex = MainGame;
			/*F_Map_Set_And_Print(1);*/
			F_GSManager_ChangeState(MainGame);
			F_GSManager_InitState(MainGame);
			break;
		case 'R':
		case 'r':
			/*F_Map_Set_And_Print(0);*/
			currentScreenIndex = InitialLoad;
			F_GSManager_ChangeState(InitialLoad);
			F_GSManager_InitState(InitialLoad);
			break;

		case '1':
			if (currentScreenIndex < d_map_amount-1)
				currentScreenIndex++;
			else
				currentScreenIndex = 0;

			F_GSManager_ChangeState(currentScreenIndex);
			F_GSManager_InitState(currentScreenIndex);
			break;
		case '2':
			if (currentScreenIndex > 0)
				currentScreenIndex--;
			else
				currentScreenIndex = d_map_amount-1;

			F_GSManager_ChangeState(currentScreenIndex);
			F_GSManager_InitState(currentScreenIndex);
			break;

	}

}


void F_Basic_Instruction_Printout()
{
	COORD v_temp_startSpot = { v_border_btm.X + 5 , (v_border_btm.Y) / 3 };
	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y);
	printf("'P' to quit");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 1);
	printf("'R' for first map");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 2);
	printf("'T' for second map");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 3);
	printf("'1' for next map");

	gotoxy(CO_TextPrintOut.X, CO_TextPrintOut.Y + 4);
	printf("'2' for previous map");

}