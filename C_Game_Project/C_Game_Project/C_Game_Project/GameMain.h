#pragma once
#include "Header.h"
#include "GameManager.h"

/*struct*/ 



void F_GameMain()
{
	F_Graphic_Init();
	F_Map_Init();
	F_GSManager_Init();
	/*F_Map_Generate();*/
	/*Input taking*/
	F_GSManager_RunningState();
}