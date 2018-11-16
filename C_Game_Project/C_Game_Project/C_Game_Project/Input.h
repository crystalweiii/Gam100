/************************************************************************************************
Filename :	Input.h / Input.c
Author(s):
Login(s) :

Description/Features:

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

