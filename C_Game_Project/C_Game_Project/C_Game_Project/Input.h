/************************************************************************************************
Filename :	Input.h / Input.c
Author(s): Ngian Teck Wei
Login(s) : teckwei.ngian(100%)

Description/Features:
Input handling that will provide function to check input and handle 
them in different way
************************************************************************************************/

#include "Header.h"

int a_key_check[127]; /*Store bool for each key*/

float f_KeyUpdate(float dt);        /*To update the delay with dt*/
int f_Check_KeyHit();

/*Check keybroad hit and return key hit*/

/*For those key that needs delay*/
int f_Check_KeyDown_Slow(int key);

/*Instant response with spam*/
int f_Check_KeyDown(int key); 

