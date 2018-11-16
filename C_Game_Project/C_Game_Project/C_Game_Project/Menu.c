#include "Menu.h"
#include "Graphic.h"
#include "Map.h"



void F_Menu_Select(COORD top_position, COORD btm_position)
{
	F_Map_DrawBorder(top_position, btm_position);
}

void F_Menu_De_Select(COORD top_position , COORD btm_position)
{
    F_Map_DrawBorder_Asc(top_position, btm_position , 32 );
}

