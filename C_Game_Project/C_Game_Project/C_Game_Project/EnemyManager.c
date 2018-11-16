/************************************************************************************************
Filename :	EnemyManager.h / EnemyManager.c
Author(s):	Darren
Login(s) :	s.low (100%)

Description/Features:
...

************************************************************************************************/
#include "EnemyManager.h"
#include "GameObjectManager.h"
#include "Map.h"


/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/
int enemiesInUse;								/* Track: active bullets*/
int enemyIndices[d_MAX_ENEMIES];				/* Track: bullets are essentially movingObject/s, hence we hold indices to the moving objects that are bullets*/
float enemySpawnPosX[d_MAX_ENEMY_SPAWN_POINT];	/* Enemy Spawn Point(s): PositionX*/
float enemySpawnPosY[d_MAX_ENEMY_SPAWN_POINT];	/* Enemy Spawn Point(s): PositionY*/
int noOfSpawnPoint = 0;							/* Track: noOfSpawnPoint*/



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
	for (int i = 0; i < d_MAX_ENEMIES; ++i)
	{
		/*Initializing indices to -1.
		Since indices can only be >= 0, -1 tells me that the bullet at this index is not active*/
		enemyIndices[i] = -1;
	}

	/*Get: Enemy Spawn Point position + Num of spawn Point*/
	F_MapManager_GetEnemySpawnPosition(enemySpawnPosX, enemySpawnPosY, &noOfSpawnPoint);
	int spawnNo = noOfSpawnPoint;

}
void F_EnemyManager_Update(float dt)
{
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
	F_GameObjectManager_SetObjectSpeed(EnemyIndex, d_ENEMY_SPEED);
	F_GameObjectManager_SetObjectType(EnemyIndex, enemyType);
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
int F_EnemyManager_FindCollidedEnemyIndex_BoxCollision(float otherPosX, float otherPosY, float otherScaleX, float otherScaleY)
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
			float enemyScaleX = movingObjectList[i].scaleX;
			float enemyScaleY = movingObjectList[i].scaleY;

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
