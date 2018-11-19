/************************************************************************************************
Filename :	BulletManager.h / BulletManager.c
Author(s):	Ong Jia Quan Joel
Login(s) :	o.jiaquanjoel(100%)

Description/Features:
This file contains init, update, cleaning up bullet.
It contains functions to spawn, kill bullets

************************************************************************************************/

#include "BulletManager.h"
#include "GameObjectManager.h"
#include <time.h>

/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/
int bulletsInUse;				  /*Number of bullets currently in use*/
int bulletIndices[d_MAX_BULLETS]; /*Bullets are essentially MovingObject/s, hence we hold indices to the moving objects that are bullets*/



/*------------------------------------------------------------------------------
// Private Function Declaration:
//----------------------------------------------------------------------------*/
void BulletManager_AddBulletIndex(int index);



/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_BulletManager_Init()
{
	/* Set: no bullets in use yet */
	bulletsInUse = 0;

	/* Set: all bulletIndices to -1, tells me that the bullet at this index is not active */
	for (int i = 0; i < d_MAX_BULLETS; ++i)
		bulletIndices[i] = -1;
}
void F_BulletManager_Update(float dt)
{
}
void F_BulletManager_Exit()
{
	for (int i = 0; i < d_MAX_BULLETS; ++i)
	{
		if (bulletIndices[i] == -1)
			continue;
		F_BulletManager_KillBullet(bulletIndices[i]);
	}
}



/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Destroy: Bullet */
void F_BulletManager_KillBullet(int index)
{
	if (index < 0)
	{
		return;
	}

	for (int i = 0; i < d_MAX_BULLETS; ++i)
	{
		if (bulletIndices[i] == index)
		{
			/* Return: to gameObjManager for objectpooling purposes*/
			GameObjectManager_ReturnMovingObjectIndex(bulletIndices[i]);
			bulletIndices[i] = -1;
			--bulletsInUse;
			return;
		}
	}
}

/* Spawn: Red/Blue/Green bullet */
void F_BulletManager_SpawnBullet(ObjectType type, float posX, float posY, float dirX, float dirY)
{
	/* Check: Did we max out bullet */
	if (bulletsInUse >= d_MAX_BULLETS)
		return;

	/* Find: an index to a moving object we can use */
	int bulletIndex = F_GameObjectManager_CreateObject();

	/* If cannot find, return */
	if (bulletIndex == -1)
		return;

	/* Track: index we got from GameObjectManager*/
	BulletManager_AddBulletIndex(bulletIndex);

	/* Set: bullet properties*/
	F_GameObjectManager_SetObjectType(bulletIndex, type);
	F_GameObjectManager_SetObjectPosition(bulletIndex, posX, posY);
	F_GameObjectManager_SetObjectPrevPosition(bulletIndex, posX, posY);
	F_GameObjectManager_SetObjectDir(bulletIndex, dirX, dirY);
	F_GameObjectManager_SetObjectScale(bulletIndex, d_CHARACTER_SCALE_X, d_CHARACTER_SCALE_Y);
	F_GameObjectManager_SetObjectSpeed(bulletIndex, d_BULLET_SPEED);
	F_GameObjectManager_SetObjectVisible(bulletIndex, true);
}



/*------------------------------------------------------------------------------
// Other
//----------------------------------------------------------------------------*/
/* Add: Bullet indices*/
void BulletManager_AddBulletIndex(int index)
{
	if (index < 0)
	{
		return;
	}

	for (int i = 0; i < d_MAX_BULLETS; ++i)
	{
		if (bulletIndices[i] == -1)
		{
			bulletIndices[i] = index;
			++bulletsInUse;
			break;
		}
	}
}