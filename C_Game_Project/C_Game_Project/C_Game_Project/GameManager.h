/*********************************************************************************************************************
Filename :	GameManager.h / GameManager.c
Author(s): Ngian Teck Wei , Ong Jia Quan Joel
Login(s) : teckwei.ngian(90%) , o.jiaquanjoel(10%)

Description/Features:
This is game state manager is to control and handle the flow of the whole program
**********************************************************************************************************************/


#include "Header.h"

void F_GSManager_Init();

/*For other class uses*/
void F_GSManager_ChangeState(int state);

/*Getting all the variable need up*/
void F_GSManager_InitState(int state);
void F_GSManager_UpdateState(int state, float dt);
void F_GSManager_ExitState(int state);
int F_GSManager_CheckForChangeState();

int F_GSManager_RunningStateMachine();

void F_GSManager_InputCheck();
