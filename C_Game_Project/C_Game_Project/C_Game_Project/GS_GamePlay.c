#include "GS_GamePlay.h"
#include "Map.h"
#include "PlayerManager.h"
#include "GameObjectManager.h"
#include "WindowsHelper.h"
#include "BulletManager.h"
#include "EnemyManager.h"

void GS_GamePlay_Init()
{
	/* Window: Make sure its full screen  */
	WindowsHelper_Init();

	/* Map: "Retrieve" level->mapdata */
	F_MapManager_Gameplay_Init(Level_One);

	/* GameObjectManager: memset all gameobject elements */
	F_GameObjectManager_Init();

	/* PlayerManager: create and spawn player*/
	F_PlayerManager_Init();

	/* GraphicManager: Static objects like wall "ONCE" */
	F_Graphic_RenderStaticObject();

	/* BulletManager: Init all bullet indices*/
	F_BulletManager_Init();

	/* EnemyManager: Init all enemy indices*/
	F_EnemyManager_Init();

	/*Spawn Enemy*/
	F_EnemyManager_SpawnEnemy(0, EnemyRed, -1, 0);
	F_EnemyManager_SpawnEnemy(1, EnemyBlue, -1, 0);
	F_EnemyManager_SpawnEnemy(2, EnemyGreen, -1, 0);
	F_EnemyManager_SpawnEnemy(3, EnemyBlue, -1, 0);
	F_EnemyManager_SpawnEnemy(4, EnemyBlue, -1, 0);
}

void GS_GamePlay_Update(float dt) 
{
	F_GameObjectManager_Update(dt);
	F_PlayerManager_Update(dt);
	F_Graphic_Draw();
}

void GS_GamePlay_Exit()
{
	F_PlayerManager_Exit();
	F_BulletManager_Exit();
	F_EnemyManager_Exit();
	//F_Map_EmptySlow();
}

