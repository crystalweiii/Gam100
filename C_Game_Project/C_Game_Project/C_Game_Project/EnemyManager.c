/************************************************************************************************
Filename :	EnemyManager.h / EnemyManager.c
Author(s):	Darren
Login(s) :	s.low (100%)

Description/Features:
This file contains init, update, cleaning up enemy.
It contains functions to random spawn, kill enemy, check collison.

************************************************************************************************/
#include "EnemyManager.h"
#include "GameObjectManager.h"
#include "Map.h"
#include "LevelManager.h"
#include "RandNumManager.h"
#include "UiHandler.h"


/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/
int enemiesInUse;									/* Track: active enemies*/
int enemyIndices[d_MAX_ENEMIES];					/* Track: movingObject/s, hence we hold indices to the moving objects that are enemies*/

//Spawn Variables
float enemySpawnPosX[d_MAX_ENEMY_SPAWN_POINT];		/* Enemy Spawn Point(s): PositionX*/
float enemySpawnPosY[d_MAX_ENEMY_SPAWN_POINT];		/* Enemy Spawn Point(s): PositionY*/
FaceDir enemySpawnFaceDir[d_MAX_ENEMY_SPAWN_POINT]; /* Track: spawn face dir */
int noOfSpawnPoint = 0;								/* Track: noOfSpawnPoint */

//Movement
float enemyDirX[d_MAX_ENEMY_SPAWN_POINT];			/* Enemy Direction: PositionX*/
float enemyDirY[d_MAX_ENEMY_SPAWN_POINT];			/* Enemy Direction: PositionY*/
int enemiesToKill;
float enemy_time_elasped = 0.0f;



/*------------------------------------------------------------------------------
// Private Function Declaration:
//----------------------------------------------------------------------------*/
void F_EnemyManager_AddEnemyIndex(int index);
float GetSpawnPositionX(int index);
float GetSpawnPositionY(int index);



/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_EnemyManager_Init()
{
	/*No bullets in use yet*/
	enemiesInUse = 0;

	/*Set all bullet related data to initial state*/
	int i = 0;
	for (i = 0; i < d_MAX_ENEMIES; ++i)
	{
		/*Initializing indices to -1.
		Since indices can only be >= 0, -1 tells me that the bullet at this index is not active*/
		enemyIndices[i] = -1;
	}

	F_EnemyManager_StartOfLevelInit(Level_One);
}

void F_EnemyManager_Update(float dt)
{
	int RandEType = GenerateRandNum(3);						// Random: enemytype
	int RandLaneSpot = GenerateRandNum(noOfSpawnPoint);		// Random: spawn position
	float dirX = 0.0f; 		
	float dirY = 0.0f;

	/*[Get]: Enemy->Spawn FaceDir*/
	switch (enemySpawnFaceDir[RandLaneSpot])				// Assign: Spawn Enemy Move Dir
	{
		case FACE_DOWN:
			dirX = 0.0f;
			dirY = 1.0f;
			break;
		case FACE_LEFT:
			dirX = -1.0f;
			dirY = 0.0f;
			break;
		case FACE_UP_LEFT:
			dirX = -1.0f;
			dirY = -1.0f;
			break;
		case FACE_DOWN_LEFT:
			dirX = -1.0f;
			dirY = 1.0f;
			break;
	}		

	enemy_time_elasped += dt;

	/* Check: Still in spawn cd*/
	if (enemy_time_elasped < d_RATE_OF_ENEMY_SPAWN + F_LevelManager_GetCurrentLevel() * 0.2f)
		return;

	/* Reset: spawn timer */
	enemy_time_elasped = 0.0f;

	switch (RandEType)
	{
		case 0:
			F_EnemyManager_SpawnEnemy(RandLaneSpot, EnemyRed, dirX, dirY);
			break;
		case 1:
			F_EnemyManager_SpawnEnemy(RandLaneSpot, EnemyBlue, dirX, dirY);
			break;
		case 2:
			F_EnemyManager_SpawnEnemy(RandLaneSpot, EnemyGreen, dirX, dirY);
			break;
		default:
			F_EnemyManager_SpawnEnemy(RandLaneSpot, EnemyRed, dirX, dirY);
			break;
	}
}

void F_EnemyManager_Exit()
{
	for (int i = 0; i < d_MAX_ENEMIES; ++i)
	{
		if (enemyIndices[i] == -1)
		{
			continue;
		}
		F_EnemyManager_KillEnemy(enemyIndices[i]);
	}
}

void F_EnemyManager_StartOfLevelInit(int level)
{
	int i = 0;

	/*Get: Num of spawn Point*/
	noOfSpawnPoint = F_MapManager_GetEnemyTotalSpawnPoint();

	/* Spawn Enemy depending on which map*/
	switch (level)
	{
	case Level_One:
		enemiesToKill = 5;
		break;
	case Level_Two:
		enemiesToKill = 5;
		break;
	case Level_Three:
		enemiesToKill = 15;
		break;
	case Level_Four:
		enemiesToKill = 20;
		break;
	case Level_Five:
		enemiesToKill = 25;
		break;
	case Level_GameOver:
		enemiesToKill = 3;
		break;
	case Level_Win:
		enemiesToKill = 0;
		break;
	}

	/*Get: Enemy Spawn Position*/
	float* tmpX = F_MapManager_GetEnemySpawnPositionX();
	float* tmpY = F_MapManager_GetEnemySpawnPositionY();
	for (i = 0; i < noOfSpawnPoint; ++i)
	{
		enemySpawnPosX[i] = *(tmpX + i);
		enemySpawnPosY[i] = *(tmpY + i);
	}

	/*Get: Enemy Spawn Face Dir*/
	FaceDir* tmpFaceDir = F_MapManager_GetEnemySpawnFaceDir();
	for (i = 0; i < noOfSpawnPoint; ++i)
	{
		enemySpawnFaceDir[i] = tmpFaceDir[i];
	}
}

