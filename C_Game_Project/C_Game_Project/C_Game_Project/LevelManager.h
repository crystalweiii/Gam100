#pragma once

void F_LevelManager_Init();
void F_LevelManager_Update();
void F_LevelManager_Exit();

void F_LevelManager_ClearLevel();
void LoadLevel(int level);
void F_LevelManager_InitEnemies(int level);

int F_LevelManager_GetCurrentLevel();