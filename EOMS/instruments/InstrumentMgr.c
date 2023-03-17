//==============================================================================
//
// Title:		InstrumentMgr.c
// Purpose:		A short description of the implementation.
//
// Created on:	2022-08-16 at 15:07:11 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <string.h>
#include "InstrumentMgr.h"
#include "visa.h"
#include "logger.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static ViSession defaultRM = 0;
static InstrumentListNode *defaultInstrList = NULL;

//==============================================================================
// Static functions
static int sFindResource()
{
	ViStatus status;

	ViUInt32 numInstrs;
	ViFindList findList;
	char instrResourceString[VI_FIND_BUFLEN];

	/* Find all the  resources in our system and store the  */
	/* number of resources in the system in numInstrs.                  */
	status = viFindRsrc(defaultRM, "?*INSTR", &findList, &numInstrs, instrResourceString);

	if (status < VI_SUCCESS)
	{
		LOG_FATAL("An error occurred while finding resources.");
		viClose(defaultRM);
		defaultRM = 0;
		return -1;
	}
	LOG_INFO(" %d instruments are detected. defaultRM is %d", numInstrs, defaultRM);

	unsigned short intfType;
	unsigned short intfNum;
	int i = numInstrs;
	InstrMgr.instrumentsCount = 0;
	while (i > 0)
	{

		status = viParseRsrc(defaultRM, instrResourceString, &intfType, &intfNum);

		LOG_INFO("instrument %s is connected, intfType is %d,intfNum is %d.", instrResourceString, intfType, intfNum);

		if (intfType != VI_INTF_ASRL && intfType != VI_INTF_USB && intfType != VI_INTF_GPIB)
		{
			--i;
			continue;
		}

		Instrument *pInstr = InstrumentAllocInit();
		pInstr->resouceMgr = defaultRM;
		pInstr->type = intfType;
		pInstr->status = Instrument_Status_Connected;
		memcpy(pInstr->address, instrResourceString, VI_FIND_BUFLEN);
		pInstr->index = InstrMgr.instrumentsCount++;

		InstrumentListPushBack(InstrMgr.plist, pInstr);

		if (i > 1)
		{
			status = viFindNext(findList, instrResourceString);
			if (status < VI_SUCCESS)
			{
				LOG_ERROR("Error viFindNext %d.", status);
				break;
			}
		}

		--i;
	}

	return 0;
}

static int Init(int x)
{
	if (0 == defaultRM)
	{
		/*
		 * First we must call viOpenDefaultRM to get the manager
		 * handle.  We will store this handle in defaultRM.
		 */

		ViStatus status = viOpenDefaultRM(&defaultRM);
		if (status < VI_SUCCESS)
		{
			LOG_FATAL("Could not open a session to the VISA Resource Manager!");
			return -1;
		}
	}

	return 0;
}

static int Scan(int x)
{
	InstrumentListClear(InstrMgr.plist);
	return sFindResource(x);
}

static int Shutdown(int x)
{
	if (0 != defaultRM)
	{
		viClose(defaultRM);
		defaultRM = 0;
	}
	InstrumentListClear(InstrMgr.plist);
	return 0;
}

static Instrument * GetInstrByIndex(int x)
{
	InstrumentListNode *cur = *InstrMgr.plist;
	InstrumentListNode *next = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->pInstr->index == x)
		{
			return cur->pInstr;
		}
		cur = next;
	}
	return NULL;
}

//==============================================================================
// Global variables

InstrumentMgr InstrMgr = {
	.plist = &defaultInstrList,
	.instrumentsCount = 0,
	.Init = Init,
	.Scan = Scan,
	.Shutdown = Shutdown,
	.GetInstrByIndex = GetInstrByIndex
   
};



//==============================================================================
// Global functions
