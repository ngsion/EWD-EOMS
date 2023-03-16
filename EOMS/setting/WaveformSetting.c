//==============================================================================
//
// Title:		WaveformSetting.c
// Purpose:		A short description of the implementation.
//
// Created on:	2023-03-16 at 17:19:51 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "WaveformSetting.h"

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
void WaveformSettingInit(WaveformSetting *pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	SetterInit(&pSet->setting);
	pSet->setting.instrumentFlag = Instrument_WaveformGenerator;

	pSet->setting.Start = Start;
	pSet->setting.Stop = Stop;
}
void WaveformSettingDeinit(WaveformSetting *pSet)
{
	SetterDeinit(&pSet->setting);
}
