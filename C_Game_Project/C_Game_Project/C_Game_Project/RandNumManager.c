/*********************************************************************************************************************
Filename :	RandNumManager.h / RandNumManager.c
Author(s):	Darren
Login(s) :	s.low (100%)

Description/Features:
This file contains generating random numbers
It contains function that generate a random number

**********************************************************************************************************************/

#pragma once

#include "RandNumManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int GenerateRandNum(int maxRange)
{
	int randomValue = 0;
	srand(time(0));
	randomValue = rand() % maxRange;
	return randomValue;
}
