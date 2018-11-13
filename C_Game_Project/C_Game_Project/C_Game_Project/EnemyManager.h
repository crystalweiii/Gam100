#pragma once
#include "Header.h"

/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_EnemyManager_Init();
void F_EnemyManager_Update(float dt);
void F_EnemyManager_Exit();

/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Spawn: Enemy*/
void F_EnemyManager_SpawnEnemy(int laneToSpawn, ObjectType enemyType, float dirX, float dirY);

/* Kill: Enemy */
void F_EnemyManager_KillEnemy(int index);

/* Get: Enemy Display */
char F_EnemyManager_GetEnemyDisplay();

/* Collision: Circle Collision*/
int F_EnemyManager_FindCollidedEnemyIndex_CircleCollision(float collidedPosX, float collidedPosY, float radiusX, float radiusY);

/* Collision: Box Collision */
int F_EnemyManager_FindCollidedEnemyIndex_BoxCollision(float otherPosX, float otherPosY, float otherScaleX, float otherScaleY);