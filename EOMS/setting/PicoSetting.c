//==============================================================================
//
// Title:		PicoSetting.c
// Purpose:		A short description of the implementation.
//
// Created on:	2023-03-16 at 17:11:40 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "PicoSetting.h"

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
void PicoSettingInit(PicoSetting *pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	SetterInit(&pSet->setting);
	pSet->setting.instrumentFlag = Instrument_Picoammeter;

	pSet->setting.Start = Start;
	pSet->setting.Stop = Stop;
}
void PicoSettingDeinit(PicoSetting *pSet)
{
	SetterDeinit(&pSet->setting);
}
