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

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

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

void SettingInit(Setting * pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	pSet->Init = Init;
	pSet->Save = Save;
	pSet->isSignal = false;
	pSet->isColector = false;
	pSet->instrumentFlag = Instrument_Unknown;
	pSet->lastInstrIndex = 0;

}
void SettingDeinit(Setting * pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	pSet->isSignal = false;
	pSet->isColector = false;
	pSet->lastInstrIndex = 0;
}
