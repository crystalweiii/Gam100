/*********************************************************************************************************************
Filename :	RandNumManager.h / RandNumManager.c
Author(s):	Darren
Login(s) :	s.low (100%)

Description/Features:
...

**********************************************************************************************************************/

#pragma once

#include "RandNumManager.h"
#include <stdio.h>
#include <stdlib.h>

int GenerateRandNum(int maxRange)
{
	int randomValue;
	randomValue = rand() % maxRange;
	return randomValue;
}
