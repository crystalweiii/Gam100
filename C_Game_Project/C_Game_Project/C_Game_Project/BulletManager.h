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
void F_BulletManager_SpawnBullet(ObjectType type, float posX, float posY, float dirX, float dirY);

/* Destroy: Bullet */
void F_BulletManager_KillBullet(int index);