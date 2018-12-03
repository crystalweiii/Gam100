/*********************************************************************************************************************
Filename :	GameObjectManager.h/ GameObjectManager.c
Author(s):	Ong Jia Quan Joel, Desmond, Darren
Login(s) :	o.jiaquanjoel(80%), seeweedesmond.yeo(10%), s.low (10%)

Description/Features:
This file contains init, update, cleanup for gameobject
It contains function that handle collision checking, response to collision, setter and getter gameobject properties

**********************************************************************************************************************/

#include "GameObjectManager.h"
#include "Map.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"

/*------------------------------------------------------------------------------
// Private Variables
//----------------------------------------------------------------------------*/
static GameObj listOfGameObjects[d_MAX_GAMEOBJECTS];

static int numberInUse;



/*------------------------------------------------------------------------------
// Private Function Declaration
//----------------------------------------------------------------------------*/
void UpdateCollisionEvent_Player(int i);
void UpdateCollisionEvent_Bullet(int i);
void UpdateCollisionEvent_Enemy(int i);
bool Check_TileCollision_With(char otherType, int index);



/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
/* Init */
void F_GameObjectManager_Init()
{
	score = 0;
	memset(listOfGameObjects, 0, sizeof(GameObj) * d_MAX_GAMEOBJECTS);
}

/* Update */
void F_GameObjectManager_Update(float dt)
{
	int processed = 0;
	// update position of all gameobjects
	int i;

	for (i = 0; i < d_MAX_GAMEOBJECTS; ++i)
	{
		if (listOfGameObjects[i].type != None &&
			listOfGameObjects[i].type != Taken)
		{
			/*----------------------------------------------------
			// Check: Out Of Bounds [Debug only, Dont remove yet]
			----------------------------------------------------*/
			/*if (F_GameObjectManager_GetObjectPositionY_Max(i) >= F_MapManager_GetMapHeight() ||
				F_GameObjectManager_GetObjectPositionY_Min(i) <= 0)
				return;
			if (F_GameObjectManager_GetObjectPositionX_Max(i) >= F_MapManager_GetMapWidth() ||
				F_GameObjectManager_GetObjectPositionX_Min(i) <= 0)
				return;*/

			/*----------------------------------------------------
			// Handle: Collision Response
			----------------------------------------------------*/
			switch (listOfGameObjects[i].type)
			{
				case Player:
					UpdateCollisionEvent_Player(i);
					break;
				case EnemyRed:
				case EnemyGreen:
				case EnemyBlue:
					UpdateCollisionEvent_Enemy(i);
					break;
				case BulletRed:
				case BulletGreen:
				case BulletBlue:
					UpdateCollisionEvent_Bullet(i);
					break;
			}

			/*----------------------------------------------------
			// Handle: Movement
			----------------------------------------------------*/
			/* Record Previous Position: Use by GraphicManager to undraw player->previous step display*/
			listOfGameObjects[i].prevPositionX = listOfGameObjects[i].positionX;
			listOfGameObjects[i].prevPositionY = listOfGameObjects[i].positionY;

			/* Calculate Velocity*/
			listOfGameObjects[i].velocityX = listOfGameObjects[i].directionX * listOfGameObjects[i].speed * dt;
			listOfGameObjects[i].velocityY = listOfGameObjects[i].directionY * listOfGameObjects[i].speed * dt;

			/* Apply Position */
			listOfGameObjects[i].positionX += listOfGameObjects[i].velocityX;
			listOfGameObjects[i].positionY += listOfGameObjects[i].velocityY;

			++processed;
			if (processed >= numberInUse)
			{
				return;
			}
		}
	}
}

