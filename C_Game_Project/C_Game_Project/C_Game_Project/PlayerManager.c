#include <math.h>
#include "PlayerManager.h"
#include "GameObjectManager.h"
#include "Input.h"

void F_PlayerManager_Init()
{
	int i = 0;

	/* Need to read from csv */
	char playerImage[ObjectSize];
	for (i = 0; i < ObjectSize; ++i)
	{
		playerImage[i] = 'a';
	}

	/* Set player initial position*/
	Vector2D playerPosition;
	playerPosition.X = 10;
	playerPosition.Y = 10;

	playerIndex = F_GameObjectManager_CreateObject();
	F_GameObjectManager_SetObjectType(playerIndex, Player);
	F_GameObjectManager_SetObjectPosition(playerIndex, playerPosition);
	F_GameObjectManager_SetObjectImage(playerIndex, playerImage);
}
void F_PlayerManager_Update()
{
	F_PlayerManager_CheckInput();
}
void F_PlayerManager_Exit()
{
	GameObjectManager_ReturnMovingObjectIndex(playerIndex);
}

void F_PlayerManager_CheckInput()
{
	Vector2D playerPosition = F_GameObjectManager_GetObjectPosition(playerIndex);
	if (f_Check_KeyDown(0x57)) /* Press 'w' */
	{
		F_GameObjectManager_SetObjectPrevPosition(playerIndex, playerPosition);
		playerPosition.Y = max(playerPosition.Y - 1.0f, 6.0f);
		F_GameObjectManager_SetObjectPosition(playerIndex, playerPosition);
	}
	else if (f_Check_KeyDown(0x53)) /* Press 's' */
	{
		F_GameObjectManager_SetObjectPrevPosition(playerIndex, playerPosition);
		playerPosition.Y = min(playerPosition.Y + 1.0f, d_game_height);
		F_GameObjectManager_SetObjectPosition(playerIndex, playerPosition);
	}

	else if (f_Check_KeyDown(0x41)) /* Press 'a' */
	{
		F_GameObjectManager_SetObjectPrevPosition(playerIndex, playerPosition);
		playerPosition.X = max(playerPosition.X - 1.0f, 6.0f);
		F_GameObjectManager_SetObjectPosition(playerIndex, playerPosition);
	}
	else if (f_Check_KeyDown(0x44)) /* Press 'd' */
	{
		F_GameObjectManager_SetObjectPrevPosition(playerIndex, playerPosition);
		playerPosition.X = min(playerPosition.X + 1.0f, d_game_width);
		F_GameObjectManager_SetObjectPosition(playerIndex, playerPosition);
	}
}