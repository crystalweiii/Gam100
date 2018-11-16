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
void F_Basic_Instruction_Printout();