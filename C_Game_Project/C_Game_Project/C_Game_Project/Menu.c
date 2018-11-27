/*********************************************************************************************************************
Filename :	Menu.h / Menu.c
Author(s):	Ngian Teck Wei
Login(s) :	teckwei.ngian(100%)

Description/Features:
This will be where the menu's functionally will be placed and use by others in need of a menu
**********************************************************************************************************************/
#include "Menu.h"
#include "Graphic.h"
#include "Map.h"


/*Logic to show how object in menu is selected*/
void F_Menu_Select(COORD top_position, COORD btm_position)
{
	F_Graphic_DrawBorder(top_position, btm_position);
}


/*Logic to show how object in menu is de-selected*/
void F_Menu_De_Select(COORD top_position , COORD btm_position)
{
    F_Graphic_DrawBorder_Asc(top_position, btm_position , 32 );
}

