#include "Input.h"

int f_Check_KeyDown_Once(int key)
{
	if (_kbhit())
	{
		return (key == _getch());
	}
	return 0;
}

int f_Check_KeyDown(int key)
{
	a_key_check[key] = GetKeyState(key);
	return (a_key_check[key] != 0 && a_key_check[key] != 1);
}
