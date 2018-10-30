#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <dos.h>

#define d_game_width 90
#define d_game_height 20

#define d_maxchar 1000

#define d_map_amount 3
#define txt_DGPLogo "txt_file/DigipenLogo.txt"
#define txt_Map1 "txt_file/Map1.txt"

typedef struct
{
	int active;
	COORD position;
}GameObject;

enum GameState
{
	Pause = -2,
	End = -1,

	StartUp = 0,
	MainMenu,
	GamePlay,

	NumberOfState

};

#endif // !Header.h