/* Handle Collision Response*/
void UpdateCollisionEvent_Player(int i)
{
	/*-----------------------------------------------
	// Handle Collision: Player XXX Vertical Wall
	-----------------------------------------------*/
	if (Check_TileCollision_With(TILE_WALL_V, i))
		listOfGameObjects[i].directionX *= -1;

	/*-----------------------------------------------
	// Handle Collision: Player XXX Horizontal Wall
	-----------------------------------------------*/
	if (Check_TileCollision_With(TILE_WALL_H, i))
		listOfGameObjects[i].directionY *= -1;
}
void UpdateCollisionEvent_Bullet(int i)
{
	/*-----------------------------------------------
	// Handle Collision: Bullet XXX Enemy
	-----------------------------------------------*/
	if (Check_TileCollision_With(TILE_ENEMY, i))
	{
		/* Find: movingObjectIndex of enemy */

		//Circle Collision
		/*int hitEnemyIndex = F_EnemyManager_FindCollidedEnemyIndex_CircleCollision(listOfGameObjects[i].positionX, listOfGameObjects[i].positionY,
																			      (float)listOfGameObjects[i].scaleX / 2, (float)listOfGameObjects[i].scaleY / 2);*/

		//Box Collision [More accurate]
		int hitEnemyIndex = F_EnemyManager_FindCollidedEnemyIndex_BoxCollision(listOfGameObjects[i].positionX, listOfGameObjects[i].positionY,
																			   listOfGameObjects[i].scaleX, listOfGameObjects[i].scaleY);

		/*Found: movingObjectIndex of enemy*/
		if (hitEnemyIndex >= 0)
		{
			/*Get: both collided thing de objectType*/
			ObjectType bulletObjType = (ObjectType)F_GameObjectManager_GetObjectType(i);
			ObjectType enemyObjType = (ObjectType)F_GameObjectManager_GetObjectType(hitEnemyIndex);

			/*-----------------------------------------------
			// Handle Collision: Red Bullet XXX Enemy
			-----------------------------------------------*/
			if (bulletObjType == BulletRed)
			{
				switch (enemyObjType)
				{
				case EnemyRed:
					/*-----------------------------------------------
					// Destroy: Enemy
					-----------------------------------------------*/
					//Draw: EMPTY over Enemy
					F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[hitEnemyIndex].isVisible, (int)listOfGameObjects[hitEnemyIndex].prevPositionX, (int)listOfGameObjects[hitEnemyIndex].prevPositionY, (int)listOfGameObjects[hitEnemyIndex].scaleX, (int)listOfGameObjects[hitEnemyIndex].scaleY, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetX, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetY);
					F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[hitEnemyIndex].isVisible, (int)listOfGameObjects[hitEnemyIndex].positionX, (int)listOfGameObjects[hitEnemyIndex].positionY, (int)listOfGameObjects[hitEnemyIndex].scaleX, (int)listOfGameObjects[hitEnemyIndex].scaleY, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetX, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetY);
					//Kill: Enemy
					F_EnemyManager_KillEnemy(hitEnemyIndex);
					DecreaseEnemiesToKill();
					score += 10;
					break;

				case EnemyGreen:
				case EnemyBlue:
					/*-----------------------------------------------
					// Boost: Enemy
					-----------------------------------------------*/
					F_GameObjectManager_SetObjectSpeed(hitEnemyIndex, d_ENEMY_ANGRY_SPEED);
					break;
				}
			
				/*-----------------------------------------------
				// Destroy: Bullet
				-----------------------------------------------*/
				//Draw: EMPTY over Bullet
				F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[i].isVisible, (int)listOfGameObjects[i].positionX, (int)listOfGameObjects[i].positionY, (int)listOfGameObjects[i].scaleX, (int)listOfGameObjects[i].scaleY, (int)listOfGameObjects[i].anchorOffsetX, (int)listOfGameObjects[i].anchorOffsetY);
				//Kill: Bullet
				F_BulletManager_KillBullet(i);
			}

			/*-----------------------------------------------
			// Handle Collision: Green Bullet XXX Enemy
			-----------------------------------------------*/
			else if (bulletObjType == BulletGreen)
			{
				switch (enemyObjType)
				{
				case EnemyGreen:
					/*-----------------------------------------------
					// Destroy: Enemy
					-----------------------------------------------*/
					//Draw: EMPTY over Enemy
					F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[hitEnemyIndex].isVisible, (int)listOfGameObjects[hitEnemyIndex].prevPositionX, (int)listOfGameObjects[hitEnemyIndex].prevPositionY, (int)listOfGameObjects[hitEnemyIndex].scaleX, (int)listOfGameObjects[hitEnemyIndex].scaleY, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetX, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetY);
					F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[hitEnemyIndex].isVisible, (int)listOfGameObjects[hitEnemyIndex].positionX, (int)listOfGameObjects[hitEnemyIndex].positionY, (int)listOfGameObjects[hitEnemyIndex].scaleX, (int)listOfGameObjects[hitEnemyIndex].scaleY, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetX, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetY);
					//Kill: Enemy
					F_EnemyManager_KillEnemy(hitEnemyIndex);
					DecreaseEnemiesToKill();
					score += 10;
					break;

				case EnemyRed:
				case EnemyBlue:
					/*-----------------------------------------------
					// Boost: Enemy
					-----------------------------------------------*/
					F_GameObjectManager_SetObjectSpeed(hitEnemyIndex, d_ENEMY_ANGRY_SPEED);
					break;
				}

				/*-----------------------------------------------
				// Destroy: Bullet
				-----------------------------------------------*/
				//Draw: EMPTY over Bullet
				F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[i].isVisible, (int)listOfGameObjects[i].positionX, (int)listOfGameObjects[i].positionY, (int)listOfGameObjects[i].scaleX, (int)listOfGameObjects[i].scaleY, (int)listOfGameObjects[i].anchorOffsetX, (int)listOfGameObjects[i].anchorOffsetY);
				//Kill: Bullet
				F_BulletManager_KillBullet(i);
			}

			/*-----------------------------------------------
			// Handle Collision: Blue Bullet XXX Enemy
			-----------------------------------------------*/
			else if (bulletObjType == BulletBlue)
			{
				switch (enemyObjType)
				{
				case EnemyBlue:
					/*-----------------------------------------------
					// Destroy: Enemy
					-----------------------------------------------*/
					//Draw: EMPTY over Enemy
					F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[hitEnemyIndex].isVisible, (int)listOfGameObjects[hitEnemyIndex].prevPositionX, (int)listOfGameObjects[hitEnemyIndex].prevPositionY, (int)listOfGameObjects[hitEnemyIndex].scaleX, (int)listOfGameObjects[hitEnemyIndex].scaleY, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetX, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetY);
					F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[hitEnemyIndex].isVisible, (int)listOfGameObjects[hitEnemyIndex].positionX, (int)listOfGameObjects[hitEnemyIndex].positionY, (int)listOfGameObjects[hitEnemyIndex].scaleX, (int)listOfGameObjects[hitEnemyIndex].scaleY, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetX, (int)listOfGameObjects[hitEnemyIndex].anchorOffsetY);
					//Kill: Enemy
					F_EnemyManager_KillEnemy(hitEnemyIndex);
					DecreaseEnemiesToKill();
					score += 10;
					break;

				case EnemyGreen:
				case EnemyRed:
					/*-----------------------------------------------
					// Boost: Enemy
					-----------------------------------------------*/
					F_GameObjectManager_SetObjectSpeed(hitEnemyIndex, d_ENEMY_ANGRY_SPEED);
					break;
				}
				
				/*-----------------------------------------------
				// Destroy: Bullet
				-----------------------------------------------*/
				//Draw: EMPTY over Bullet
				F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[i].isVisible, (int)listOfGameObjects[i].positionX, (int)listOfGameObjects[i].positionY, (int)listOfGameObjects[i].scaleX, (int)listOfGameObjects[i].scaleY, (int)listOfGameObjects[i].anchorOffsetX, (int)listOfGameObjects[i].anchorOffsetY);
				//Kill: Bullet
				F_BulletManager_KillBullet(i);
			}
		}
	}
	
	/*-----------------------------------------------
	// Handle Collision: Bullet XXX Wall
	-----------------------------------------------*/
	if (Check_TileCollision_With(TILE_WALL_V, i) || Check_TileCollision_With(TILE_WALL_H, i))
	{
		/*-----------------------------------------------
		// Destroy: Bullet
		-----------------------------------------------*/
		//Draw: EMPTY over Bullet
		F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[i].isVisible, (int)listOfGameObjects[i].positionX, (int)listOfGameObjects[i].positionY, (int)listOfGameObjects[i].scaleX, (int)listOfGameObjects[i].scaleY, (int)listOfGameObjects[i].anchorOffsetX, (int)listOfGameObjects[i].anchorOffsetY);
		//Kill: Bullet
		F_BulletManager_KillBullet(i);
	}
}
void UpdateCollisionEvent_Enemy(int i)
{
	int RandDir = GenerateRandNum(3);
	/*-----------------------------------------------
	// Handle Collision: Enemy XXX Player Defense
	-----------------------------------------------*/
	if (Check_TileCollision_With(TILE_WALL_V, i) || Check_TileCollision_With(TILE_WALL_H, i) || Check_TileCollision_With(TILE_PLAYER_DEFENSE, i))
	{
		/*Draw EMPTY over ENEMY*/
		F_DrawScaleTile_Position(TILE_EMPTY, None, listOfGameObjects[i].isVisible, (int)listOfGameObjects[i].positionX, (int)listOfGameObjects[i].positionY, (int)listOfGameObjects[i].scaleX,
			                                       (int)listOfGameObjects[i].scaleY, (int)listOfGameObjects[i].anchorOffsetX, (int)listOfGameObjects[i].anchorOffsetY);

		/*Enemy Die*/
		F_EnemyManager_KillEnemy(i);

		/*Player HP--*/
		F_PlayerManager_DecrementPlayerLife(1);
	}

	if (Check_TileCollision_With(TILE_ENEMY_MOVEDOWN, i))
	{
		F_GameObjectManager_SetObjectDir(i, 0, 1);
	}

	if (Check_TileCollision_With(TILE_ENEMY_MOVEUP, i))
	{
		F_GameObjectManager_SetObjectDir(i, 0, -1);
	}

	if (Check_TileCollision_With(TILE_ENEMY_MOVELEFT, i))
	{
		F_GameObjectManager_SetObjectDir(i, -1, 0);
	}
	if (Check_TileCollision_With(TILE_ENEMY_MOVE_DOWNLEFT, i))
	{
		F_GameObjectManager_SetObjectDir(i, -1, 1);
	}
	if (Check_TileCollision_With(TILE_ENEMY_MOVE_UPLEFT, i))
	{
		F_GameObjectManager_SetObjectDir(i, -1, -1);
	}
	if (Check_TileCollision_With(TILE_ENEMY_MOVE_THREEDIR, i))
	{
		switch (RandDir)
		{
		case 0:
			F_GameObjectManager_SetObjectDir(i, -1, 0);		//Left
			break;
		case 1:
			F_GameObjectManager_SetObjectDir(i, -1, -1);	//Left Up
			break;
		case 2:
			F_GameObjectManager_SetObjectDir(i, -1, 1);		//Left Down
			break;
		}
	}
	
}


