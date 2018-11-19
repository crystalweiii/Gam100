#ifndef MATH_H
#define MATH_H
#include <Windows.h>

typedef struct 
{
	float X;
	float Y;
}Vector2D;


COORD Math_Get_Border(COORD GivenCOORD, int movement);

#endif