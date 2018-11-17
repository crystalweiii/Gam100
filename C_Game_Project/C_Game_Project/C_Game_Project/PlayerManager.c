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
int playerIndex1, playerIndex2;

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
	playerIndex1 = F_GameObjectManager_CreateObject();
	playerIndex2 = F_GameObjectManager_CreateObject();

	/* Assign: Player 1 properties */
	F_GameObjectManager_SetObjectType(playerIndex1, Player);
	F_GameObjectManager_SetObjectPosition(playerIndex1, F_MapManager_GetPlayer1SpawnPosition().X, F_MapManager_GetPlayer1SpawnPosition().Y);
	F_GameObjectManager_SetObjectPrevPosition(playerIndex1, F_MapManager_GetPlayer1SpawnPosition().X, F_MapManager_GetPlayer1SpawnPosition().Y);
	F_GameObjectManager_SetObjectSpeed(playerIndex1, d_PLAYER_SPEED);
	F_GameObjectManager_SetObjectScale(playerIndex1, d_CHARACTER_SCALE_X, d_CHARACTER_SCALE_Y);
	F_GameObjectManager_SetObjectImage(playerIndex1, playerImage);

	/* Assign: Player 2 properties */
	F_GameObjectManager_SetObjectType(playerIndex2, Player);
	F_GameObjectManager_SetObjectPosition(playerIndex2, F_MapManager_GetPlayer2SpawnPosition().X, F_MapManager_GetPlayer2SpawnPosition().Y);
	F_GameObjectManager_SetObjectPrevPosition(playerIndex2, F_MapManager_GetPlayer2SpawnPosition().X, F_MapManager_GetPlayer2SpawnPosition().Y);
	F_GameObjectManager_SetObjectSpeed(playerIndex2, d_PLAYER_SPEED);
	F_GameObjectManager_SetObjectScale(playerIndex2, d_CHARACTER_SCALE_X, d_CHARACTER_SCALE_Y);
	F_GameObjectManager_SetObjectImage(playerIndex2, playerImage);

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
	GameObjectManager_ReturnMovingObjectIndex(playerIndex1);
	GameObjectManager_ReturnMovingObjectIndex(playerIndex2);
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
				CreateBullet(BulletBlue, playerIndex1);
				break;
			/* Press backspace *TEMP* */
			case 0x08:
				CreateBullet(BulletBlue, playerIndex2);
				break;
		}
	}

	if (f_Check_KeyDown(0x26)) /* Press 'UP ARROW KEY' */
	{
		F_GameObjectManager_SetObjectDir(playerIndex1, 0, -1);
	}
	else if (f_Check_KeyDown(0x28)) /* Press 'DOWN ARROW KEY' */
	{
		F_GameObjectManager_SetObjectDir(playerIndex1, 0, 1); /* STOPS MOVEMENT */
	}
	else
	{
		F_GameObjectManager_SetObjectDir(playerIndex1, 0, 0);
	}

	if (f_Check_KeyDown(0x25)) /* Press 'LEFT ARROW KEY' */
	{
		F_GameObjectManager_SetObjectDir(playerIndex2, -1, 0);
	}
	else if (f_Check_KeyDown(0x27)) /* Press 'RIGHT ARROW KEY' */
	{
		F_GameObjectManager_SetObjectDir(playerIndex2, 1, 0);
	}
	else
	{
		F_GameObjectManager_SetObjectDir(playerIndex2, 0, 0); /* STOPS MOVEMENT */
	}

}

/* Spawn: Bullet*/
void CreateBullet(ObjectType type, int owner)
{
	/* Check: Still in shoot cooldown? */
	if (time_elasped < d_RATE_OF_PLAYER_FIRE)
		return;

	/* Reset: shoot timer */
	time_elasped = 0.0f;

	/* Get: Player Info */
	GameObj object = F_GameObjectManager_GetMovingObject(owner);

	/* Create: RED/BLUE/GREEN Bullet*/\
	if (owner == playerIndex1)
		F_BulletManager_SpawnBullet(type, object.positionX + d_PLAYER_SHOOT_X_OFFSET, object.positionY, 1, 0);
	else if (owner == playerIndex2)
		F_BulletManager_SpawnBullet(type, object.positionX, object.positionY + d_PLAYER_SHOOT_Y_OFFSET, 0, -1);

}