/*------------------------------------------------------------------------------
// Setter & Getter
//----------------------------------------------------------------------------*/
float F_GameObjectManager_GetObjectPositionX(int index)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return -1;
	}

	return listOfGameObjects[index].positionX;
}
float F_GameObjectManager_GetObjectPositionY(int index)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return -1;
	}

	return listOfGameObjects[index].positionY;
}
float F_GameObjectManager_GetObjectPrevPositionX(int index)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return -1;
	}

	return listOfGameObjects[index].prevPositionX;
}
float F_GameObjectManager_GetObjectPrevPositionY(int index)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return -1;
	}

	return listOfGameObjects[index].prevPositionY;
}
float F_GameObjectManager_GetObjectVelocityX(int index)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return -1;
	}

	return listOfGameObjects[index].velocityX;
}
float F_GameObjectManager_GetObjectVelocityY(int index)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return -1;
	}

	return listOfGameObjects[index].velocityY;
}
float F_GameObjectManager_GetObjectPositionX_Min(int index)
{
	/*X is 6*/
	if (listOfGameObjects[index].scaleX % 2 == 0)
		return listOfGameObjects[index].positionX + listOfGameObjects[index].scaleX / 2 - listOfGameObjects[index].scaleX;
	/*X is 5*/
	else
		return listOfGameObjects[index].positionX + listOfGameObjects[index].scaleX / 2 - listOfGameObjects[index].scaleX + 1;
}
float F_GameObjectManager_GetObjectPositionX_Max(int index)
{
	return listOfGameObjects[index].positionX - listOfGameObjects[index].scaleX / 2 + listOfGameObjects[index].scaleX - 1;
}
float F_GameObjectManager_GetObjectPositionY_Min(int index)
{
	/*X is 6*/
	if (listOfGameObjects[index].scaleY % 2 == 0)
		return listOfGameObjects[index].positionY + listOfGameObjects[index].scaleY / 2 - listOfGameObjects[index].scaleY;
	/*X is 5*/
	else
		return listOfGameObjects[index].positionY + listOfGameObjects[index].scaleY / 2 - listOfGameObjects[index].scaleY + 1;
}
float F_GameObjectManager_GetObjectPositionY_Max(int index)
{
	return listOfGameObjects[index].positionY - listOfGameObjects[index].scaleY / 2 + listOfGameObjects[index].scaleY - 1;
}
ObjectType F_GameObjectManager_GetObjectType(int index)
{
	return listOfGameObjects[index].type;
}
float F_GameObjectManager_GetObjectDirX(int index)
{
	return listOfGameObjects[index].directionX;
}
float F_GameObjectManager_GetObjectDirY(int index)
{
	return listOfGameObjects[index].directionY;
}
bool F_GameObjectManager_GetObjectVisible(int index)
{
	return listOfGameObjects[index].isVisible;
}


