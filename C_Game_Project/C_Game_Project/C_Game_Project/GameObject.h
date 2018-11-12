#pragma once
#include "Math.h"
#include "Header.h"

#define ObjectSize 9


typedef struct GameObject
{
	ObjectType type;

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