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
	LOG_INFO("Setting Init");
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
void PicoSettingInit(PicoSetting *pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	SettingInit(&pSet->setting);
	pSet->setting.instrumentFlag = Instrument_Picoammeter;

	pSet->setting.Init = Init;
	pSet->setting.Save = Save;
}
void PicoSettingDeinit(PicoSetting *pSet)
{
	SettingDeinit(&pSet->setting);
}