void F_GameObjectManager_SetObjectVisible(int index, bool visible)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].isVisible = visible;
}
void F_GameObjectManager_SetObjectDir(int index, float x, float y)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].directionX = x;
	listOfGameObjects[index].directionY = y;
}
void F_GameObjectManager_SetObjectScale(int index, int x, int y)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].scaleX = x;
	listOfGameObjects[index].scaleY = y;

	listOfGameObjects[index].anchorOffsetX = x / 2;
	listOfGameObjects[index].anchorOffsetY = y / 2;
}
void F_GameObjectManager_SetObjectSpeed(int index, float speed)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].speed = speed;
}
void F_GameObjectManager_SetObjectVelocity(int index, float x, float y)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].velocityX = x;
	listOfGameObjects[index].velocityY = x;
}
void F_GameObjectManager_SetObjectPosition(int index, float x, float y)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].positionX = x;
	listOfGameObjects[index].positionY = y;
}
void F_GameObjectManager_SetObjectPrevPosition(int index, float x, float y)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].prevPositionX = x;
	listOfGameObjects[index].prevPositionY = y;
}
void F_GameObjectManager_SetObjectType(int index, ObjectType type)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].type = type;
}
void F_GameObjectManager_SetObjectImage(int index, char image[ObjectSize])
{
	int i;
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}

	for (i = 0; i < ObjectSize; ++i)
	{
		listOfGameObjects[index].image[i] = image[i];
	}
}

