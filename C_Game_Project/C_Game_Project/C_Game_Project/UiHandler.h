#pragma once
#include "Header.h"
#define MAX_PRINTOUT_CHAR 100


/*
typedef struct
{
	GameObject v_game_object;
	int v_index;
	char v_printOut[MAX_PRINTOUT_CHAR];
	int v_digit;
}UiObject;

UiObject v_UiObject[10];
int x = 0;

void F_UIobject_init() {
	UiObject tempUiObj;
	GameObject tempGObj;
	COORD tempPos = {0,0};

	tempGObj.active = 0;
	tempGObj.position = tempPos;

	tempUiObj.v_game_object = tempGObj;
	tempUiObj.v_index = 0;
	tempUiObj.v_digit = 0;

	for (x = 0; x < 10; x++) {
		v_UiObject[x] = tempUiObj;
	}

}

*/
/*
void F_Insert_Print_Out() {
	
	for (x = 0; x < 10; x++)
	{
		if (v_UiObject[x].v_game_object.active != 1)
	}
	
}
*/
void F_UI_Init();
void F_UI_Print_Out();

void F_UI_Print_Out_Index(int index);
void F_UI_Clear_Index(int index);

void F_UI_Border_PO();


void F_UI_Basic_Instru();
void F_UI_Game_Instru();
void F_UI_Game_Info_Right();
void F_UI_Game_Info_Below();
void F_UI_Game_Continue_Instru();