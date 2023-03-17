//==============================================================================
//
// Title:		SettingMgr.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-10-04 at 21:10:43 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "SettingMgr.h"
#include "PicoSetting.h"
#include "LCRSetting.h"
#include "WaveformSetting.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static Setting *defaultSettingArray[SETTING_MAX_NUM];

//==============================================================================
// Static functions
static int Init(int x)
{
	int i = 0;
	for (; i < SETTING_MAX_NUM; i++)
	{
		defaultSettingArray[i] = NULL;
	}

	defaultSettingArray[0] = (Setting *)malloc(sizeof(PicoSetting));
	PicoSettingInit((PicoSetting *)defaultSettingArray[0]);

	defaultSettingArray[1] = (Setting *)malloc(sizeof(WaveformSetting));
	WaveformSettingInit((WaveformSetting *)defaultSettingArray[1]);

	defaultSettingArray[2] = (Setting *)malloc(sizeof(LCRSetting));
	LCRSettingInit((LCRSetting *)defaultSettingArray[2]);

	for (i = 0; i < SETTING_MAX_NUM; i++)
	{
		if (NULL != defaultSettingArray[i])
		{
			defaultSettingArray[i]->Init(defaultSettingArray[i]);
		}
	}

	return 0;
}

static int Shutdown(int x)
{
	int i = 0;
	for (; i < SETTING_MAX_NUM; i++)
	{
		if (NULL != defaultSettingArray[i])
		{
			defaultSettingArray[i]->Save(defaultSettingArray[i]);
		}
	}

	for (i = 0; i < SETTING_MAX_NUM; i++)
	{
		if (NULL != defaultSettingArray[i])
		{
			free(defaultSettingArray[i]);
			defaultSettingArray[i] = NULL;
		}
	}

	return 0;
}
static Setting *FindWithInstrFlag(int flag)
{
	Setting *pSet = NULL;
	for (int i = 0; i < SETTING_MAX_NUM; i++)
	{
		if (NULL != defaultSettingArray[i] && (defaultSettingArray[i]->instrumentFlag == flag))
		{
			pSet = defaultSettingArray[i];
			break;
		}
	}
	return pSet;
}
//==============================================================================
// Global variables

//==============================================================================
// Global functions
SettingMgr SetMgr = {
	.Init = Init,
	.Shutdown = Shutdown,
	.FindWithInstrFlag = FindWithInstrFlag};
