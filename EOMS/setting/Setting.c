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

static int Start(Setting *pSet)
{
	LOG_INFO("Setting starts");
	return 0;
}
static int Stop(Setting *pSet)
{
	LOG_INFO("Setting Stops");
	return 0;
}

//==============================================================================
// Global variables

//==============================================================================
// Global functions

void SetterInit(Setting * pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	pSet->isSignal = false;
	pSet->isColector = false;
	pSet->instrumentFlag = Instrument_Unknown;

}
void SetterDeinit(Setting * pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	pSet->isSignal = false;
	pSet->isColector = false;
}