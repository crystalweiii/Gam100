#pragma once
#include "Math.h"

#define ObjectSize 9

typedef enum ObjectType
{
	None,
	Taken,
	Player,
	Enemy,
	Bullet
}ObjectType;

typedef struct GameObject
{
	ObjectType type;
	Vector2D prevposition;
	Vector2D position;
	Vector2D velocity;
	char image[ObjectSize];
}GameObj;