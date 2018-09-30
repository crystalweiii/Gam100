#include "Header.h"
#include "Graphic.h"

int f_input()
{
	if (_kbhit())
	{
		switch (fgetc(stdin))
		{
		case 'W':
			printf("W has been hit");
			return 'W';
			break;
		default:
			printf("wrong input");
			break;
		}
	}
	return 0;
}