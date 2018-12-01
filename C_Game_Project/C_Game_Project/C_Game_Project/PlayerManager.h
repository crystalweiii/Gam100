/*********************************************************************************************************************
Filename :	PlayerManager.h / PlayerManager.c
Author(s):	Ong Jia Quan Joel, Desmond
Login(s) :	o.jiaquanjoel(40%), seeweedesmond.yeo(60%)

Description/Features:
This file contains init, update, cleanup for player.
It contains function that handle player inputs during gameplay, and trigger event when input is enter.

**********************************************************************************************************************/
#pragma once
#include "Math.h"

/*------------------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------------*/
void F_PlayerManager_Init();
void F_PlayerManager_Update(float dt);
void F_PlayerManager_Exit();

/*------------------------------------------------------------------------------
// Getter Function
//----------------------------------------------------------------------------*/
int F_PlayerManager_GetPlayerLife();
void F_PlayerManager_DecrementPlayerLife(int decrement);

/*------------------------------------------------------------------------------
// Others
//----------------------------------------------------------------------------*/
void F_PlayerManager_CheckInput();
void F_PlayerManager_RestartPlayerLife();