void F_GameObjectManager_KillAllMapTile()
{
	int i = 0;
	for (i = 0; i < d_MAX_GAMEOBJECTS; ++i)
	{
		if (listOfGameObjects[i].type != Player)
		{
			memset(&listOfGameObjects[i], 0, sizeof(GameObj));
		}
	}
}

/*------------------------------------------------------------------------------
// Collision
//----------------------------------------------------------------------------*/
bool Check_TileCollision_With(char otherType, int index)
{
	int i = 0;
	/* Check X Axis Collision */
	if (listOfGameObjects[index].directionX != 0)
	{
		/* Check Collision: RIGHT */
		if (listOfGameObjects[index].directionX > 0)
		{
			for (i = 0; i < listOfGameObjects[index].scaleY; ++i)
			{
				/* Has Collided with otherType */
				if (F_Get_Map_DataType((int)(F_GameObjectManager_GetObjectPositionX_Max(index) + listOfGameObjects[index].velocityX), (int)(F_GameObjectManager_GetObjectPositionY_Min(index) + i)) == otherType)
					return true;
			}
		}
		/* Check Collision: LEFT */
		else if (listOfGameObjects[index].directionX < 0)
		{
			for (i = 0; i < listOfGameObjects[index].scaleY; ++i)
			{
				/* Has Collided with otherType */
				if (F_Get_Map_DataType((int)(F_GameObjectManager_GetObjectPositionX_Min(index) + listOfGameObjects[index].velocityX), (int)(F_GameObjectManager_GetObjectPositionY_Min(index) + i)) == otherType)
					return true;
			}
		}
	}

	/* Check Y Axis Collision */
	if (listOfGameObjects[index].directionY != 0)
	{
		/* Check Collision: DOWN */
		if (listOfGameObjects[index].directionY > 0)
		{
			for (i = 0; i < listOfGameObjects[index].scaleX; ++i)
			{
				/* Has Collided with otherType */
				if (F_Get_Map_DataType((int)(F_GameObjectManager_GetObjectPositionX_Min(index) + i), (int)(F_GameObjectManager_GetObjectPositionY_Max(index) + listOfGameObjects[index].velocityY)) == otherType)
					return true;
			}
		}

		/* Check Collision: UP*/
		else if (listOfGameObjects[index].directionY < 0)
		{
			for (i = 0; i < listOfGameObjects[index].scaleX; ++i)
			{
				/* Has Collided with otherType */
				if (F_Get_Map_DataType((int)(F_GameObjectManager_GetObjectPositionX_Min(index) + i), (int)(F_GameObjectManager_GetObjectPositionY_Min(index) + listOfGameObjects[index].velocityY)) == otherType)
					return true;
			}
		}
	}
	return false;
}




/*------------------------------------------------------------------------------
// Others
//----------------------------------------------------------------------------*/
//Assign a memory space for an object
int F_GameObjectManager_CreateObject()
{
	int i;
	for (i = 0; i < d_MAX_GAMEOBJECTS; ++i)
	{
		if (listOfGameObjects[i].type == None)
		{
			listOfGameObjects[i].type = Taken;
			++numberInUse;
			return i;
		}
	}
	/*No more available objects*/
	return -1;
}
int F_GameObjectManager_GetNumberInUse()
{
	return numberInUse;
}
GameObj F_GameObjectManager_GetMovingObject(int index)
{
	return listOfGameObjects[index];
}
void GameObjectManager_ReturnMovingObjectIndex(int index)
{
	if (index < 0 || index >= d_MAX_GAMEOBJECTS)
	{
		return;
	}
	--numberInUse;
	/*Setting moving object back to safe state*/
	memset(&listOfGameObjects[index], 0, sizeof(GameObj));
}
GameObj *GetGameObjectList()
{
	return listOfGameObjects;
}

