//==============================================================================
//
// Title:		LCRSetting.c
// Purpose:		A short description of the implementation.
//
// Created on:	2023-03-16 at 17:19:29 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "LCRSetting.h"
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
void LCRSettingInit(LCRSetting *pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	SetterInit(&pSet->setting);
    pSet->setting.instrumentFlag = Instrument_LCRMeter;

	pSet->setting.Start = Start;
	pSet->setting.Stop = Stop;

}
void LCRSettingDeinit(LCRSetting *pSet)
{
	SetterDeinit(&pSet->setting);
}
