/*********************************************************************************************************************
Filename :	GS_GamePlay.h / GS_GamePlay.c
Author(s):	Ong Jia Quan Joel
Login(s) :	o.jiaquanjoel(100%)

Description/Features:
This is for the gameplay state, where others will then link up with their gameplay logics
**********************************************************************************************************************/

#include "GS_GamePlay.h"
#include "LevelManager.h"
#include "Map.h"
#include "PlayerManager.h"
#include "GameObjectManager.h"
#include "WindowsHelper.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "BlockerManager.h"
#include "UiHandler.h"

void GS_GamePlay_Init()
{
	/* Window: Make sure its full screen  */
	//WindowsHelper_Init();
	
	/* Handles level loading stuff etc*/
	F_LevelManager_Init();

	/* GameObjectManager: memset all gameobject elements */
	F_GameObjectManager_Init();

	/* PlayerManager: create and spawn player*/
	F_PlayerManager_Init();

	/* BulletManager: Init all bullet indices*/
	F_BulletManager_Init();

	/* EnemyManager: Init all enemy indices*/
	F_EnemyManager_Init();

	/* BlockerManager: Init and spawn blocker */
	F_BlockerManager_Init();

	/* Printing of instruction*/
	F_UI_Print_Out_Index(PT_Game_Instruction);
	F_UI_Print_Out_Index(PT_Game_Info_Right);
}

void GS_GamePlay_Update(float dt) 
{
	F_GameObjectManager_Update(dt);
	F_PlayerManager_Update(dt);
	F_EnemyManager_Update(dt);
	F_LevelManager_Update();
	F_Graphic_Draw();
}

void GS_GamePlay_Exit()
{

	F_UI_Clear_Index(PT_Game_Instruction);
	F_UI_Clear_Index(PT_Game_Info_Right);
	F_PlayerManager_Exit();
	F_BulletManager_Exit();
	F_EnemyManager_Exit();
	F_LevelManager_Exit();
	F_BlockerManager_Exit();
}