/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Spawn: Red/Blue/Green Enemy */
void F_EnemyManager_SpawnEnemy(int laneToSpawn, ObjectType enemyType, float dirX, float dirY)
{
	//int RandType = GenerateRandNum(3);
	int RandSpawnSpot = laneToSpawn; //GenerateRandNum(noOfSpawnPoint);

	if (enemiesInUse >= d_MAX_ENEMIES)
		return;

	/*Getting an index to a moving object we can use*/
	int EnemyIndex = F_GameObjectManager_CreateObject();

	/*If all moving objects are in use, MovingObjectManager will give us an index of -1*/
	if (EnemyIndex == -1)
		return;

	/*Keep track of the index we got from MovingObjectManager*/
	F_EnemyManager_AddEnemyIndex(EnemyIndex);

	//- Assign to random Spawn Position
	F_GameObjectManager_SetObjectPosition(EnemyIndex, GetSpawnPositionX(RandSpawnSpot), GetSpawnPositionY(RandSpawnSpot));
	F_GameObjectManager_SetObjectPrevPosition(EnemyIndex, GetSpawnPositionX(RandSpawnSpot), GetSpawnPositionY(RandSpawnSpot));
	F_GameObjectManager_SetObjectScale(EnemyIndex, d_CHARACTER_SCALE_X, d_CHARACTER_SCALE_Y);
	F_GameObjectManager_SetObjectDir(EnemyIndex, dirX, dirY);
	F_GameObjectManager_SetObjectSpeed(EnemyIndex, (float)(d_ENEMY_SPEED + 2));
	F_GameObjectManager_SetObjectType(EnemyIndex, enemyType);
	F_GameObjectManager_SetObjectVisible(EnemyIndex, true);
}

/* Destroy: Enemy */
void F_EnemyManager_KillEnemy(int index)
{
	if (index < 0)
		return;

	for (int i = 0; i < d_MAX_ENEMIES; ++i)
	{
		if (enemyIndices[i] == index)
		{
			/* Return: to gameObjManager for objectpooling purposes*/
			GameObjectManager_ReturnMovingObjectIndex(enemyIndices[i]);
			enemyIndices[i] = -1;
			--enemiesInUse;
			return;
		}
	}
}



/*------------------------------------------------------------------------------
// Setter & Getter
//----------------------------------------------------------------------------*/
/* Get: Enemy ascii code */
char F_EnemyManager_GetEnemyDisplay()
{
	return 'E';
}

/* Get: Enemy Spawn Point PositionX */
float GetSpawnPositionX(int index)

{
	return enemySpawnPosX[index];
}

/* Get: Enemy Spawn Point PositionY */
float GetSpawnPositionY(int index)
{
	return enemySpawnPosY[index];
}

/* Get Enemies left to kill */
int GetEnemiesToKill()
{
	return enemiesToKill;
}

/* Minus enemies left to kill count by 1*/
void DecreaseEnemiesToKill()
{
	--enemiesToKill;

	// Update UI: Enemies To kill 
	F_UI_Game_Info_Right();
}

/*------------------------------------------------------------------------------
// Collision
//----------------------------------------------------------------------------*/
/* Collision: Circle Collision*/
int F_EnemyManager_FindCollidedEnemyIndex_CircleCollision(float collidedPosX, float collidedPosY, float radiusX, float radiusY)
{
	int i = 0;
	GameObj* movingObjectList = GetGameObjectList();
	for (i = 0; i < d_MAX_GAMEOBJECTS; ++i)
	{
		if (movingObjectList[i].type == EnemyRed || movingObjectList[i].type == EnemyGreen || movingObjectList[i].type == EnemyBlue)
		{
			if (movingObjectList[i].positionX - collidedPosX < movingObjectList[i].scaleX + radiusX)
			{
				if (collidedPosY - movingObjectList[i].positionY < movingObjectList[i].scaleY + radiusY)
				{
					return i;
				}
			}
		}
	}

	return -1;
}

/* Collision: Box Collision */
int F_EnemyManager_FindCollidedEnemyIndex_BoxCollision(float otherPosX, float otherPosY, int otherScaleX, int otherScaleY)
{
	int i = 0;
	GameObj* movingObjectList = GetGameObjectList();
	for (i = 0; i < d_MAX_GAMEOBJECTS; ++i)
	{
		if (movingObjectList[i].type == EnemyRed || movingObjectList[i].type == EnemyGreen || movingObjectList[i].type == EnemyBlue)
		{
			/*2D Bounding Box Collision*/
			float enemyPosX = movingObjectList[i].positionX;
			float enemyPosY = movingObjectList[i].positionY;
			int enemyScaleX = movingObjectList[i].scaleX;
			int enemyScaleY = movingObjectList[i].scaleY;

			//Enemy: MinX and MaxX is it between 
			//Collided: MinX and MaxX
			if (
				enemyPosX < otherPosX + otherScaleX &&
				enemyPosX + enemyScaleX > otherPosX &&
				enemyPosY < otherPosY + otherScaleY &&
				enemyPosY + enemyScaleY > otherPosY)
			{
				return i;
			}
		}
	}

	return -1;
}




/*------------------------------------------------------------------------------
// Other
//----------------------------------------------------------------------------*/
/* Add: Bullet indices*/
void F_EnemyManager_AddEnemyIndex(int index)
{
	if (index < 0)
	{
		return;
	}

	for (int i = 0; i < d_MAX_ENEMIES; ++i)
	{
		if (enemyIndices[i] == -1)
		{
			enemyIndices[i] = index;
			++enemiesInUse;
			break;
		}
	}
}
