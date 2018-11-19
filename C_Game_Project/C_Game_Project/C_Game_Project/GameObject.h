/************************************************************************************************
Filename :	GameObject.h / GameObject.c
Author(s):	Ong Jia Quan Joel
Login(s) :	o.jiaquanjoel(100%)

Description/Features:

************************************************************************************************/

#pragma once
#include "Math.h"
#include "Header.h"
#include <stdbool.h>

#define ObjectSize 9


typedef struct GameObject
{
	ObjectType type;

	/* IsVisible*/
	bool isVisible;

	/* Scale */
	int scaleX;
	int scaleY;

	/* Anchor */
	int anchorOffsetX;
	int anchorOffsetY;

	/* Accumulated position of object. Will be rounded off to put on screen */
	float positionX;
	float positionY;

	/* Convenient variable: Use for unDrawing previous tile */
	float prevPositionX;
	float prevPositionY;

	/* Velocity */
	float velocityX;
	float velocityY;

	/* Speed */
	float speed;

	/* Move Direction */
	float directionX;
	float directionY;

	char image[ObjectSize];
}GameObj;