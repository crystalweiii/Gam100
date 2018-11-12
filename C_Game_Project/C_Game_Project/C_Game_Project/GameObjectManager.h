#pragma once
#include "GameObject.h"

#define MAX_GAMEOBJECTS 200

void F_GameObjectManager_Init();
void F_GameObjectManager_Update(float dt);

/* Current position */
Vector2D F_GameObjectManager_GetObjectPosition(int index);
void F_GameObjectManager_SetObjectPosition(int index, Vector2D object);

/* Previous position */
Vector2D F_GameObjectManager_GetObjectPrevPosition(int index);
void F_GameObjectManager_SetObjectPrevPosition(int index, Vector2D object);

/* Velocity */
Vector2D F_GameObjectManager_GetObjectVelocity(int index);
void F_GameObjectManager_SetObjectVelocity(int index, Vector2D object);

int F_GameObjectManager_CreateObject();

/* How character looks like */
void F_GameObjectManager_SetObjectType(int index);
void F_GameObjectManager_SetObjectImage(int index, char image[]);

GameObj *GetGameObjectList();

/* Number of active gameobjects */
int MovingObjectManager_GetNumberInUse();

/* Send back the memory reserved for the object*/
void GameObjectManager_ReturnMovingObjectIndex(int index);
