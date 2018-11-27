/************************************************************************************************
Filename :	BulletManager.h / BulletManager.c
Author(s):	Ong Jia Quan Joel
Login(s) :	o.jiaquanjoel(100%)

Description/Features:
This file contains init, update, cleaning up bullet.
It contains functions to spawn, kill bullets.

************************************************************************************************/

#pragma once
#include "Header.h"

/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_BulletManager_Init();
void F_BulletManager_Update(float dt);
void F_BulletManager_Exit();

/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Spawn: Red/Blue/Green bullet */
void F_BulletManager_SpawnBullet(float posX, float posY, float dirX, float dirY);

/* Destroy: Bullet */
void F_BulletManager_KillBullet(int index);

/* Get: Bullet Inventory*/
int* F_BulletManager_GetBulletInventoryArray();

/* Get: Bullet Inventory size */
int F_BulletManager_GetBulletInventorySize();

/* Get: Bullet Inventory First Index*/
ObjectType F_BulletManager_GetBulletInventory_FirstIndex();