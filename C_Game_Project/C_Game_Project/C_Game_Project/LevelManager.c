#include "LevelManager.h"
#include "Header.h"
#include "Map.h"
#include "Input.h"
#include "EnemyManager.h"
#include "BlockerManager.h"

/***********************
 * 	Private Variables
 ***********************/
int currentLevel = Level_One;
int nextLevel = Level_Two;
int win;

void F_LevelManager_Init()
{
	F_MapManager_Gameplay_Init(currentLevel);
	F_LevelManager_InitEnemies(currentLevel);
}

void F_LevelManager_Update()
{
	if (win)
		currentLevel++;

	if (currentLevel == nextLevel)
	{
		F_LevelManager_ClearLevel();
		LoadLevel(nextLevel);
		nextLevel++;
		win = 0;
	}

	/* Test */
	if (f_Check_KeyDown(0x4C))
		win = 1;
}

int F_LevelManager_GetCurrentLevel()
{
	return currentLevel;
}

/* Load enxt level */
void LoadLevel(int level)
{
	F_MapManager_Gameplay_Init(level);
	F_LevelManager_InitEnemies(Level_Two);
}

void F_LevelManager_InitEnemies(int level)
{
	F_EnemyManager_StartOfLevelInit(level);
}

/* Clears map and enemies */
void F_LevelManager_ClearLevel()
{
	F_Map_EmptySlow();
	F_EnemyManager_Exit();

	F_BlockerManager_Exit();
}

void F_LevelManager_Exit()
{
	F_LevelManager_ClearLevel();
}