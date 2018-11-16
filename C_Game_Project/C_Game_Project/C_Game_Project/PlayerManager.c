/*********************************************************************************************************************
Filename :	PlayerManager.h / PlayerManager.c
Author(s):	Ong Jia Quan Joel, Desmond
Login(s) :	o.jiaquanjoel(40%), seeweedesmond.yeo(60%)

Description/Features:
This file contains init, update, cleanup for player
It contains function that handle player inputs during gameplay, and trigger event when input is enter

**********************************************************************************************************************/

//#include <math.h>
#include "Math.h"
#include "PlayerManager.h"
#include "GameObjectManager.h"
#include "Input.h"
#include "Map.h"
#include <conio.h>				/* _getch(), _kbhit()*/
#include "BulletManager.h"

/*------------------------------------------------------------------------------
// Private Variables Declaration
//----------------------------------------------------------------------------*/
float time_elasped = 0.0f;
int playerIndex;

/*------------------------------------------------------------------------------
// Private Function Declaration
//----------------------------------------------------------------------------*/
void CreateBullet(ObjectType type);

/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_PlayerManager_Init()
{
	/* Init: Used for shoot cooldown */
	time_elasped = 0.0f;

	/* Need to read from csv */
	int i = 0;
	char playerImage[ObjectSize];
	for (i = 0; i < ObjectSize; ++i)
	{
		playerImage[i] = 'a';
	}

	/* Retrieve: Empty GameObject Slot*/
	playerIndex = F_GameObjectManager_CreateObject();

	/* Assign: Player properties */
	F_GameObjectManager_SetObjectType(playerIndex, Player);
	F_GameObjectManager_SetObjectDir(playerIndex, 0, 1);
	F_GameObjectManager_SetObjectPosition(playerIndex, F_MapManager_GetPlayerSpawnPosition().X, F_MapManager_GetPlayerSpawnPosition().Y);
	F_GameObjectManager_SetObjectPrevPosition(playerIndex, F_MapManager_GetPlayerSpawnPosition().X, F_MapManager_GetPlayerSpawnPosition().Y);
	F_GameObjectManager_SetObjectSpeed(playerIndex, d_PLAYER_SPEED);
	F_GameObjectManager_SetObjectScale(playerIndex, d_CHARACTER_SCALE_X, d_CHARACTER_SCALE_Y);
	F_GameObjectManager_SetObjectImage(playerIndex, playerImage);
}
void F_PlayerManager_Update(float dt)
{
	/* Track: shoot cooldown */
	time_elasped += dt;

	/* LOOP: Turnbased input */
	F_PlayerManager_CheckInput();
}
void F_PlayerManager_Exit()
{
	/* Exit: Return object index, for objectpooling purpose */
	GameObjectManager_ReturnMovingObjectIndex(playerIndex);
}

/*------------------------------------------------------------------------------
// Others
//----------------------------------------------------------------------------*/
/* LOOP: Turnbased input */
void F_PlayerManager_CheckInput()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			/* Press Space bar */
			case 0x20:
				CreateBullet(BulletBlue);
				break;
		}
	}
}

/* Spawn: Bullet*/
void CreateBullet(ObjectType type)
{
	/* Check: Still in shoot cooldown? */
	if (time_elasped < d_RATE_OF_PLAYER_FIRE)
		return;

	/* Reset: shoot timer */
	time_elasped = 0.0f;

	/* Get: Player Info */
	GameObj object = F_GameObjectManager_GetMovingObject(playerIndex);

	/* Create: RED/BLUE/GREEN Bullet*/
	F_BulletManager_SpawnBullet(type, object.positionX + d_PLAYER_SHOOT_X_OFFSET, object.positionY, 1, 0);
}