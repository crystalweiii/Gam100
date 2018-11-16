/**************************************************************************
	Files: PlayerManager.h / PlayerManager.c
	Bullet Functions: [Joel: 100%]
	Player Init / Update / Exit Functions: [Desmond: 100%]
**************************************************************************/
#pragma once
#include "Math.h"

/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_PlayerManager_Init();
void F_PlayerManager_Update(float dt);
void F_PlayerManager_Exit();



/*------------------------------------------------------------------------------
// Others
//----------------------------------------------------------------------------*/
void F_PlayerManager_CheckInput();