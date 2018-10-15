#include "GameManager.h"

GameState v_gamestate = Running;
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

}

void F_GSManager_ChangeState(int state)
{
	v_gamestate = Loading;
	/*Transition*/
	int count = 5000;
	int loadingSpot;
	while (v_gamestate == Loading)
	{
		gotoxy((v_top.X + v_btm.X + v_buffer.X) / 2 + 1, v_top.Y + v_btm.Y + v_buffer.Y + 1);
		loadingSpot = printf_s("Loading");
		
	}
	v_gamestate = state;

}

int F_GSManager_RunningState()
{
	if (v_gamestate == Running)
	{
		while (v_gamestate == Running)
		{
			F_GSManager_Running();
		}
		F_GSManager_RunningState();
		return 1;
	}
	else if (v_gamestate == Pause)
	{
		
		while (v_gamestate == Pause)
		{
			printf("pause\n");
			v_gamestate = End;
		}
		F_GSManager_RunningState();
		return 1;
	}
	else if (v_gamestate == End)
	{
		return 0;
	}
	return 1;
}

void F_GSManager_Running()
{
	temp_c_input = f_input();
	if (temp_c_input == 'P' || temp_c_input == 'p')
		F_GSManager_ChangeState(Pause);
	if (temp_c_input == 'C' || temp_c_input == 'c') /*clear screen*/
		F_Map_Empty();
	if (temp_c_input == 'T' || temp_c_input == 't') /*reset screen*/
	{
		F_Map_Set_And_Print(1);
	}
	if (temp_c_input == 'R' || temp_c_input == 'r') /*reset screen*/
	{
		F_Map_Set_And_Print(0);
	}

}


