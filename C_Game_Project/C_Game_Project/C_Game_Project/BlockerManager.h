/************************************************************************************************
Filename :	Blocker.h / Blocker.c
Author(s):	
Login(s) :	

Description/Features:
This file contains init, update, cleaning up blocker.
It contains functions to blocker, kill blocker.

************************************************************************************************/

#pragma once
#include "Header.h"

/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_BlockerManager_Init();
void F_BlockerManager_Update();
void F_BlockerManager_Exit();

/*------------------------------------------------------------------------------
// Utility
//----------------------------------------------------------------------------*/
/* Spawn: Red/Blue/Green bullet */
void F_BlockerManager_SpawnBlocker(ObjectType type, int posX, int posY);

/* Destroy: Bullet */
void F_BlockerManager_KillBlocker(int index);