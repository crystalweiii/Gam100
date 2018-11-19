#include "Math.h"

COORD Math_Get_Border(COORD GivenCOORD, int movement)
{
	COORD Temp = { GivenCOORD.X + movement, GivenCOORD.Y + movement };
	return Temp;
}