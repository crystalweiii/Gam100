#include "GS_GamePlay.h"
#include "Map.h"
#include "PlayerManager.h"
#include "GameObjectManager.h"

void GS_GamePlay_Init()
{
	F_Map_Set_And_Print(2);
	F_PlayerManager_Init();
	F_Graphic_Draw();
}

void GS_GamePlay_Update(float dt) 
{
	F_GameObjectManager_Update(dt);
	F_PlayerManager_Update();
	F_Graphic_Draw();
}

void GS_GamePlay_Exit()
{
	F_PlayerManager_Exit();
	F_Map_EmptySlow();
}

