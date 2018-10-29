#pragma once
#include "Input.h"
#include "TextReader.h"
#include "Map.h"
#include "Header.h"

void F_GSManager_Init();

/*For transition and other fancy stuff*/
void F_GSManager_ChangeState(int state);

/*Getting all the variable need up*/
void F_GSManager_InitState(int state);

int F_GSManager_RunningState(int* dt);
void F_GSManager_InputCheck();


void F_Basic_Instruction_Printout();