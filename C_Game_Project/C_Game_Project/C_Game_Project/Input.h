#include "Header.h"
#include "Graphic.h"

int f_input()
{

	if (_kbhit())
	{
		int temp = _getch();
		printf("input get: %d" , temp);
		return temp;
	}
	/*printf("No input");*/
	return 0;
}