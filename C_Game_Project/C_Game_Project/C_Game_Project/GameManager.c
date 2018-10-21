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
	F_GSManager_ChangeState(InitialLoad);
	F_GSManager_InitState(InitialLoad);

}

void F_GSManager_ChangeState(int state)
{
	v_previous_gs = v_current_gs;
	v_current_gs = state;
	/*Transition*/
	F_Map_EmptySlow();
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
		/*
		switch (v_current_gs)
		{
		case Running:
			F_GSManager_Running();
			break;
		case InitialLoad:
			break;
		case MainMenu:
			break;
		case MainGame:
			break;
		case Pause:
			break;
		case End:
			break;
		}
		*/
		/*
		*dt = time(NULL) / 3600;
		gotoxy(v_temp_startSpot.X, v_temp_startSpot.Y + 3);
		printf("Seconds went pass: %d", *dt);
		*/

	}

	/*
	if (v_current_gs == Running)
	{
		while (v_current_gs == Running)
		{
			F_GSManager_Running();
		}
		F_GSManager_RunningState();
		return 1;
	}
	else if (v_current_gs == Pause)
	{

		while (v_current_gs == Pause)
		{
			printf("pause\n");
			v_current_gs = End;
		}
		F_GSManager_RunningState();
		return 1;
	}
	else if (v_current_gs == End)
	{
		return 0;
	}
	return 1;
	*/
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
			/*F_Map_Set_And_Print(1);*/
			F_GSManager_ChangeState(MainGame);
			F_GSManager_InitState(MainGame);
			break;
		case 'R':
		case 'r':
			/*F_Map_Set_And_Print(0);*/
			F_GSManager_ChangeState(InitialLoad);
			F_GSManager_InitState(InitialLoad);
			break;

		case 'N':
		case 'n':
			if (currentScreenIndex < d_map_amount-1)
				currentScreenIndex++;
			else
				currentScreenIndex = 0;

			F_GSManager_ChangeState(currentScreenIndex);
			F_GSManager_InitState(currentScreenIndex);
	}

}


