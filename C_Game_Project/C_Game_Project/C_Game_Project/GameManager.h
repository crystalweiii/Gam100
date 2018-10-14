#pragma once
#include "Input.h"
#include "TextReader.h"
#include "Map.h"
#include "Header.h"

int f_input();

void F_GSManager_Init();
void F_GSManager_ChangeState(int state);

int F_GSManager_RunningState(int* dt);
void F_GSManager_Running();
