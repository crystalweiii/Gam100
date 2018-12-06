#include "Header.h"
#include "Map.h"
#include "Input.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "BlockerManager.h"
#include "GameManager.h"
#include "GS_GamePlay.h"
#include "GameObjectManager.h"
#include "UiHandler.h"
#include "LevelManager.h"
#include "BulletManager.h"

/***********************
 * 	Private Variables
 ***********************/
int currentLevel = Level_One;
int nextLevel = Level_Two;

void F_LevelManager_Init()
{
	currentLevel = Level_One;
	nextLevel = Level_Two;
	F_UI_Game_Info_Right();
	F_MapManager_Gameplay_Init(currentLevel);
	F_LevelManager_InitEnemies(currentLevel);
}

void F_LevelManager_Update()
{	
	if (win)
	{
		GS_SetGamePaused(1);
		win = 0;
		currentLevel++;
		PrintContinueInstruction();
		return;
	}

	if (currentLevel == nextLevel)
	{
		if(currentLevel == d_map_amount - 3)
		{
			F_LevelManager_Exit();
			win = 0;
		}
		else
		{
			F_LevelManager_ClearLevel();
			LoadLevel(nextLevel);
			nextLevel++;
			win = 0;
		}
	}
	
	F_LevelManager_CheckIfWin();

	/* Test press L to restart to mainmenu */
	if (f_Check_KeyDown(0x4C))
	{
		//F_LevelManager_Exit();
		win = 1;
	}
}

int F_LevelManager_GetCurrentLevel()
{
	return currentLevel;
}

void F_LevelManager_SetCurrentLevel(int level)
{
	currentLevel = level;
}

/* Load next level */
void LoadLevel(int level)
{
	//F_PlayerManager_Init();
	F_MapManager_Gameplay_Init(level);
	F_LevelManager_InitEnemies(level);
	F_BlockerManager_Init();
	F_PlayerManager_RestartPlayerLife();
	F_UI_Game_Info_Right();
}

void F_LevelManager_InitEnemies(int level)
{
	F_EnemyManager_StartOfLevelInit(level);
}

/* Clears map and enemies */
void F_LevelManager_ClearLevel()
{
	F_Map_EmptySlow();
	//F_PlayerManager_Exit();
	F_EnemyManager_Exit();
	F_BlockerManager_Exit();
	F_BulletManager_Exit();
	F_GameObjectManager_KillAllMapTile();
}

void F_LevelManager_Exit()
{
	F_LevelManager_ClearLevel();
	F_GSManager_ChangeState(GameOver);
}

void F_LevelManager_Lost()
{
	F_LevelManager_Exit();
	win = 0;
}

int F_LevelManager_CheckIfWin()
{
	if (GetEnemiesToKill() <= 0)
		win = 1;
	return win;
}

void PrintContinueInstruction()
{
	F_LevelManager_ClearLevel();
	F_UI_Game_Continue_Instru();
}