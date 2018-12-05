/*********************************************************************************************************************
Filename :	GS_GamePlay.h / GS_GamePlay.c
Author(s): Ngian Teck Wei
Login(s) : teckwei.ngian(100%)

Description/Features:
This is for the gameplay state, where others will then link up with their gameplay logics
**********************************************************************************************************************/

extern void GS_GamePlay_Init();

extern void GS_GamePlay_Update(float dt);

extern void GS_GamePlay_Exit();

/* Game paused or running toggle */
int GS_GetGamePaused();
void GS_SetGamePaused(int value);
