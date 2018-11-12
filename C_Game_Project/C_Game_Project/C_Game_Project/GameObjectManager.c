#include "GameObjectManager.h"

static GameObj listOfGameObjects[MAX_GAMEOBJECTS];
static int numberInUse;

void F_GameObjectManager_Init()
{
	memset(listOfGameObjects, 0, sizeof(GameObj) * MAX_GAMEOBJECTS);
}

void F_GameObjectManager_Update(float dt)
{
	int processed = 0;
	// update position of all gameobjects
	int i;
	for (i = 0; i < MAX_GAMEOBJECTS; ++i)
	{
		if (listOfGameObjects[i].type != None &&
			listOfGameObjects[i].type != Taken)
		{
			listOfGameObjects[i].position.X += listOfGameObjects[i].velocity.X * dt;
			listOfGameObjects[i].position.Y += listOfGameObjects[i].velocity.Y * dt;

			++processed;
			if (processed >= numberInUse)
			{
				return;
			}
		}
	}
}

Vector2D F_GameObjectManager_GetObjectPosition(int index)
{
	if (index < 0 || index >= MAX_GAMEOBJECTS)
	{
		return;
	}

	return listOfGameObjects[index].position;
}

void F_GameObjectManager_SetObjectPosition(int index, Vector2D object)
{
	if (index < 0 || index >= MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].position = object;
}

Vector2D F_GameObjectManager_GetObjectPrevPosition(int index)
{
	if (index < 0 || index >= MAX_GAMEOBJECTS)
	{
		return;
	}

	return listOfGameObjects[index].prevposition;
}

void F_GameObjectManager_SetObjectPrevPosition(int index, Vector2D object)
{
	if (index < 0 || index >= MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].prevposition = object;
}

Vector2D F_GameObjectManager_GetObjectVelocity(int index)
{
	if (index < 0 || index >= MAX_GAMEOBJECTS)
	{
		return;
	}

	return listOfGameObjects[index].velocity;
}

void F_GameObjectManager_SetObjectVelocity(int index, Vector2D object)
{
	if (index < 0 || index >= MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].velocity = object;
}

//Assign a memory space for an object
int F_GameObjectManager_CreateObject()
{
	int i;
	for (i = 0; i < MAX_GAMEOBJECTS; ++i)
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

void F_GameObjectManager_SetObjectType(int index, ObjectType type)
{
	if (index < 0 || index >= MAX_GAMEOBJECTS)
	{
		return;
	}

	listOfGameObjects[index].type = type;
}

void F_GameObjectManager_SetObjectImage(int index, char image[ObjectSize])
{
	int i;
	if (index < 0 || index >= MAX_GAMEOBJECTS)
	{
		return;
	}

	for (i = 0; i < ObjectSize; ++i)
	{
		listOfGameObjects[index].image[i] = image[i];
	}
}

GameObj *GetGameObjectList()
{
	return listOfGameObjects;
}

int MovingObjectManager_GetNumberInUse()
{
	return numberInUse;
}

void GameObjectManager_ReturnMovingObjectIndex(int index)
{
	if (index < 0 || index >= MAX_GAMEOBJECTS)
	{
		return;
	}
	--numberInUse;
	/*Setting moving object back to safe state*/
	memset(&listOfGameObjects[index], 0, sizeof(GameObj));
}