/************************************************************************************************
Filename :	Input.h / Input.c
Author(s):	
Login(s) :	

Description/Features:

************************************************************************************************/

#include "Input.h"


float delay = 1; /*for key delay*/


float f_KeyUpdate(float dt)
{
   /*delay bool according to dt*/
	if(delay<1.f)
		delay += dt*2;
	return delay;
}


int f_Check_KeyHit()
{
	return _kbhit();
}


int f_Check_KeyDown_Slow(int key)
{

     a_key_check[key] = GetKeyState(key);
	 if ((delay >= 1.f) && (a_key_check[key] != 0 && a_key_check[key] != 1))
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
