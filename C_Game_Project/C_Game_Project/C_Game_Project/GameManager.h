#pragma once
#include "Input.h"
#include "TextReader.h"
#include "Map.h"
#include "Header.h"

enum GameState
{
	Running = 0,
	Pause,
	Loading,
	End
};

int f_input();


void F_GSManager_Init();
void F_GSManager_ChangeState(int state);

int F_GSManager_RunningState();
void F_GSManager_Running();
