/************************************************************************************************
Filename :	Input.h / Input.c
Author(s): Ngian Teck Wei
Login(s) : teckwei.ngian(100%)

Description/Features:
Input handling that will provide function to check input and handle
them in different way
************************************************************************************************/

#include "Input.h"

/*for key delay*/
float delay = 1; 


float f_KeyUpdate(float dt)
{
   /*delay bool according to dt*/
	if(delay<1.f)
		delay += dt*4;
	return delay;
}


int f_Check_KeyHit()
{
	return _kbhit();
}


int f_Check_KeyDown_Slow(int key)
{

	 if (delay >= 1.f &&  f_Check_KeyDown(key))
	 {
		 delay = 0.f;
		 return 1;
	 }
	return 0;
	/*
	if (_kbhit())
	{
		return (key == _getch());
	}
	return 0;
	*/
}

int f_Check_KeyDown(int key)
{
	a_key_check[key] = GetKeyState(key);
	return (a_key_check[key] != 0 && a_key_check[key] != 1);
}
