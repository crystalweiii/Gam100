#pragma once
#include "GameObject.h"
#include "Math.h"
#include <stdbool.h>
#include "Header.h"


/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_GameObjectManager_Init();
void F_GameObjectManager_Update(float dt);

/*------------------------------------------------------------------------------
// Setter & Getter
//----------------------------------------------------------------------------*/
/* Dir, Scale, Speed */
void F_GameObjectManager_SetObjectDir(int index, float x, float y);
void F_GameObjectManager_SetObjectScale(int index, int x, int y);
void F_GameObjectManager_SetObjectSpeed(int index, float speed);

/* Current position */
float F_GameObjectManager_GetObjectPositionX(int index);
float F_GameObjectManager_GetObjectPositionY(int index);
void F_GameObjectManager_SetObjectPosition(int index, float x, float y);

/* Previous position */
float F_GameObjectManager_GetObjectPrevPositionX(int index);
float F_GameObjectManager_GetObjectPrevPositionY(int index);
void F_GameObjectManager_SetObjectPrevPosition(int index, float x, float y);

/* Velocity */
float F_GameObjectManager_GetObjectVelocityX(int index);
float F_GameObjectManager_GetObjectVelocityY(int index);
void F_GameObjectManager_SetObjectVelocity(int index, float x, float y);

/* How character looks like */
void F_GameObjectManager_SetObjectType(int index, ObjectType type);
void F_GameObjectManager_SetObjectImage(int index, char image[ObjectSize]);

/* Corner Position */
float F_GameObjectManager_GetObjectPositionX_Min(int index);
float F_GameObjectManager_GetObjectPositionX_Max(int index);
float F_GameObjectManager_GetObjectPositionY_Min(int index);
float F_GameObjectManager_GetObjectPositionY_Max(int index);

/* Object Type*/
ObjectType F_GameObjectManager_GetObjectType(int index);


/*------------------------------------------------------------------------------
// Others
//----------------------------------------------------------------------------*/
GameObj F_GameObjectManager_GetMovingObject(int index);
GameObj *GetGameObjectList();
int F_GameObjectManager_CreateObject();
int F_GameObjectManager_GetNumberInUse();				   /* Number of active gameobjects */
void GameObjectManager_ReturnMovingObjectIndex(int index); /* Send back the memory reserved for the object*/

