/************************************************************************************************
Filename :	Blocker.h / Blocker.c
Author(s):
Login(s) :

Description/Features:
This file contains init, update, cleaning up blocker.
It contains functions to blocker, kill blocker.

************************************************************************************************/

#include "BlockerManager.h"
#include "GameObjectManager.h"
#include "Map.h"

/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/
int blockersInUse;				  /*Number of bullets currently in use*/
int blockersIndices[d_MAX_BLOCKERS]; /*Bullets are essentially MovingObject/s, hence we hold indices to the moving objects that are bullets*/



/*------------------------------------------------------------------------------
// Private Function Declaration:
//----------------------------------------------------------------------------*/
void BlockerManager_AddBlockerIndex(int index);
void RetrieveData_And_SpawnBlocker();


/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_BlockerManager_Init()
{
	/* Set: no bullets in use yet */
	blockersInUse = 0;

	/* Set: all bulletIndices to -1, tells me that the bullet at this index is not active */
	for (int i = 0; i < d_MAX_BLOCKERS; ++i)
		blockersIndices[i] = -1;

	/* Retrieve and Spawn: Blocker position data from map*/
	RetrieveData_And_SpawnBlocker();
}
void F_BlockerManager_Update()
{
}
void F_BlockerManager_Exit()
{
	for (int i = 0; i < d_MAX_BLOCKERS; ++i)
	{
		if (blockersIndices[i] == -1)
			continue;
		F_BlockerManager_KillBlocker(blockersIndices[i]);
	}
}



/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
void RetrieveData_And_SpawnBlocker()
{
	int x, y;
	x = y = 0;
	for (y = 0; y < d_game_height; ++y)
	{
		for (x = 0; x < d_game_width; ++x)
		{
			if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_MOVEUP)
				F_BlockerManager_SpawnBlocker(BlockerUp, x, y);

			else if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_MOVEDOWN)
					F_BlockerManager_SpawnBlocker(BlockerDown, x, y);

			else if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_MOVELEFT)
				F_BlockerManager_SpawnBlocker(BlockerLeft, x, y);

			else if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_MOVERIGHT)
				F_BlockerManager_SpawnBlocker(BlockerRight, x, y);

			else if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_MOVE_DOWNLEFT)
				F_BlockerManager_SpawnBlocker(BlockerDownLeft, x, y);

			else if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_MOVE_UPLEFT)
				F_BlockerManager_SpawnBlocker(BlockerUpLeft, x, y);

			else if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_MOVE_THREEDIR)
				F_BlockerManager_SpawnBlocker(BlockerThreeDir, x, y);

			else if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_MOVE_TWODIR_LEFT_TOPLEFT)
				F_BlockerManager_SpawnBlocker(BlockerTwoDir_Left_TopLeft, x, y);

			else if (s_current_map.V_Map_Array[y][x] == TILE_ENEMY_MOVE_TWODIR_LEFT_BTMLEFT)
				F_BlockerManager_SpawnBlocker(BlockerTwoDir_Left_BtmLeft, x, y);
		}
	}
}
/* Destroy: Bullet */
void F_BlockerManager_KillBlocker(int index)
{
	if (index < 0)
	{
		return;
	}

	for (int i = 0; i < d_MAX_BLOCKERS; ++i)
	{
		if (blockersIndices[i] == index)
		{
			/* Return: to gameObjManager for objectpooling purposes*/
			GameObjectManager_ReturnMovingObjectIndex(blockersIndices[i]);
			blockersIndices[i] = -1;
			--blockersInUse;
			return;
		}
	}
}

/* Spawn: Red/Blue/Green bullet */
void F_BlockerManager_SpawnBlocker(ObjectType type, float posX, float posY)
{
	/* Check: Did we max out bullet */
	if (blockersInUse >= d_MAX_BLOCKERS)
		return;

	/* Find: an index to a moving object we can use */
	int blockerIndex = F_GameObjectManager_CreateObject();

	/* If cannot find, return */
	if (blockerIndex == -1)
		return;

	/* Track: index we got from GameObjectManager*/
	BlockerManager_AddBlockerIndex(blockerIndex);

	/* Set: bullet properties*/
	F_GameObjectManager_SetObjectType(blockerIndex, type);
	F_GameObjectManager_SetObjectPosition(blockerIndex, posX, posY);
	F_GameObjectManager_SetObjectPrevPosition(blockerIndex, posX, posY);
	F_GameObjectManager_SetObjectDir(blockerIndex, 0, 0);
	F_GameObjectManager_SetObjectScale(blockerIndex, 1, 1);
	F_GameObjectManager_SetObjectSpeed(blockerIndex, 0);
	F_GameObjectManager_SetObjectVisible(blockerIndex, d_BLOCKER_IS_VISIBLE);
}



/*------------------------------------------------------------------------------
// Other
//----------------------------------------------------------------------------*/
/* Add: Bullet indices*/
void BlockerManager_AddBlockerIndex(int index)
{
	if (index < 0)
	{
		return;
	}

	for (int i = 0; i < d_MAX_BLOCKERS; ++i)
	{
		if (blockersIndices[i] == -1)
		{
			blockersIndices[i] = index;
			++blockersInUse;
			break;
		}
	}
}