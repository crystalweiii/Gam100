
#include "Header.h"

void F_GSManager_Init();

/*For transition and other fancy stuff*/
void F_GSManager_ChangeState();

/*Getting all the variable need up*/
void F_GSManager_InitState();
void F_GSManager_UpdateState();
void F_GSManager_ExitState();
int F_GSManager_CheckForChangeState();

int F_GSManager_RunningStateMachine(int* dt);

void F_GSManager_InputCheck();  
void F_Basic_Instruction_Printout();                  /*Temp Debug and print out*/