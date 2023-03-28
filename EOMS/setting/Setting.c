//==============================================================================
//
// Title:		Setting.c
// Purpose:		A short description of the implementation.
//
// Created on:	2023-03-16 at 16:58:54 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "Setting.h"
#include "logger.h"
#include "stdlib.h"
#include "time.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static void get_rand_str(char s[], unsigned int number)
{
	char str[64] = "00123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int i;
	char ss[2];
	// printf("%c %cn",str[1],str[62]);
	srand((unsigned int)time((time_t *)NULL));
	for (i = 1; i <= number; i++)
	{
		sprintf(ss, "%c", str[(rand() % 62) + 1]);
		// printf(ss);
		strcat(s, ss);
	}
}

static int Init(Setting *pSet)
{
	LOG_INFO("Setting Inits");
	return 0;
}
static int Save(Setting *pSet)
{
	LOG_INFO("Setting Save");
	return 0;
}

//==============================================================================
// Global variables

//==============================================================================
// Global functions

void SettingInit(Setting *pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	pSet->Init = Init;
	pSet->Save = Save;
	pSet->isSignal = false;
	pSet->isCollector = false;
	pSet->instrumentFlag = Instrument_Unknown;
	pSet->lastInstrIndex = 0;

	memset(pSet->batchNo, 0, BATCH_NO_LENGTH);
	get_rand_str(pSet->batchNo, 6);
}
void SettingDeinit(Setting *pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	pSet->isSignal = false;
	pSet->isCollector = false;
	pSet->lastInstrIndex = 0;
}
