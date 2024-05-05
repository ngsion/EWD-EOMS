//==============================================================================
//
// Title:		KoradSetting.c
// Purpose:		A short description of the implementation.
//
// Created on:	2024-05-05 at 21:25:04 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "KoradSetting.h"
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
	KoradSetting * pLCRset = (KoradSetting*) pSet;
 
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
void KoradSettingInit(KoradSetting *pSet)
{
	if (NULL == pSet)
	{
		return;
	}
	SettingInit(&pSet->setting);
    pSet->setting.instrumentFlag = Instrument_Korad;
 

}
void KoradSettingDeinit(KoradSetting *pSet)
{
	SettingDeinit(&pSet->setting);
}
