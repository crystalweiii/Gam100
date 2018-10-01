#pragma once
#include "Header.h"
#include "Input.h"
#include "TextReader.h"

/*struct*/ 
enum GameState
{
	Running = 0,
	Pause,
	End
};


int v_gamestate = Running;
int temp_c_input = 0;


void F_GameMain()
{
	graphicInit();

	/*F_Map_Generate();*/

	/*Game Logic*/
	if (v_gamestate == Running)
	{
		F_Map_Print();
		
		while (v_gamestate == Running)
		{
			temp_c_input = f_input();
			if(temp_c_input == 'W' || temp_c_input == 'w')
				v_gamestate = Pause;
			if (temp_c_input == 'C' || temp_c_input == 'c') /*clear screen*/
				F_Map_Empty();
			if (temp_c_input == 'R' || temp_c_input == 'r') /*reset screen*/
			{
				F_Map_Empty();
				F_Map_Set_And_Print();
			}
		}
	}
	if (v_gamestate == Pause)
	{
		while (v_gamestate == Pause)
		{
			printf("pause\n");
			v_gamestate = End;
		}
	}
	/*Input taking*/

}