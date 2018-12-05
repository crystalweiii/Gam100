#pragma once

void F_LevelManager_Init();
void F_LevelManager_Update();
void F_LevelManager_Exit();

void F_LevelManager_ClearLevel();
void LoadLevel(int level);
void F_LevelManager_InitEnemies(int level);

int F_LevelManager_GetCurrentLevel();
void F_LevelManager_SetCurrentLevel(int level);
int F_LevelManager_CheckIfWin();
void F_LevelManager_Lost();

/* Printing the transition screen */
void PrintContinueInstruction();

int win;