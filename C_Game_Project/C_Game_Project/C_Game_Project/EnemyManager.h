/************************************************************************************************
Filename :	EnemyManager.h / EnemyManager.c
Author(s):	Darren
Login(s) :	s.low (100%)

Description/Features:
This file contains init, update, cleaning up enemy.
It contains functions to random spawn, kill enemy, check collison.
************************************************************************************************/

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

/* Basic enemy initialization */
void F_EnemyManager_StartOfLevelInit(int level);

/* Return enemies left to kill */
int GetEnemiesToKill();
/* Minus enemies left to kill count by 1*/
void DecreaseEnemiesToKill();