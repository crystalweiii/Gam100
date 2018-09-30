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


void F_GameMain()
{
	F_ReadFromText(txt_DGPLogo);

	F_Map_Generate();

	/*Game Logic*/
	if (v_gamestate == Running)
	{
		F_Map_Printing();

		while (v_gamestate == Running)
		{
			if(f_input() == 'W')
				v_gamestate = Pause;
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